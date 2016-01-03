#ifndef _CAMERAMASTER_H
#define _CAMERAMASTER_H
#include "definitions.h"
#include "WindowMaster.h"

///<summary>The Camera Master is a singleton that handles all cameras, 
//switching between them, and the calculation of the view and perspective matrices.</summary>
class CameraMaster{

public:
	///<summary> Camera Mode denotes the type of camera - Perspective or Orthographic.
	///</summary>
	enum CameraMode
	{
		PERSPECTIVE = 0,
		ORTHOGRAPHIC = 1
	};

#pragma region Singleton Functions
	///<summary> Gets the Camera Master singleton </summary>
	///<returns> A pointer to the Camera Master singleton object </returns>
	///<remark>GetInstance is the only place where the CameraMaster constructor will ever be called.</remark>
	static CameraMaster* GetInstance(void);
	///<summary> Destroys the CameraMaster singleton </summary>
	///<remark>ReleaseInstance is the only place where the CameraMaster destructor will ever be called.</remark>
	static void ReleaseInstance(void);
#pragma endregion 

#pragma region Camera Movement Functions
	///<summary> Moves the camera towards or away its focal point without changing orientation, equivalent to "zooming" in or out </summary>
	///<param name="p_zoomDistance"> The displacement in world coordinates of the camera. Negative values result in "zooming out" </param>
	void zoomCamera(float p_zoomDistance);
	///<summary> Moves the camera along the given vector by the given magnitude, similar to a truck in film. Equivalent to translation. </summary>
	///<param name="p_dist"> The magnitude of the translation of the camera - negative values will result in moving in the opposite direction </param>
	///<param name="p_axis"> The vector along which the camera will move, or the axis of translation. Normalize for predictable results. </param>
	void truckCamera(float p_dist, vec3 p_axis); 
	///<summary> Rotates the entire camera along the given axis by the given angle. </summary>
	///<param name="p_dist"> The desired rotation angle in radians around the axis. </param>
	///<param name="p_axis"> The axis around which to rotate, recommended normalized. </param>
	void rotateCamera(float p_angleRad, vec3 p_axis);
	///<summary>Moves the camera around its focal point, like a planet orbiting the sun. </summary>
	///<param name="p_angleRad"> The angle, in radians, to rotate through around the axis.  </param>
	///<param name="p_axis"> The axis around which the camera will rotate. A normalized vector is recommended. </param>
	void orbitCamera(float p_angleRad, vec3 p_axis); 
	///<summary> Changes the orientation of the camera by choosing a new center of the screen, rather than by arbitrary rotation. </summary>
	///<param name="p_focalPoint"> The new focal point of the camera, in world coordinates. </param>
	void pointCamera(vec3 p_focalPoint); 
	///<summary> Sets the camera that is currently being rendered and manipulated. </summary>
	///<param name="p_index"> The index of the camera to be bound </param>
	void bindCamera(uint p_index);
	///<summary>
	///Creates a new camera
	///</summary>
	///<param name="p_position"> The position of the camera in world coordinates. </param>
	///<param name="p_focalPoint"> What the camera is pointing at, or alternatively the center of the screen when using the camera. World Coordinates. </param>
	///<param name="p_up">The up vector of the new camera in world coordinates </param>
	///<param name="p_mode">The Camera Mode of the new camera - PERSPECTIVE or ORTHOGRAPHIC </param>
	///<param name="p_fov">The field of view of the new camera, in radians </param>
	///<param name="p_nearClip">The near clipping plane of the new camera </param>
	///<param name="p_farClip"> The far clipping plane of the new camera </param>
	///<returns> The index of the camera, to be used in binding.</returns>
	///<remark> Creating the camera does not bind the camera. The camera must be bound to be used. </remark>
	uint createCamera(vec4& p_position, vec3& p_focalPoint, vec3 &p_up, CameraMode p_mode, float p_fov, float p_nearClip, float p_farClip);
#pragma endregion	

#pragma region Properties
	///<summary> View Matrix property </summary>
	///<returns> A 4x4 matrix representing the view transformation from the currently bound camera </returns>
	mat4 GetViewMatrix(void){ return m_cameras[m_currentCamera]->m_viewMatrix; }
	///<summary> Perspective Matrix property </summary>
	///<returns> A 4x4 matrix representing the perspective transformation from the currently bound camera </returns>
	mat4 GetPerspMatrix(void){ return m_cameras[m_currentCamera]->m_perspMatrix; }
	///<summary> Camera Mode property </summary>
	///<returns> The mode of the currently bound camera </returns>
	CameraMode GetCameraMode(void){	return m_cameras[m_currentCamera]->m_mode;}
	///<summary> Current Camera property </summary>
	///<returns> The index of the currently bound camera </returns>
	uint GetCurrentCamera(void){ return m_currentCamera; }
	
	///<summary> Camera Mode property </summary>
	///<param name="p_mode"> The new mode of the camera </param>
	void SetCameraMode(CameraMode p_mode);
	///<summary>Near clipping plane property </summary>
	///<param name="p_mode"> The new near clipping distance of the camera. </param>
	void SetNearClipping(float p_nearclip){ m_cameras[m_currentCamera]->m_nearClip= p_nearclip; Update(); }
	///<summary>Far clipping plane property </summary>
	///<param name="p_mode"> The new far clipping distance of the camera. </param>
	void SetFarClipping(float p_farclip){ m_cameras[m_currentCamera]->m_nearClip = p_farclip; Update(); }
	///<summary>Field of view property </summary>
	///<param name="p_mode"> The new field of view angle of the camera, in radians. </param>
	void SetFOV(float p_fovRad){ m_cameras[m_currentCamera]->m_fov = p_fovRad; Update(); }

#pragma endregion
private:

	///<summary> Contains all the data necessary to simulate a camera through view and perspective transformations </summary>
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

	///<summary> Camera Master constructor </summary>
	CameraMaster(void);
	///<summary>Camera Master copy constructor </summary>
	CameraMaster(const CameraMaster& other);
	///<summary> Camera Master assignment operator </summary>
	CameraMaster& operator=(const CameraMaster& other);
	///<summary> Camera Master Destructor </summary>
	~CameraMaster(void);

	///<summary> Updates the view and perspective matrices based on new changes. </summary>
	///<remark> Update is called every time a relevant change is made elsewhere in the camera master, but that is not necessarily every frame or timestep. </remark>
	void Update(void); 
	typedef struct Camera Camera;
};
#endif