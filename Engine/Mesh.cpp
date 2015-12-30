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
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableVertexAttribArray(0);

}

Mesh* Mesh::Cube(float size)
{
	Mesh* cube = new Mesh();
	GLfloat g_vertex_buffer_data[] =
	{
		size, -size, -size, // triangle 1 : begin
		-size, -size, size,
		-size, size, size, // triangle 1 : end
		size, size, -size, // triangle 2 : begin
		-size, -size, -size,
		-size, size, -size, // triangle 2 : end
		size, -size, size,
		-size, -size, -size,
		size, -size, -size,
		size, size, -size,
		size, -size, -size,
		-size, -size, -size,
		-size, -size, -size,
		-size, size, size,
		-size, size, -size,
		size, -size, size,
		-size, -size, size,
		-size, -size, -size,
		-size, size, size,
		-size, -size, size,
		size, -size, size,
		size, size, size,
		size, -size, -size,
		size, size, -size,
		size, -size, -size,
		size, size, size,
		size, -size, size,
		size, size, size,
		size, size, -size,
		-size, size, -size,
		size, size, size,
		-size, size, -size,
		-size, size, size,
		size, size, size,
		-size, size, size,
		size, -size, size
	};

	GLfloat g_color_buffer_data[] =
	{
		-1.0f, -1.0f, -1.0f, // triangle 1 : begin
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f, -1.0f, // triangle 2 : begin
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f, // triangle 2 : end
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f
	};

	glBindBuffer(GL_ARRAY_BUFFER, cube->m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, cube->m_colorBuffer); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	return cube;
}