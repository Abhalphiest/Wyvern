#ifndef _MESHMASTER_H
#define _MESHMASTER_H

#include"Mesh.h"
#include<map>
struct MeshData{
	uint numInstances = 0;
	std::vector<mat4> localToWorld; //transformation matrices per instance

	//constructor
	MeshData(void);
	MeshData(MeshData& other);
	MeshData& operator=(MeshData& other);
	~MeshData(void);

	//need an array of floats for shaders
	void GetMatArray(float* arrayDest);
};
class MeshMaster{

	int numMeshes; //number of meshes in the render list
	static MeshMaster* instance; //singleton
	std::vector<Mesh*> meshList;
	std::vector<MeshData*> mDataList;
	float* floatMatrices; //list of matrices to render in float form
	std::map<String, int> m_map; //objects in the list

public:
	//singleton functions
	static MeshMaster* GetInstance();
	static void Release(void);

	//render list functions
	uint AddMesh(Mesh* mesh); //adds a new mesh to the mesh list, returns index

	Mesh* GetMesh(String name); //gets the mesh associated with a given name

	Mesh* GetMesh(uint index); //gets mesh associated with given index

	void AddToRenderList(Mesh* mesh, mat4& toWorld);
	void AddToRenderList(uint index, mat4& toWorld);
	void Render(void);

private:
	//constructor, copy constructor, destructor, etc
	MeshMaster(void);
	MeshMaster(MeshMaster const& other);
	MeshMaster& operator=(MeshMaster const& other);
	~MeshMaster(void);

	uint findMesh(Mesh* mesh); //finds the index of the given mesh

	void Init(void);
	void ResetList(void);



};

#endif