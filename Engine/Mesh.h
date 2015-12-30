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

public:
	
	static Mesh* Cube(float p_size);
	static Mesh* Sphere(float p_radius, uint p_subdivisions);
	static Mesh* Torus(float p_innerRad, float p_outerRad, uint p_subdivisions);
	static Mesh* Cone(float p_radius, float p_height, uint p_subdivisions);
	static Mesh* Cylinder(float p_radius, float p_height, uint p_subdivisions);
	String GetName(void){ return m_name; }
	void Render(mat4 &p_modelMatrix);
	~Mesh(void); //destructor
	Mesh& operator=(Mesh& other); //assignment operator
	Mesh(Mesh& other); //copy constructor
	void SetWireframe(bool p_wireframe){ m_renderWireframe = p_wireframe; }

private:
	Mesh(void); //constructor
	void AddQuad(vec3 &p1, vec3 &p2, vec3 &p3, vec3 &p4);
	void AddTri(vec3 &p1, vec3 &p2, vec3 &p3);
	void CheckVertex(vec3 &p);
	void CompileMesh(void);
	void CompileMesh(vec3 color);
	vec3 TruncateVector(const vec3& v);
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
	std::vector<float> m_vertices;
	std::vector<uint> m_indices;
	std::map<vec3, int, vec3Comparison> m_indexMap;

	bool m_renderWireframe = false;

	CameraMaster* m_cameraMaster = nullptr;
	MaterialMaster* m_materialMaster = nullptr;
	LightMaster* m_lightMaster = nullptr;
	ShaderMaster* m_shaderMaster = nullptr;

	char* m_name = '\0'; //empty string for uninitialized name

};
#endif