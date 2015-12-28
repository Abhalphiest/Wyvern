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

//constructor
MeshMaster::MeshMaster(void)
{
	m_numRenderMeshes = 0;
	//allocate as automatic variable
	m_meshList = std::vector<Mesh*>();
	m_meshDataList = std::vector<MeshData*>();
	m_map = std::map<String, int>();
	m_floatMatrices = nullptr;
}
//copy constructor
MeshMaster::MeshMaster(MeshMaster const& other)
{
	m_numRenderMeshes = other.m_numRenderMeshes;
	m_floatMatrices = (float*)malloc(sizeof(float)*m_numRenderMeshes);
	memcpy(m_floatMatrices, other.m_floatMatrices, sizeof(float)*m_numRenderMeshes);
	m_meshList = std::vector <Mesh*> ();
	Mesh* temp; //deep copy
	for (uint i = 0; i < other.m_meshList.size(); i++)
	{
		temp = (Mesh*)malloc(sizeof(Mesh));
		memcpy(temp, other.m_meshList[i], sizeof(Mesh));
		m_meshList.push_back(temp);
	}
	m_meshDataList = std::vector<MeshData*>();
	MeshData* tempData; //deep copy
	for (uint i = 0; i < other.m_meshDataList.size(); i++)
	{
		tempData = (MeshData*)malloc(sizeof(MeshData));
		memcpy(tempData, other.m_meshDataList[i], sizeof(MeshData));
		m_meshDataList.push_back(tempData);
	}
	m_map = other.m_map;

}
//assignment operator overload
MeshMaster& MeshMaster::operator=(MeshMaster const& other)
{
	m_numRenderMeshes = other.m_numRenderMeshes;
	m_floatMatrices = (float*)malloc(sizeof(float)*m_numRenderMeshes);
	memcpy(m_floatMatrices, other.m_floatMatrices, sizeof(float)*m_numRenderMeshes);
	m_meshList = std::vector <Mesh*>();
	Mesh* temp; //deep copy
	for (uint i = 0; i < other.m_meshList.size(); i++)
	{
		temp = (Mesh*)malloc(sizeof(Mesh));
		memcpy(temp, other.m_meshList[i], sizeof(Mesh));
		m_meshList.push_back(temp);
	}
	m_meshDataList = std::vector<MeshData*>();
	MeshData* tempData; //deep copy
	for (uint i = 0; i < other.m_meshDataList.size(); i++)
	{
		tempData = (MeshData*)malloc(sizeof(MeshData));
		memcpy(tempData, other.m_meshDataList[i], sizeof(MeshData));
		m_meshDataList.push_back(tempData);
	}
	m_map = other.m_map;
	return *this;
}
//destructor
MeshMaster::~MeshMaster(void)
{
	if (m_floatMatrices != nullptr)
	{
		free(m_floatMatrices);
		m_floatMatrices = nullptr;
	}
	for (uint i = 0; i < m_meshList.size(); i++)
	{
		if (m_meshList[i] != nullptr)
		{
			free(m_meshList[i]);
			m_meshList[i] = nullptr;
		}
	}
	for (uint i = 0; i < m_meshDataList.size(); i++)
	{
		
		if (m_meshDataList[i] != nullptr)
		{
			free(m_meshDataList[i]);
			m_meshDataList[i] = nullptr;
		}
	}
}

uint MeshMaster::AddMesh(Mesh* p_mesh)
{
	if(m_map.find(p_mesh->GetName()) == m_map.end()) //not already added
	{
		uint index = m_meshList.size(); //index on 0
		m_meshList.push_back(p_mesh);
		m_map.insert(std::pair<String,int>(p_mesh->GetName(),index));
		return index;
	}
	else return FindMesh(p_mesh);
}

Mesh* MeshMaster::GetMesh(String p_name)
{
	return nullptr;
}
Mesh* MeshMaster::GetMesh(uint p_index)
{
	return nullptr;
}
void MeshMaster::AddToRenderList(Mesh* p_mesh, mat4& p_toWorld)
{

}
void MeshMaster::AddToRenderList(uint p_index, mat4& p_toWorld)
{

}
void MeshMaster::Render(void)
{

}

int MeshMaster::FindMesh(Mesh* p_mesh)
{
	try
	{
		return m_map.at(p_mesh->GetName());
	}
	catch (std::out_of_range e)
	{
		return -1; //not found
	}
}

void ResetList(void)
{
	
}


//struct functions
MeshData::MeshData(void)
{

}
MeshData::MeshData(MeshData& other)
{

}
MeshData& MeshData::operator=(MeshData& other)
{
	return *this;
}
MeshData::~MeshData(void)
{

}
void MeshData::GetMatArray(float*p_arrayDest)
{

}
