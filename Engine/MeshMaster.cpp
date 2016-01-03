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
void MeshMaster::Release(void)
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}
MeshMaster::MeshMaster(void)
{

}
MeshMaster::~MeshMaster(void)
{

}
MeshMaster& MeshMaster::operator=(MeshMaster& other)
{
	return *this;
}
MeshMaster::MeshMaster(MeshMaster& other)
{

}
uint MeshMaster::AddMesh(Mesh* p_mesh, String p_name)
{
	return 0;
}
void MeshMaster::RemoveMesh(uint p_index)
{

}
uint MeshMaster::AddInstance(uint p_index, mat4& p_toWorld)
{
	return 0;
}
void MeshMaster::UpdateInstance(uint p_meshIndex, uint p_instanceIndex, mat4& p_toWorld)
{

}
void MeshMaster::RemoveInstance(uint p_meshIndex, uint p_instanceIndex)
{

}
void MeshMaster::Render(void)
{

}

MeshMaster::MeshData::MeshData(Mesh* mesh){

}
MeshMaster::MeshData::~MeshData(void)
{

}
MeshMaster::MeshData& MeshMaster::MeshData::operator=(MeshData& other)
{
	return *this;
}
MeshMaster::MeshData::MeshData(MeshData& other)
{

}
