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
}
Mesh::~Mesh(void)
{

}
void Mesh::Render(mat4 &p_modelMatrix)
{
	mat4 persp =m_cameraMaster->GetPerspMatrix();
	mat4 view = m_cameraMaster->GetViewMatrix();
	mat4 mvp = persp*view*p_modelMatrix;
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

}

Mesh* Mesh::Cube(float size)
{
	Mesh* cube = new Mesh();
	float vertices[] = {
		-size/2,size/2,size/2,
		size/2,size/2,size/2,
		-size/2,-size/2,size/2,
		size / 2, -size / 2, size / 2,
		-size / 2, size / 2, -size / 2,
		size / 2, size / 2, -size / 2,
		-size / 2, -size / 2,-size / 2,
		size / 2, -size / 2, -size / 2 };
	uint indices[] = { 0,1,2,2,1,3,1,5,7,1,7,3,7,5,4,4,6,7,3,7,4,0,3,4,0,4,1,1,4,5,3,2,6,3,6,7};

	glBindBuffer(GL_ARRAY_BUFFER, cube->m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, cube->m_colorBuffer); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube->m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
	cube->m_numVertices = sizeof(indices);
	return cube;
}