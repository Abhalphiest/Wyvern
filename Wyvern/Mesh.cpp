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
	//remove our reference to all the buffer objects
	//if we're the last reference, that memory will be freed
	glDeleteVertexArrays(1,&m_vao);
	m_vao = 0; //just in case, I guess?
}
Mesh& Mesh::operator=(Mesh& other)
{
	glDeleteVertexArrays(1, &m_vao);
	m_vao = other.m_vao;
	m_vertexBuffer = other.m_vertexBuffer;
	m_colorBuffer = other.m_colorBuffer;
	m_uvBuffer = other.m_uvBuffer;
	m_tangentBuffer = other.m_tangentBuffer;
	m_bitangentBuffer = other.m_bitangentBuffer;
	m_indexBuffer = other.m_indexBuffer;
	m_vertices = other.m_vertices; //not a vector of pointers, so just this assignment is ok
	m_indices = other.m_indices;
	m_indexMap = other.m_indexMap;
	m_renderWireframe = other.m_renderWireframe;
	m_name = other.m_name;
	//don't need to bother with the singletons, they'll be the same anyway.
	//technically we didn't need to bother with anything other than the vao here, the rest would have been done for us
	//but it's nice to have it all explicit here in case the structure of the class changes to need something more complicated, like memory management
	return *this;
}
Mesh::Mesh(Mesh& other)
{
	m_vao = other.m_vao;
	m_vertexBuffer = other.m_vertexBuffer;
	m_colorBuffer = other.m_colorBuffer;
	m_uvBuffer = other.m_uvBuffer;
	m_tangentBuffer = other.m_tangentBuffer;
	m_bitangentBuffer = other.m_bitangentBuffer;
	m_indexBuffer = other.m_indexBuffer;
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glGenBuffers(1, &m_vertexBuffer);
	glGenBuffers(1, &m_colorBuffer);
	glGenBuffers(1, &m_uvBuffer);
	glGenBuffers(1, &m_tangentBuffer);
	glGenBuffers(1, &m_bitangentBuffer);
	glGenBuffers(1, &m_indexBuffer);
	m_vertices = other.m_vertices; //not a vector of pointers, so just this assignment is ok
	m_indices = other.m_indices;
	m_indexMap = other.m_indexMap;
	m_renderWireframe = other.m_renderWireframe;
	m_name = other.m_name;
	m_cameraMaster = other.m_cameraMaster;
	m_shaderMaster = other.m_shaderMaster;
	//technically we didn't need to bother with anything other than the vao here, the rest would have been done for us
	//but it's nice to have it all explicit here in case the structure of the class changes to need something more complicated, like memory management
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
Mesh* Mesh::Sphere(float p_radius, uint p_subdivisions)
{
	Mesh* sphere = new Mesh();
	if (p_subdivisions < 3)
		p_subdivisions = 3;
	else if (p_subdivisions > 360)
		p_subdivisions = 360;

	float approxStep = 360.0f / p_subdivisions;
	float radstep = 180.0f / p_subdivisions;
	float heightstep = 180.0f / p_subdivisions;
	vec3 baseCenter = vec3(0, -p_radius, 0);
	vec3 topCenter = vec3(0, p_radius, 0);
	float leftx;
	float leftz;
	float rightx;
	float rightz;
	float topy;
	float bottomy;
	float bottomrad;
	float toprad;

	//taking the easy O(n^2) time solution here
	for (uint i = 0; i < p_subdivisions; i++)
	{


		for (uint j = 0; j < p_subdivisions; j++)
		{
			leftx = glm::cos(glm::radians(j*approxStep));
			rightx = glm::cos(glm::radians((j + 1)*approxStep));
			leftz = glm::sin(glm::radians(j*approxStep));
			rightz = glm::sin(glm::radians((j + 1)*approxStep));
			topy = baseCenter.y + glm::cos(glm::radians((i + 1)*radstep))*p_radius;
			bottomy = baseCenter.y + glm::cos(glm::radians((i*radstep)))*p_radius;
			bottomrad = glm::sin(glm::radians(i*radstep))*p_radius;
			toprad = glm::sin(glm::radians((i + 1)*radstep))*p_radius;

			sphere->AddQuad(vec3(leftx*toprad, topy, leftz*toprad),
				vec3(rightx*toprad, topy, rightz*toprad),
				vec3(rightx*bottomrad, bottomy, rightz*bottomrad),
				vec3(leftx*bottomrad, bottomy, leftz*bottomrad));
		}

	}


	sphere->CompileMesh();
	return sphere;
}
Mesh* Mesh::Torus(float p_innerRad, float p_outerRad, uint p_subdivisions)
{
	Mesh* torus = new Mesh();
	if (p_subdivisions < 3)
		p_subdivisions = 3;
	else if (p_subdivisions > 360)
		p_subdivisions = 360;

	float approxStep = 360.0f / p_subdivisions;
	float radRing = (p_outerRad - p_innerRad)*.5f;
	float centRad = (p_outerRad + p_innerRad)*.5f;
	vec3 leftEnd;
	vec3 rightEnd;
	float lefty;
	float righty;
	float leftxtop;
	float rightxtop;
	float leftztop;
	float rightztop;
	float leftzbottom;
	float rightzbottom;
	float leftxbottom;
	float rightxbottom;


	//again, easy O(n^2) solution

	for (uint i = 0; i < p_subdivisions; i++)
	{
		leftEnd = vec3(glm::cos(glm::radians(i*approxStep)), 0, glm::sin(glm::radians(i*approxStep)));
		rightEnd = vec3(glm::cos(glm::radians((i + 1)*approxStep)), 0, glm::sin(glm::radians((i + 1)*approxStep)));
		for (uint j = 0; j < p_subdivisions; j++)
		{
			righty = glm::sin(glm::radians(j*approxStep))*radRing;
			lefty = glm::sin(glm::radians((j + 1)*approxStep))*radRing;
			rightxtop = (glm::cos(glm::radians(j*approxStep))*radRing + centRad)*rightEnd.x;
			leftxtop = (glm::cos(glm::radians((j + 1)*approxStep))*radRing + centRad)*rightEnd.x;
			rightztop = (glm::cos(glm::radians(j*approxStep))*radRing + centRad)*rightEnd.z;
			leftztop = (glm::cos(glm::radians((j + 1)*approxStep))*radRing + centRad)*rightEnd.z;
			rightxbottom = (glm::cos(glm::radians(j*approxStep))*radRing + centRad)*leftEnd.x;
			leftxbottom = (glm::cos(glm::radians((j + 1)*approxStep))*radRing + centRad)* leftEnd.x;
			rightzbottom = (glm::cos(glm::radians(j*approxStep))*radRing + centRad)*leftEnd.z;
			leftzbottom = (glm::cos(glm::radians((j + 1)*approxStep))*radRing + centRad)* leftEnd.z;

			torus->AddQuad(vec3(leftxtop, lefty, leftztop),
				vec3(rightxtop, righty, rightztop),
				vec3(rightxbottom, righty, rightzbottom),
				vec3(leftxbottom, lefty, leftzbottom));
		}
	}

	torus->CompileMesh();
	return torus;
}
Mesh* Mesh::Cone(float p_radius, float p_height, uint p_subdivisions)
{
	Mesh* cone = new Mesh();
	if (p_subdivisions < 3)
		p_subdivisions = 3;
	else if (p_subdivisions > 360)
		p_subdivisions = 360;

	float approxStep = 360.0f / p_subdivisions;
	vec3 baseCenter = vec3(0, -p_height*.5f, 0);
	vec3 topCenter = vec3(0, p_height*.5f, 0);
	float leftx;
	float leftz;
	float rightx;
	float rightz;

	for (uint i = 0; i < p_subdivisions; i++)
	{
		leftx = glm::cos(glm::radians(i*approxStep))*p_radius;
		leftz = glm::sin(glm::radians(i*approxStep))*p_radius;
		rightx = glm::cos(glm::radians((i + 1)*approxStep))*p_radius;
		rightz = glm::sin(glm::radians((i + 1)*approxStep))*p_radius;

		cone->AddTri(baseCenter, vec3(leftx, baseCenter.y, leftz),
			vec3(rightx, baseCenter.y, rightz));
		cone->AddTri(topCenter, vec3(rightx, baseCenter.y, rightz), vec3(leftx, baseCenter.y, leftz));
	}



	cone->CompileMesh();
	return cone;
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
Mesh* Mesh::Pipe(float p_outerRadius, float p_innerRadius, float p_height, uint p_subdivisions)
{
	Mesh* pipe = new Mesh();
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
	for (uint i = 0; i < p_subdivisions; i++)
	{
		leftx = glm::cos(glm::radians(i*approxStep));
		leftz = glm::sin(glm::radians(i*approxStep));
		rightx = glm::cos(glm::radians((i + 1)*approxStep));
		rightz = glm::sin(glm::radians((i + 1)*approxStep));
		pipe->AddQuad(vec3(rightx*p_outerRadius, baseCenter.y, rightz*p_outerRadius),
			vec3(rightx*p_innerRadius, baseCenter.y, rightz*p_innerRadius),
			vec3(leftx*p_innerRadius, baseCenter.y, leftz*p_innerRadius),
			vec3(leftx*p_outerRadius, baseCenter.y, leftz*p_outerRadius)
			);

		pipe->AddQuad(vec3(leftx*p_innerRadius, topCenter.y, leftz*p_innerRadius),
			vec3(rightx*p_innerRadius, topCenter.y, rightz*p_innerRadius),
			vec3(rightx*p_outerRadius, topCenter.y, rightz*p_outerRadius),
			vec3(leftx*p_outerRadius, topCenter.y, leftz*p_outerRadius)
			);
		pipe->AddQuad(
			vec3(rightx*p_innerRadius, baseCenter.y, rightz*p_innerRadius),
			vec3(rightx*p_innerRadius, topCenter.y, rightz*p_innerRadius),
			vec3(leftx*p_innerRadius, topCenter.y, leftz*p_innerRadius),
			vec3(leftx*p_innerRadius, baseCenter.y, leftz*p_innerRadius)
			);
		pipe->AddQuad(vec3(leftx*p_outerRadius, topCenter.y, leftz*p_outerRadius),
			vec3(rightx*p_outerRadius, topCenter.y, rightz*p_outerRadius),
			vec3(rightx*p_outerRadius, baseCenter.y, rightz*p_outerRadius),
			vec3(leftx*p_outerRadius, baseCenter.y, leftz*p_outerRadius)
			);

	}
	pipe->CompileMesh();
	return pipe;
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
	p = TruncateVector(p); //get rid of redundant points due to rounding error
	if (m_indexMap.find(p) == m_indexMap.end()) //not in there already
	{
		
		m_indexMap[p] = m_vertices.size()/3;
		m_vertices.push_back(p.x);
		fprintf(stdout, "%f ",p.x);
		m_vertices.push_back(p.y);
		fprintf(stdout, "%f ",p.y);
		m_vertices.push_back(p.z);
		fprintf(stdout, "%f \n",p.z);
		
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

vec3 Mesh::TruncateVector(const vec3& v)
{
	vec3 returnV = vec3();
	returnV.x = std::trunc(100000 * v.x) / 100000;
	returnV.y = std::trunc(100000 * v.y) / 100000;
	returnV.z = std::trunc(100000 * v.z) / 100000;
	return returnV;
}
