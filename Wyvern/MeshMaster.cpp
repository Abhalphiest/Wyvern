#include"MeshMaster.h"
MeshMaster* MeshMaster::m_instance = nullptr;
MeshMaster* MeshMaster::GetInstance(void)
{
	if (m_instance == nullptr)
	{
		m_instance = new MeshMaster();
	}
	return m_instance;
}
void MeshMaster::ReleaseInstance(void)
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}
MeshMaster::MeshMaster(void)
{
	m_renderList = std::vector<MeshData>();
}
MeshMaster::~MeshMaster(void)
{
	m_renderList.clear();
}
MeshMaster& MeshMaster::operator=(const MeshMaster& other)
{
	m_renderList = other.m_renderList;
	m_nameMap = other.m_nameMap;
	return *this;
}
MeshMaster::MeshMaster(const MeshMaster& other)
{
	m_renderList = other.m_renderList;
	m_nameMap = other.m_nameMap;
}
uint MeshMaster::AddMesh(Mesh* p_mesh, String &p_name)
{
	for (uint i = 0; i < m_renderList.size(); i++)
	{
		if (m_renderList[i].m_mesh == p_mesh)
			return i;
	}
	if(m_nameMap.find(p_name)!=m_nameMap.end())
	{
		String temp;
		int i=0;
		while (m_nameMap.find(temp) != m_nameMap.end())
		{
			temp = p_name + std::to_string(i);
			i++;
		}
		p_name = temp;
	}
	p_mesh->SetName(p_name);
	MeshData mdata = MeshData(p_mesh);
	m_renderList.push_back(mdata);
	m_nameMap[p_name] = m_renderList.size() - 1;
	return m_nameMap[p_name];
	
}
Mesh* MeshMaster::GetMesh(uint p_index)
{
	return m_renderList[p_index].m_mesh;
}
Mesh* MeshMaster::GetMesh(String p_name)
{
	if (m_nameMap.find(p_name) != m_nameMap.end())
	{
		uint i = m_nameMap[p_name];
		return m_renderList[i].m_mesh;
	}
	return nullptr;
}
void MeshMaster::ClearMeshes(void)
{
	m_renderList.clear();
}

uint MeshMaster::AddInstance(uint p_index, mat4& p_toWorld)
{
	mat4 toWorld = p_toWorld;
	uint index = m_renderList[p_index].m_numInstances;
	m_renderList[p_index].m_numInstances++;
	m_renderList[p_index].m_toWorld.push_back(toWorld);
	return index;
}
uint MeshMaster::AddInstance(String p_name, mat4& p_toWorld)
{
	if (m_nameMap.find(p_name) != m_nameMap.end())
	{	
		mat4 toWorld = p_toWorld;
		uint i = m_nameMap[p_name];
		uint index = m_renderList[i].m_numInstances;
		m_renderList[i].m_numInstances++;
		m_renderList[i].m_toWorld.push_back(toWorld);
		return index;
	}
	else
	{
		return -1;
	}
}
void MeshMaster::UpdateInstance(uint p_meshIndex, uint p_instanceIndex, mat4& p_toWorld)
{
	mat4 toWorld = p_toWorld;
	m_renderList[p_meshIndex].m_toWorld[p_instanceIndex] = toWorld;
}
void MeshMaster::UpdateInstance(String p_name, uint p_instanceIndex, mat4& p_toWorld)
{
	if (m_nameMap.find(p_name) != m_nameMap.end())
	{
		mat4 toWorld = p_toWorld;
		m_renderList[m_nameMap[p_name]].m_toWorld[p_instanceIndex] = toWorld;
	}
}
void MeshMaster::ClearInstances(uint p_meshIndex)
{
	m_renderList[p_meshIndex].m_toWorld.clear();
	m_renderList[p_meshIndex].m_numInstances = 0;
}
void MeshMaster::ClearInstances(String p_name)
{
	m_renderList[m_nameMap[p_name]].m_toWorld.clear();
	m_renderList[m_nameMap[p_name]].m_numInstances = 0;
}
void MeshMaster::ClearInstances(void)
{
	for (uint i = 0; i < m_renderList.size(); i++)
	{
		m_renderList[i].m_toWorld.clear();
		m_renderList[i].m_numInstances = 0;
	}
}
void MeshMaster::Render(void)
{
	for (uint i = 0; i < m_renderList.size(); i++)
	{
		for (uint j = 0; j < m_renderList[i].m_numInstances; j++)
		{
			m_renderList[i].m_mesh->Render(m_renderList[i].m_toWorld[j]);
			
		}
	}
}

MeshMaster::MeshData::MeshData(Mesh* p_mesh){
	m_mesh = p_mesh;
	m_numInstances = 0;
	m_toWorld = std::vector<mat4>();
}
MeshMaster::MeshData::~MeshData(void)
{
	if (m_mesh != nullptr)
	{
		delete m_mesh;
		m_mesh = nullptr;
	}
	m_toWorld.clear();
}
MeshMaster::MeshData& MeshMaster::MeshData::operator=(const MeshData& other)
{
	if (other.m_mesh != nullptr)
	{
		if (m_mesh != nullptr)
		{
			delete m_mesh;
		}
		m_mesh = new Mesh(*(other.m_mesh));
	}
	else
		m_mesh = nullptr;
	m_toWorld.clear();
	m_mesh = other.m_mesh;
	m_numInstances = other.m_numInstances;
	m_toWorld = other.m_toWorld;
	return *this;
}
MeshMaster::MeshData::MeshData(const MeshData& other)
{
	if (other.m_mesh != nullptr)
	{
		m_mesh = new Mesh(*(other.m_mesh));
	}
	else
		m_mesh = nullptr;
	m_numInstances = other.m_numInstances;
	m_toWorld = other.m_toWorld;
}
