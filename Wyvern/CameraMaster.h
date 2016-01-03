#ifndef _CAMERAMASTER_H
#define _CAMERAMASTER_H
#include "definitions.h"
#include "WindowMaster.h"
class CameraMaster{

public:
	enum CameraMode
	{
		PERSPECTIVE = 0,
		ORTHOGONALX = 1,
		ORTHOGONALY = 2,
		ORTHOGONALZ = 3
	};

	
	//singleton functions
	static CameraMaster* GetInstance(void);
	static void ReleaseInstance(void);

	//camera control functions
	void zoomCamera(float p_zoomDistance);
	void truckCamera(float p_dist, vec3 p_axis); //translation
	void rotateCamera(float p_angleRad, vec3 p_axis);
	void orbitCamera(float p_angleRad, vec3 p_axis); //move the camera around its focal point, like a planet orbiting the sun
	void pointCamera(vec3 p_focalPoint); 
	void bindCamera(uint p_index);
	uint createCamera(vec4& p_position, vec3& p_focalPoint, vec3 &p_up, CameraMode p_mode, float p_fov, float p_nearClip, float p_farClip);
	

	//getters
	mat4 GetViewMatrix(void){ return m_cameras[m_currentCamera]->m_viewMatrix; }
	mat4 GetPerspMatrix(void){ return m_cameras[m_currentCamera]->m_perspMatrix; }
	CameraMode GetCameraMode(void){	return m_cameras[m_currentCamera]->m_mode;}
	uint GetCurrentCamera(void){ return m_currentCamera; }
	//setters
	void SetCameraMode(CameraMode p_mode);
	void SetNearClipping(float p_nearclip){ m_cameras[m_currentCamera]->m_nearClip= p_nearclip; Update(); }
	void SetFarClipping(float p_farclip){ m_cameras[m_currentCamera]->m_nearClip = p_farclip; Update(); }
	void SetFOV(float p_fovRad){ m_cameras[m_currentCamera]->m_fov = p_fovRad; Update(); }
private:
	struct Camera
	{
		mat4 m_viewMatrix;
		mat4 m_perspMatrix;
		vec4 m_position;
		vec3 m_focalPoint; //will serve as our orientation along with up, I think this will work okay
		vec3 m_up;
		float m_fov;
		float m_nearClip;
		float m_farClip;
		CameraMode m_mode;	
	};
	static CameraMaster* m_instance;
	std::vector<Camera*> m_cameras; //going to have to memory manage this time
	uint m_currentCamera;

	WindowMaster* m_windowMaster;

	CameraMaster(void);
	CameraMaster(const CameraMaster& other);
	CameraMaster& operator=(const CameraMaster& other);
	~CameraMaster(void);
	void Update(void); //so we only update when something changes
	typedef struct Camera Camera;
};
#endif