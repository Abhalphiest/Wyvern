#ifndef _MESHMASTER_H
#define _MESHMASTER_H
#include"definitions.h"
#include"Mesh.h"
class MeshMaster
{
	struct MeshData
	{
		Mesh* m_mesh;
		uint m_numInstances;
		std::vector<mat4> m_toWorld;

		MeshData(Mesh* p_mesh); //constructor
		~MeshData(void); //destructor
		MeshData& operator=(const MeshData& other); //assignment operator
		MeshData(const MeshData& other); //copy constructor
	};
public:
	//singleton functions
	MeshMaster* GetInstance(void);
	void Release(void);

	uint AddMesh(Mesh* p_mesh, String &p_name);
	Mesh* GetMesh(uint p_index);
	Mesh* GetMesh(String p_name);
	void ClearMeshes(void);
	uint AddInstance(uint p_index, mat4& p_toWorld);
	uint AddInstance(String p_name, mat4& p_toWorld);
	void UpdateInstance(uint p_meshIndex, uint p_instanceIndex, mat4& p_toWorld);
	void UpdateInstance(String p_name, uint p_instanceIndex, mat4& p_toWorld);
	void ClearInstances(uint p_meshIndex);
	void ClearInstances(String p_name);
	void ClearInstances(void);
	void Render(void);
	
private:
	MeshMaster(void); //constructor
	~MeshMaster(void); //destructor
	MeshMaster& operator=(const MeshMaster& other);
	MeshMaster(const MeshMaster& other);

	static MeshMaster* m_instance; //singleton pointer
	std::vector<MeshData> m_renderList;
	std::map<String, uint> m_nameMap;

	
	
	
};

#endif