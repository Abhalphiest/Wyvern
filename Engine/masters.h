//These are a bunch of singletons, and they'll handle the camera, materials, lights, the window, and shaders.
#ifndef _masters_h_
#define _masters_h_

#include"definitions.h"
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include"GL\glew.h"
#include<GL\GLU.h>
#include<GL\GL.h>
#include"glfw3.h"

class CameraMaster{

};

class MaterialMaster{

};
class LightMaster{

};




class TimeMaster{

	DWORD timerStart = 0;
	DWORD startingTime = 0;
	DWORD lastCalled = 0;

	uint fps = 60; //frames per second
	int frames = 0; //keep track of frames

	std::vector<DWORD> clock; //clock list

public:
	uint GetFPS(void);
	void UpdateTime(void); //update the current time
	void StartClock(uint clock); //starts a time count for the clock at given index
	float TimeDiff(uint clock); //time difference since the last time this method was called for the given clock
	bool Countdown(uint clock,float time, bool repeat); //counts down on the given clock, returns true when count is up

private:
	TimeMaster(void); //constructor
	TimeMaster(TimeMaster const& other); //copy constructor
	TimeMaster & operator=(TimeMaster const& other); //copy assignment operator
	~TimeMaster(void); //destructor

	void Release(void); //give up our memory
	void Init(void); //initialize
};


#include"Mesh.h"
#include<map>
struct MeshData{
	uint numInstances = 0;
	std::vector<matrix4> localToWorld; //transformation matrices per instance

	//constructor
	MeshData(void);
	MeshData(MeshData& other);
	MeshData& operator=(MeshData& other);
	~MeshData(void);

	//need an array of floats for shaders
	void GetMatArray(float* arrayDest);
};
class MeshMaster{

	int numMeshes; //number of meshes in the render list
	static MeshMaster* instance; //singleton
	std::vector<Mesh*> meshList;
	std::vector<MeshData*> mDataList;
	float* floatMatrices; //list of matrices to render in float form
	std::map<String, int> m_map; //objects in the list

public:
	//singleton functions
	static MeshMaster* GetInstance();
	static void Release(void);

	//render list functions
	uint AddMesh(Mesh* mesh); //adds a new mesh to the mesh list, returns index

	Mesh* GetMesh(String name); //gets the mesh associated with a given name

	Mesh* GetMesh(uint index); //gets mesh associated with given index

	void AddToRenderList(Mesh* mesh, matrix4& toWorld);
	void AddToRenderList(uint index, matrix4& toWorld);
	void Render(void);

private:
	//constructor, copy constructor, destructor, etc
	MeshMaster(void);
	MeshMaster(MeshMaster const& other);
	MeshMaster& operator=(MeshMaster const& other);
	~MeshMaster(void);

	uint findMesh(Mesh* mesh); //finds the index of the given mesh

	void Init(void);
	void ResetList(void);
	


};
#endif