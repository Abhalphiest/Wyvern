#include"CameraMaster.h"
CameraMaster* CameraMaster::m_instance = nullptr;

//singleton functions
CameraMaster* CameraMaster::GetInstance(void)
{
	if (m_instance == nullptr)
	{
		m_instance = new CameraMaster();
	}
	return m_instance;
}

void CameraMaster::ReleaseInstance(void)
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

//constructor
CameraMaster::CameraMaster(void)
{
	m_windowMaster = WindowMaster::GetInstance();//do this first!
	m_cameras = std::vector<Camera*>(); //automatic variable, no new keyword
	uint cameraid = createCamera(vec4(0.0f, 0.0f, -10.0f, 1.0f), vec3(0.0f), vec3(0.0f,1.0f,0.0f), PERSPECTIVE, 45.0f, .01f, 100.0f); //default camera to start with
	bindCamera(cameraid);
	
}
//copy constructor
CameraMaster::CameraMaster(const CameraMaster& other)
{
	m_cameras = std::vector<Camera*>(); //automatic variable, no new keyword
	for (uint i = 0; i < other.m_cameras.size(); i++)
	{
		m_cameras.push_back(m_cameras[i]); //because this is a singleton and we only want one instance anyways
											//it's okay to just give them the exact same pointers instead of deep copying
	}										//or at least that's what I think at the moment
	m_currentCamera = other.m_currentCamera;
	m_windowMaster = other.m_windowMaster;
}
//assignment operator
CameraMaster& CameraMaster::operator=(const CameraMaster& other)
{
	if (this != &other)
	{
		for (uint i = 0; i < m_cameras.size(); i++)
		{
			
			if (m_cameras[i] != nullptr)
			{
				_aligned_free(m_cameras[i]);
				m_cameras[i] = nullptr;
			}
		}
		m_cameras.clear(); //clear does not delete for us, so we needed to delete first
		for (uint i = 0; i < other.m_cameras.size(); i++)
		{
			m_cameras.push_back(m_cameras[i]); //because this is a singleton and we only want one instance anyways
			//it's okay to just give them the exact same pointers instead of deep copying
		}										//or at least that's what I think at the moment
		m_currentCamera = other.m_currentCamera;
		m_windowMaster = other.m_windowMaster;
	}
	return *this;
}
//destructor
CameraMaster::~CameraMaster(void)
{
	for (uint i = 0; i < m_cameras.size(); i++)
	{
		if (m_cameras[i] != nullptr)
		{
			_aligned_free(m_cameras[i]);
			m_cameras[i] = nullptr;
		}
	}
}

//setter implementation
void CameraMaster::SetCameraMode(CameraMode p_mode)
{
	if (m_currentCamera != -1 && m_cameras[m_currentCamera]->m_mode != p_mode)
	{
		m_cameras[m_currentCamera]->m_mode = p_mode;
		Update();
	}
}

void CameraMaster::Update()
{
	Camera* camera = m_cameras[m_currentCamera];
	switch (camera->m_mode)
	{
	case PERSPECTIVE:
	{
		camera->m_viewMatrix = glm::lookAt((vec3)camera->m_position, camera->m_focalPoint, camera->m_up);
		camera->m_perspMatrix = glm::perspective(camera->m_fov, m_windowMaster->GetWindowRatio(), camera->m_nearClip, camera->m_farClip);
		break;
	}
	case ORTHOGONALX:
	{
		break;
	}
	case ORTHOGONALY:
	{
		break;
	}
	case ORTHOGONALZ:
	{
		break;
	}
	}
}

void CameraMaster::zoomCamera(float p_zoomDistance)
{

}
void CameraMaster::truckCamera(float p_dist, vec3 p_axis)
{

}
void CameraMaster::rotateCamera(float p_angleRad, vec3 p_axis)
{
	mat4 rotation = glm::rotate(glm::degrees(p_angleRad), p_axis);
	Camera*camera = m_cameras[m_currentCamera];
	camera->m_up = (vec3)(rotation*vec4(camera->m_up, 1.0f));
	camera->m_focalPoint = (vec3)(rotation*vec4(camera->m_focalPoint-(vec3)camera->m_position,1.0f))+(vec3)camera->m_position;
	Update();
}
void CameraMaster::orbitCamera(float p_angleRad, vec3 p_axis)
{
	Camera* camera = m_cameras[m_currentCamera];
	vec4 focalSpacePos = vec4((vec3)camera->m_position - camera->m_focalPoint,0.0f);
	mat4 rotation = glm::rotate(glm::degrees(p_angleRad), p_axis);
	vec4 rotated = rotation*focalSpacePos;
	camera->m_position = glm::translate((vec3)(rotated - focalSpacePos))*camera->m_position;
	Update();

}
void CameraMaster::pointCamera(vec3 p_focalPoint)
{
	m_cameras[m_currentCamera]->m_focalPoint = p_focalPoint;
	Update();
}
void CameraMaster::bindCamera(uint p_index)
{
	if (p_index >= 0 && p_index < m_cameras.size())
	{
		m_currentCamera = p_index;
		Update();
	}
}
uint CameraMaster::createCamera(vec4& p_position, vec3& p_focalPoint, vec3 &p_up, CameraMode p_mode, float p_fov, float p_nearClip, float p_farClip)
{
	Camera* newCamera = (Camera*)_aligned_malloc(sizeof(Camera),16);
	newCamera->m_position = p_position;
	newCamera->m_focalPoint = p_focalPoint;
	newCamera->m_up = p_up;
	newCamera->m_mode = p_mode;
	newCamera->m_fov = p_fov;
	newCamera->m_nearClip = p_nearClip;
	newCamera->m_farClip = p_farClip;
	newCamera->m_perspMatrix = mat4(1.0f);
	newCamera->m_perspMatrix = mat4(1.0f); //initialize to identity matrices
	m_cameras.push_back(newCamera);
	return m_cameras.size() - 1; //return our new index

}