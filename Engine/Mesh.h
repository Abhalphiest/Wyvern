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
	bool m_isBound = false; //is it bound?
	bool m_wireframe = false; //draw it in wireframe?
	uint m_numVertices = 0; 
	uint m_materialIndex; 
	
	GLuint m_vao = 0; //vertex array object index
	GLuint m_vertexBuffer = 0; //vertex buffer index
	GLuint m_colorBuffer = 0; //color  buffer index
	GLuint m_uvBuffer = 0; //UV buffer index
	GLuint m_tangentBuffer = 0;
	GLuint m_binormalBuffer = 0;
	GLuint m_shaderIndex = 0;
	GLuint m_ogShaderIndex = 0; //for the original shader


	CameraMaster* m_camera = nullptr;
	MaterialMaster* m_material = nullptr;
	LightMaster* m_light = nullptr;
	ShaderMaster* m_shader = nullptr;

	char* m_name = '\0'; //empty string for uninitialized name
	

public:
	Mesh(void); //constructor
	String GetName(void){ return m_name; }

private:


};
#endif