#ifndef _OBJECT_H_
#define _OBJECT_H_

#include"definitions.h"
#include"ShaderMaster.h"
#include"CameraMaster.h"
#include"MaterialMaster.h"
#include"LightMaster.h"
///The object class is meant to be the end user of the engine's primary pathway into the control of an onscreen object
///It is much more "intuitive" and hides the functionality of many of the master interactions and index maintenance inherent in such
///an object.
///<summary>
///
///</summary>
class Object{
public:
	static Object& PrimitiveCube(float p_size, String p_name, uint p_materialIndex);
	static Object& PrimitiveSphere(float p_radius, uint p_subdivisions, String p_name, uint p_materialIndex);
	static Object& PrimitiveTorus(float p_innerRadius, float p_outerRadius, uint p_subdivisions, String p_name, uint p_materialIndex);
	static Object& PrimitivePipe(float p_innerRadius, float p_outerRadius, float p_height, uint p_subdivisions, String p_name, uint p_materialIndex);
	static Object& PrimitiveCylinder(float p_radius, float p_height, uint p_subdivisions, String p_name, uint p_materialIndex);
	static Object& PrimitiveCone(float p_radius, float p_height, uint p_subdivisions, String p_name, uint p_materialIndex);
	static Object& PrimitivePlane(float p_width, float p_height, String p_name, uint p_materialIndex);
	static Object& PrimitiveIcosphere(float p_radius, uint p_subdivisions, String p_name, uint p_materialIndex);
	static Object& MeshObject(char* m_meshPath, String p_name, uint p_materialIndex);


	void SetPosition(vec3 p_position){ m_position = p_position;}
	void SetOrientation(quaternion p_orientation){ m_orientation = p_orientation; }
	void SetVelocity(vec3 p_velocity){ m_velocity = p_velocity;}
	void SetAcceleration(vec3 p_acceleration){ m_acceleration = p_acceleration;}
	vec3 GetPosition(void){ return m_position;}
	quaternion GetOrientation(void){ return m_orientation;}
	vec3 GetVelocity(void){ return m_velocity;}
	vec3 GetAcceleration(void){ return m_acceleration;}
	vec3 GetForwardVector(void){ return m_forward;}
	vec3 GetUpVector(void){ return m_up;}
	vec3 GetRightVector(void){ return m_right;}

	void Rotate(quaternion p_rotation, float p_seconds);
	void Rotate(quaternion p_rotation, uint p_frames);
	void Rotate(vec3 p_axis, float p_angleRad, float p_seconds);
	void Rotate(vec3 p_axis, float p_angleRad, uint p_frames);
	void Translate(vec3 p_vector, float p_seconds);
	void Translate(vec3 p_vector, uint p_frames);
	void Scale(vec3 p_scaleVec, float p_seconds);
	void Scale(vec3 p_scaleVec, uint p_frames);
	void Scale(float p_scaleFac, float p_seconds);
	void Scale(float p_scaleFac, uint p_frames);



private:
	Object(void);
	vec3 m_position;
	vec3 m_forward;
	vec3 m_right;
	vec3 m_up;
	vec3 m_scale;
	quaternion m_orientation;
	vec3 m_velocity;
	vec3 m_acceleration;

	mat4 m_modelMatrix;

	uint m_meshID;
	uint m_materialID;

};
#endif