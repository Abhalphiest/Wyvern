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
	glGenBuffers(1, &m_normalBuffer);
	glGenBuffers(1, &m_matrixBuffer);
	glBindVertexArray(0);
	m_cameraMaster = CameraMaster::GetInstance();
	m_shaderMaster = ShaderMaster::GetInstance();
	m_materialMaster = MaterialMaster::GetInstance();
	m_vertices = std::vector<float>();
	m_uvs = std::vector<float>();
	m_normals = std::vector<float>();
	m_indices = std::vector<uint>();
	m_indexMap = std::map<vec3, int, vec3Comparison>();
}
Mesh::~Mesh(void)
{
}
Mesh& Mesh::operator=(Mesh& other)
{
	//fprintf(stdout, "copy assignment called");
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glGenBuffers(1, &m_vertexBuffer);
	glGenBuffers(1, &m_colorBuffer);
	glGenBuffers(1, &m_uvBuffer);
	glGenBuffers(1, &m_tangentBuffer);
	glGenBuffers(1, &m_bitangentBuffer);
	glGenBuffers(1, &m_indexBuffer);
	glGenBuffers(1, &m_normalBuffer);
	glGenBuffers(1, &m_matrixBuffer);
	m_materialIndex = other.m_materialIndex;
	m_numVertices = other.m_numVertices;
	m_vertices = other.m_vertices; //not a vector of pointers, so just this assignment is ok
	m_uvs = other.m_uvs;
	m_normals = other.m_normals;
	m_indices = other.m_indices;
	m_indexMap = other.m_indexMap;
	m_renderWireframe = other.m_renderWireframe;
	m_name = other.m_name;
	m_bufferType = other.m_bufferType;
	CompileMesh();
	m_cameraMaster = CameraMaster::GetInstance();
	m_shaderMaster = ShaderMaster::GetInstance();
	m_materialMaster = MaterialMaster::GetInstance();

	return *this;
}
Mesh::Mesh(Mesh& other)
{
	m_vao = other.m_vao; 
	m_indexBuffer = other.m_indexBuffer;
	m_vertexBuffer = other.m_vertexBuffer; 
	m_colorBuffer = other.m_colorBuffer; 
	m_uvBuffer = other.m_uvBuffer; 
	m_normalBuffer = other.m_normalBuffer;
	m_tangentBuffer = other.m_tangentBuffer;
	m_bitangentBuffer = other.m_bitangentBuffer;
	m_matrixBuffer = other.m_matrixBuffer;
	m_materialIndex = other.m_materialIndex;
	m_numVertices = other.m_numVertices;
	m_vertices = other.m_vertices; //not a vector of pointers, so just this assignment is ok
	m_uvs = other.m_uvs;
	m_normals = other.m_normals;
	m_indices = other.m_indices;
	m_indexMap = other.m_indexMap;
	m_renderWireframe = other.m_renderWireframe;
	m_name = other.m_name;
	m_cameraMaster = CameraMaster::GetInstance();
	m_shaderMaster = ShaderMaster::GetInstance();
	m_materialMaster = MaterialMaster::GetInstance();
	m_bufferType = VERTEX | COLOR;
	CompileMesh();
}
void Mesh::Render(mat4 &p_modelMatrix)
{
	glBindVertexArray(m_vao);
	mat4 persp=m_cameraMaster->GetPerspMatrix();
	mat4 view= m_cameraMaster->GetViewMatrix();
	if (m_renderWireframe)
	{
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	}
	m_materialMaster->BindMaterial(m_materialIndex);
	
	
	
	if (m_bufferType&VERTEX)
	{
		
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glEnableVertexAttribArray(POSITION_ATTRIB_INDEX);
		glVertexAttribPointer(POSITION_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glUniformMatrix4fv(glGetUniformLocation(m_shaderMaster->GetProgramID(), "projection"), 1, GL_FALSE, &persp[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(m_shaderMaster->GetProgramID(), "view"), 1, GL_FALSE, &view[0][0]);
	}
	
	if (m_bufferType&UV)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_uvBuffer);
		glEnableVertexAttribArray(UV_ATTRIB_INDEX);
		glVertexAttribPointer(UV_ATTRIB_INDEX, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
	if (m_bufferType&NORM)
	{
		
		glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
		glEnableVertexAttribArray(NORMAL_ATTRIB_INDEX);
		glVertexAttribPointer(NORMAL_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
	if (m_bufferType&COLOR)
	{
		
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
		glEnableVertexAttribArray(COLOR_ATTRIB_INDEX);
		glVertexAttribPointer(COLOR_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	
	glBindBuffer(GL_ARRAY_BUFFER, m_matrixBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4), &p_modelMatrix[0], GL_STATIC_DRAW);
	GLsizei vec4Size = sizeof(glm::vec4);
	glEnableVertexAttribArray(MODELMAT_ATTRIB_INDEX);
	glVertexAttribPointer(MODELMAT_ATTRIB_INDEX, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)0);
	glEnableVertexAttribArray(MODELMAT_ATTRIB_INDEX+1);
	glVertexAttribPointer(MODELMAT_ATTRIB_INDEX + 1, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(vec4Size));
	glEnableVertexAttribArray(MODELMAT_ATTRIB_INDEX + 2);
	glVertexAttribPointer(MODELMAT_ATTRIB_INDEX + 2, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(2 * vec4Size));
	glEnableVertexAttribArray(MODELMAT_ATTRIB_INDEX + 3);
	glVertexAttribPointer(MODELMAT_ATTRIB_INDEX + 3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(3 * vec4Size));

	glVertexAttribDivisor(MODELMAT_ATTRIB_INDEX, 1);
	glVertexAttribDivisor(MODELMAT_ATTRIB_INDEX + 1, 1);
	glVertexAttribDivisor(MODELMAT_ATTRIB_INDEX + 2, 1);
	glVertexAttribDivisor(MODELMAT_ATTRIB_INDEX + 3, 1);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glDrawElementsInstanced(GL_TRIANGLES,m_numVertices, GL_UNSIGNED_INT,(void*)0,1);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	glBindVertexArray(0);
}

void Mesh::RenderInstanced(std::vector<mat4> p_modelMatrices)
{
	glBindVertexArray(m_vao);
	uint count = p_modelMatrices.size();
	mat4 persp = m_cameraMaster->GetPerspMatrix();
	mat4 view = m_cameraMaster->GetViewMatrix();
	if (m_renderWireframe)
	{
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	}
	m_materialMaster->BindMaterial(m_materialIndex);
	GLuint programID = m_shaderMaster->GetProgramID();
	glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1, GL_FALSE, &persp[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "view"), 1, GL_FALSE, &view[0][0]);
	m_shaderMaster->BindShaderProgram(m_materialMaster->GetShaderProgram());
	



	glBindBuffer(GL_ARRAY_BUFFER, m_matrixBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4)*count, &p_modelMatrices[0], GL_STATIC_DRAW);
	GLsizei vec4Size = sizeof(glm::vec4);
	glEnableVertexAttribArray(MODELMAT_ATTRIB_INDEX);
	glVertexAttribPointer(MODELMAT_ATTRIB_INDEX, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)0);
	glEnableVertexAttribArray(MODELMAT_ATTRIB_INDEX + 1);
	glVertexAttribPointer(MODELMAT_ATTRIB_INDEX + 1, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(vec4Size));
	glEnableVertexAttribArray(MODELMAT_ATTRIB_INDEX + 2);
	glVertexAttribPointer(MODELMAT_ATTRIB_INDEX + 2, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(2 * vec4Size));
	glEnableVertexAttribArray(MODELMAT_ATTRIB_INDEX + 3);
	glVertexAttribPointer(MODELMAT_ATTRIB_INDEX + 3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(3 * vec4Size));

	glVertexAttribDivisor(MODELMAT_ATTRIB_INDEX, 1);
	glVertexAttribDivisor(MODELMAT_ATTRIB_INDEX + 1, 1);
	glVertexAttribDivisor(MODELMAT_ATTRIB_INDEX + 2, 1);
	glVertexAttribDivisor(MODELMAT_ATTRIB_INDEX + 3, 1);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glDrawElementsInstanced(GL_TRIANGLES, m_numVertices, GL_UNSIGNED_INT, (void*)0, count);
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
	cube->m_bufferType = VERTEX | COLOR;
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

	sphere->m_bufferType = VERTEX | COLOR;
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
	torus->m_bufferType = VERTEX | COLOR;
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


	cone->m_bufferType = VERTEX | COLOR;
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
	cylinder->m_bufferType = VERTEX | COLOR;
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
	pipe->m_bufferType = VERTEX | COLOR;
	pipe->CompileMesh();
	return pipe;
}


Mesh* Mesh::LoadObj(const char* path)
{
	Mesh* mesh = new Mesh();
	std::vector<vec3> tempvertices;
	std::vector<vec2> tempuvs;
	std::vector<vec3> tempnormals;
	std::vector<uint> vertexIndices, uvIndices, normalIndices;
	FILE* file = fopen(path, "r");
	if (file == NULL)
	{
		fprintf(stderr, "Could not open the obj file.");
		return nullptr;
	}
	while (true)
	{
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;
		if (strcmp(lineHeader, "v") == 0)
		{
			vec3 v;
			fscanf(file, "%f %f %f\n", &v.x, &v.y, &v.z);
			tempvertices.push_back(v);
			
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			vec2 v;
			fscanf(file, "%f %f\n", &v.x, &v.y);
			tempuvs.push_back(v);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			vec3 v;
			fscanf(file, "%f %f %f\n", &v.x, &v.y, &v.z);
			tempnormals.push_back(v);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			uint vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
								&vertexIndex[1], &uvIndex[1], &normalIndex[1], 
								&vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				printf(".obj file can't be read, try exporting with other options.");
				return nullptr;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}
	if (!mesh->IndexObj(tempvertices, tempuvs, tempnormals, vertexIndices, uvIndices, normalIndices))
		return nullptr;
	mesh->m_bufferType = VERTEX | UV | NORM;
	mesh->CompileMesh();
	return mesh;
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
		//fprintf(stdout, "%f ",p.x);
		m_vertices.push_back(p.y);
		//fprintf(stdout, "%f ",p.y);
		m_vertices.push_back(p.z);
		//fprintf(stdout, "%f \n",p.z);
		
	}
}

void Mesh::CompileMesh(void)
{
	glBindVertexArray(m_vao);
	if (m_bufferType&VERTEX)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(float), &m_vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(POSITION_ATTRIB_INDEX);
		glVertexAttribPointer(POSITION_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
	if (m_bufferType&COLOR)
	{
		vec3 colorVec = m_materialMaster->GetMaterialColor(m_materialIndex);
		std::vector<float> color = std::vector<float>();
		for (uint i = 0; i < m_vertices.size(); i += 3)
		{
			color.push_back(colorVec.x);
			color.push_back(colorVec.y);
			color.push_back(colorVec.z);
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(float), &color[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(COLOR_ATTRIB_INDEX);
		glVertexAttribPointer(COLOR_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
	if (m_bufferType&UV)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, m_uvs.size()*sizeof(float), &m_uvs[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(UV_ATTRIB_INDEX);
		glVertexAttribPointer(UV_ATTRIB_INDEX, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
	if (m_bufferType&NORM)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, m_normals.size()*sizeof(float), &m_normals[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(NORMAL_ATTRIB_INDEX);
		glVertexAttribPointer(NORMAL_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size()*sizeof(uint), &m_indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

bool Mesh::IndexObj(std::vector<vec3> &p_vertices, std::vector<vec2> &p_uvs, std::vector<vec3> &p_normals,
	std::vector<uint> &p_vertIndices, std::vector<uint> &p_uvIndices, std::vector<uint> &p_normIndices)
{
	std::map<vec3, uint, vec3Comparison> objMap;
	if (p_vertIndices.size() != p_uvIndices.size() || p_uvIndices.size() != p_normIndices.size())
	{
		fprintf(stderr, "Cannot read .obj file, try different export settings.");
		return false;
	}

	vec3 indexVec;
	for (uint i = 0; i < p_vertIndices.size(); i++)
	{
		indexVec = vec3(p_vertIndices[i], p_uvIndices[i], p_normIndices[i]);
		if (objMap.find(indexVec) == objMap.end())
		{
			objMap[indexVec] = m_numVertices;
			m_numVertices++;
			m_vertices.push_back(p_vertices[p_vertIndices[i]-1].x);
			m_vertices.push_back(p_vertices[p_vertIndices[i]-1].y);
			m_vertices.push_back(p_vertices[p_vertIndices[i]-1].z);

			m_uvs.push_back(p_uvs[p_uvIndices[i]-1].x);
			m_uvs.push_back(p_uvs[p_uvIndices[i]-1].y);

			m_normals.push_back(p_normals[p_normIndices[i]-1].x);
			m_normals.push_back(p_normals[p_normIndices[i]-1].y);
			m_normals.push_back(p_normals[p_normIndices[i]-1].z);
		}
		
		m_indices.push_back(objMap[indexVec]);

	}
	return true;
}

vec3 Mesh::TruncateVector(const vec3& v)
{
	vec3 returnV = vec3();
	returnV.x = std::trunc(100000 * v.x) / 100000;
	returnV.y = std::trunc(100000 * v.y) / 100000;
	returnV.z = std::trunc(100000 * v.z) / 100000;
	return returnV;
}
