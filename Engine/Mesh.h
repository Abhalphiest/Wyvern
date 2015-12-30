//Margaret Dorsey
//10/21/2015

#ifndef _MESH_H_
#define _MESH_H_

#include"definitions.h"
#include"ShaderMaster.h"
#include"CameraMaster.h"
#include"MaterialMaster.h"
#include"LightMaster.h"


class Mesh
{
protected:
	uint m_numVertices = 0; 
	uint m_materialIndex; 
	GLuint m_vao = 0; //vertex array object index
	GLuint m_indexBuffer = 0;
	GLuint m_vertexBuffer = 0; //vertex buffer index
	GLuint m_colorBuffer = 0; //color  buffer index
	GLuint m_uvBuffer = 0; //UV buffer index
	GLuint m_tangentBuffer = 0;
	GLuint m_bitangentBuffer = 0;
	GLuint m_shaderIndex = 0;


	CameraMaster* m_cameraMaster = nullptr;
	MaterialMaster* m_materialMaster = nullptr;
	LightMaster* m_lightMaster = nullptr;
	ShaderMaster* m_shaderMaster = nullptr;

	char* m_name = '\0'; //empty string for uninitialized name
	

public:
	
	static Mesh* Cube(float size);
	static Mesh* Sphere();
	static Mesh* Torus();
	static Mesh* Cone(float radius, float height, uint subdivisions);
	static Mesh* Cylinder(float radius, float height, uint subdivisions);
	String GetName(void){ return m_name; }
	void Render(mat4 &p_modelMatrix);
	~Mesh(void); //destructor
	Mesh& operator=(Mesh& other); //assignment operator
	Mesh(Mesh& other); //copy constructor

private:
	Mesh(void); //constructor

};
#endif