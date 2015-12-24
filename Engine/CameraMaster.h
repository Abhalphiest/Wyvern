#ifndef _CAMERAMASTER_H
#define _CAMERAMASTER_H
#include "definitions.h"
class CameraMaster{
public:
	enum CameraMode
	{
		PERSPECTIVE = 0,
		ORTHOGONALX = 1,
		ORTHOGONALY = 2,
		ORTHOGONALZ = 3
	};
	//singletonfunctions
	static CameraMaster* GetInstance(void);
	static void ReleaseInstance(void);

	//camera control functions
	void zoomCamera(float p_zoomDistance);
	void truckCamera(float p_dist, vec3 p_axis); //translation
	void rotateCamera(float p_angleRad, vec3 p_axis);
	void orbitCamera(float p_angleRad); //move the camera around its focal point, like a planet orbiting the sun
	void pointCamera(vec3 p_focalPoint); 

	//getters
	mat4 GetViewMatrix(void){ return m_viewMatrix; }
	mat4 GetPerspMatrix(void){ return m_perspMatrix; }
	CameraMode GetCameraMode();

	//setters
	void SetCameraMode(CameraMode p_mode);
	void SetNearClipping(float p_nearclip);
	void SetFarClipping(float p_farclip);
private:
	mat4 m_viewMatrix;
	mat4 m_perspMatrix;
	vec4 m_position;
	vec3 m_orientation;
	CameraMaster* m_instance;
	CameraMaster(void);
	CameraMaster(const CameraMaster& other);
	CameraMaster& operator=(const CameraMaster& other);
	CameraMode mode;
};
#endif