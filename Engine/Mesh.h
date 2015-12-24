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
	bool isBound = false; //is it bound?
	bool isCopy = false; //is this a copy?
	bool wireframe = false; //draw it in wireframe?
	GLuint numVertices = 0; //better to use the GL unsigned ints, for portability's sake
	GLuint materialIndex; 
	
	GLuint vao = 0; //vertex array object index
	GLuint vertexBuffer = 0; //vertex buffer index
	GLuint colorBuffer = 0; //color  buffer index
	GLuint UVBuffer = 0; //UV buffer index
	GLuint tangentBuffer = 0;
	GLuint binormalBuffer = 0;
	GLuint shaderIndex = 0;
	GLuint ogShaderIndex = 0; //for the original shader

	mat4 m_toWorld;
	mat4 m_modelMatrix;
	vec4 m_position;
	quaternion m_orientation;

	CameraMaster* camera = nullptr;
	MaterialMaster* material = nullptr;
	LightMaster* light = nullptr;
	ShaderMaster* shader = nullptr;

	char* name = '\0'; //empty string for uninitialized name
	

public:
	Mesh(void); //constructor

private:


};
#endif