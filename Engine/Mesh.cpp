//Mesh class for rendering
#include"Mesh.h"


Mesh::Mesh(void)
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glGenBuffers(1, &m_vertexBuffer);
	glGenBuffers(1, &m_colorBuffer);
	glGenBuffers(1, &m_uvBuffer);
	glGenBuffers(1, &m_tangentBuffer);
	glGenBuffers(1, &m_bitangentBuffer);
	glGenBuffers(1, &m_indexBuffer);
	m_cameraMaster = CameraMaster::GetInstance();
	m_shaderMaster = ShaderMaster::GetInstance();
	m_vertices = std::vector<float>();
	m_indices = std::vector<uint>();
	m_indexMap = std::map<vec3, int, vec3Comparison>();
}
Mesh::~Mesh(void)
{

}
void Mesh::Render(mat4 &p_modelMatrix)
{
	mat4 persp =m_cameraMaster->GetPerspMatrix();
	mat4 view = m_cameraMaster->GetViewMatrix();
	mat4 mvp = persp*view*p_modelMatrix;
	if (m_renderWireframe)
	{
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	}
	glUseProgram(m_shaderMaster->GetProgramID());
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glUniformMatrix4fv(glGetUniformLocation(m_shaderMaster->GetProgramID(), "MVP"), 1, GL_FALSE, &mvp[0][0]);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glDrawElements(GL_TRIANGLES,m_numVertices, GL_UNSIGNED_INT,(void*)0);
	glDisableVertexAttribArray(0);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

}

Mesh* Mesh::Cube(float p_size)
{
	Mesh* cube = new Mesh();
	float len = p_size / 2.0f;
	vec3 p0 = vec3(-len, len, len);
	vec3 p1 = vec3(len, len, len);
	vec3 p2 = vec3(-len, -len, len);
	vec3 p3 = vec3(len, -len, len);
	vec3 p4 = vec3(-len, len, -len);
	vec3 p5 = vec3(len, len, -len);
	vec3 p6 = vec3(-len, -len, -len);
	vec3 p7 = vec3(len, -len, -len);
	cube->AddQuad(p0, p1, p3, p2);
	cube->AddQuad(p1, p5, p7, p3);
	cube->AddQuad(p4, p6, p7, p5);
	cube->AddQuad(p4, p0, p2, p6);
	cube->AddQuad(p0, p4, p5, p1);
	cube->AddQuad(p2, p3, p7, p6);
	cube->CompileMesh();
	return cube;
}

Mesh* Mesh::Cylinder(float p_radius, float p_height, uint p_subdivisions)
{
	Mesh* cylinder = new Mesh();
	if (p_subdivisions < 3)
	{
		p_subdivisions = 3;
	}
	else if (p_subdivisions > 360)
	{
		p_subdivisions = 360;
	}

	float approxStep = 360.0f / p_subdivisions;
	vec3 baseCenter = vec3(0, -p_height*.5f, 0);
	vec3 topCenter = vec3(0, p_height*.5f, 0);
	float leftx;
	float leftz;
	float rightx;
	float rightz;
	for (uint i = 0; i < p_subdivisions;i++)
	{
		leftx = glm::cos(glm::radians(i*approxStep))*p_radius;
		leftz = glm::sin(glm::radians(i*approxStep))*p_radius;
		rightx = glm::cos(glm::radians((i + 1)*approxStep))*p_radius;
		rightz = glm::sin(glm::radians((i + 1)*approxStep))*p_radius;
		cylinder->AddTri(baseCenter, 
			vec3(leftx, baseCenter.y, leftz),
			vec3(rightx, baseCenter.y, rightz));

		cylinder->AddTri(topCenter,
			vec3(rightx, topCenter.y, rightz),
			vec3(leftx, topCenter.y, leftz)
			);
		cylinder->AddQuad(vec3(leftx, baseCenter.y, leftz), vec3(rightx, baseCenter.y, rightz),
			vec3(rightx, topCenter.y, rightz), vec3(leftx, topCenter.y, leftz));

	}
	cylinder->CompileMesh();
	return cylinder;
}
void Mesh::AddTri(vec3 &p1, vec3 &p2, vec3 &p3)
{
	//see if these vertices have already been used, because we're doing indexed rendering
	CheckVertex(p1);
	CheckVertex(p2);
	CheckVertex(p3);

	//should check for counter clockwise here with crossproduct

	//add the vertices
	m_indices.push_back(m_indexMap[p1]);
	m_indices.push_back(m_indexMap[p2]);
	m_indices.push_back(m_indexMap[p3]);
	m_numVertices += 3;

	
}

void Mesh::AddQuad(vec3 &p1, vec3 &p2, vec3 &p3, vec3 &p4)
{
	AddTri(p1, p2, p3);
	AddTri(p1, p3, p4);
}

void Mesh::CheckVertex(vec3 &p)
{
	if (m_indexMap.find(p) == m_indexMap.end()) //not in there already
	{
		m_indexMap[p] = m_vertices.size()/3;
		m_vertices.push_back(p.x);
		//fprintf(stdout, "%f ",p.x);
		m_vertices.push_back(p.y);
		//fprintf(stdout, "%f ",p.y);
		m_vertices.push_back(p.z);
		//fprintf(stdout, "%f \n",p.z);
		
	}
}

void Mesh::CompileMesh(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(float), &m_vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(float), &m_vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size()*sizeof(uint), &m_indices[0], GL_STATIC_DRAW);
}