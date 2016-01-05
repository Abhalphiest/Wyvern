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
	m_cameras = std::vector<Camera>(); //automatic variable, no new keyword
	uint cameraid = createCamera(vec4(0.0f, 8.0f, -10.0f, 1.0f), vec3(0.0f), vec3(0.0f,1.0f,0.0f), PERSPECTIVE, 45.0f, .01f, 100.0f); //default camera to start with
	bindCamera(cameraid);
}
//copy constructor
CameraMaster::CameraMaster(const CameraMaster& other)
{
	m_cameras = other.m_cameras;
	m_currentCamera = other.m_currentCamera;
	m_windowMaster = other.m_windowMaster;
}
//assignment operator
CameraMaster& CameraMaster::operator=(const CameraMaster& other)
{
	if (this != &other)
	{
		m_cameras = other.m_cameras;						
		m_currentCamera = other.m_currentCamera;
		m_windowMaster = other.m_windowMaster;
	}
	return *this;
}
//destructor
CameraMaster::~CameraMaster(void)
{
	
}

//setter implementation
void CameraMaster::SetCameraMode(CameraMode p_mode)
{
	if (m_currentCamera != -1 && m_cameras[m_currentCamera].m_mode != p_mode)
	{
		m_cameras[m_currentCamera].m_mode = p_mode;
		Update();
	}
}

void CameraMaster::Update()
{
	Camera camera = m_cameras[m_currentCamera];
	switch (camera.m_mode)
	{
	case PERSPECTIVE:
	{
		camera.m_viewMatrix = glm::lookAt((vec3)camera.m_position, camera.m_focalPoint, camera.m_up);
		camera.m_perspMatrix = glm::perspective(camera.m_fov, m_windowMaster->GetWindowRatio(), camera.m_nearClip, camera.m_farClip);
		break;
	}
	case ORTHOGRAPHIC:
	{
		camera.m_viewMatrix = glm::lookAt((vec3)camera.m_position, camera.m_focalPoint, camera.m_up);
		float distance = (float) (camera.m_focalPoint - (vec3)camera.m_position).length();
		camera.m_perspMatrix = glm::ortho(-distance, distance, -distance, distance);
		break;
	}
	
	}
}

void CameraMaster::zoomCamera(float p_zoomDistance)
{
	Camera camera = m_cameras[m_currentCamera];
	vec3 transVec = glm::normalize(camera.m_focalPoint - (vec3)camera.m_position)*p_zoomDistance;
	camera.m_position = glm::translate(transVec)*camera.m_position;
	Update();
}
void CameraMaster::truckCamera(float p_dist, vec3 p_axis)
{
	vec3 dir = glm::normalize(p_axis);
	Camera camera = m_cameras[m_currentCamera];
	camera.m_position = glm::translate(dir*p_dist)*camera.m_position;
	camera.m_focalPoint =(vec3)( glm::translate(dir*p_dist)*vec4(camera.m_focalPoint, 1.0f));
	Update();
}
void CameraMaster::rotateCamera(float p_angleRad, vec3 p_axis)
{
	quaternion rotation = angleAxis(glm::degrees(p_angleRad), p_axis);
	Camera camera = m_cameras[m_currentCamera];
	camera.m_up = (vec3)(rotation*vec4(camera.m_up, 0.0f));
	camera.m_focalPoint = (vec3)(rotation*vec4(camera.m_focalPoint-(vec3)camera.m_position,0.0f))+(vec3)camera.m_position;
	Update();
}
void CameraMaster::orbitCamera(float p_angleRad, vec3 p_axis)
{
	Camera camera = m_cameras[m_currentCamera];
	quaternion rotation = angleAxis(glm::degrees(p_angleRad), p_axis);
	camera.m_position = vec4(camera.m_focalPoint,0.0f)+rotation*(camera.m_position - vec4(camera.m_focalPoint,0.0f));
	camera.m_up = rotation*camera.m_up;
	Update();

}
void CameraMaster::pointCamera(vec3 p_focalPoint)
{
	m_cameras[m_currentCamera].m_focalPoint = p_focalPoint;
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
	Camera newCamera = Camera();
	newCamera.m_position = p_position;
	newCamera.m_focalPoint = p_focalPoint;
	newCamera.m_up = p_up;
	newCamera.m_mode = p_mode;
	newCamera.m_fov = p_fov;
	newCamera.m_nearClip = p_nearClip;
	newCamera.m_farClip = p_farClip;
	newCamera.m_perspMatrix = mat4(1.0f);
	newCamera.m_perspMatrix = mat4(1.0f); //initialize to identity matrices
	m_cameras.push_back(newCamera);
	return m_cameras.size() - 1; //return our new index

}