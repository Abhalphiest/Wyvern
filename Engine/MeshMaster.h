#ifndef _MESHMASTER_H
#define _MESHMASTER_H

#include"Mesh.h"
#include<map>
struct MeshData{
	uint m_numInstances = 0;
	std::vector<mat4> m_toWorld; //transformation matrices per instance
	//constructor
	MeshData(void);
	MeshData(MeshData& other);
	MeshData& operator=(MeshData& other);
	~MeshData(void);

	//need an array of floats for shaders
	void GetMatArray(float* p_arrayDest);
};
class MeshMaster{

	

public:
	//singleton functions
	static MeshMaster* GetInstance();
	static void Release(void);

	//render list functions
	uint AddMesh(Mesh* p_mesh); //adds a new mesh to the mesh list, returns index

	Mesh* GetMesh(String p_name); //gets the mesh associated with a given name

	Mesh* GetMesh(uint p_index); //gets mesh associated with given index

	void AddToRenderList(Mesh* p_mesh, mat4& p_toWorld);
	void AddToRenderList(uint p_index, mat4& p_toWorld);
	void Render(void);

private:
	//constructor, copy constructor, destructor, etc
	MeshMaster(void);
	MeshMaster(MeshMaster const& other);
	MeshMaster& operator=(MeshMaster const& other);
	~MeshMaster(void);

	int FindMesh(Mesh* p_mesh); //finds the index of the given mesh

	void Init(void);
	void ResetList(void);

	int m_numRenderMeshes; //number of meshes in the render list
	static MeshMaster* m_instance; //singleton
	std::vector<Mesh*> m_meshList;
	std::vector<MeshData*> m_meshDataList;
	float* m_floatMatrices; //list of matrices to render in float form
	std::map<String, int> m_map; //objects in the list


};

#endif