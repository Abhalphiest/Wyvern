//Margaret Dorsey
//Rochester Institute of Technology
//main.cpp is going to be our sandbox during development
//
// Most of this stuff will
//be moved out of the main file and put into a master or class once it's ironed out.

//include the libraries
#define _CRTDBG_MAP_ALLOC
#include"definitions.h"
#include"WindowMaster.h"
#include"ShaderMaster.h"
#include"InputMaster.h"
#include"CameraMaster.h"
#include"MeshMaster.h"
#include"TimeMaster.h"
#include"Mesh.h"

//---------------------
//variable declarations
//---------------------

//for window creation
WindowMaster* windowMaster;
ShaderMaster* shaderMaster;
InputMaster* inputMaster;
CameraMaster* cameraMaster;
MeshMaster* meshMaster;
MaterialMaster* materialMaster;
TimeMaster* timeMaster;
Mesh* mesh;

mat4 mvp;
GLuint mvp_handle;
GLuint VertexArrayID;
GLuint vertexbuffer;
GLuint colorbuffer;
//function prototypes
void init();
void update();
GLuint loadBMP(const char* imgpath);
//main
int main(int argc, char** argv)
{
  windowMaster = WindowMaster::GetInstance();
  shaderMaster = ShaderMaster::GetInstance();
  inputMaster = InputMaster::GetInstance();
  cameraMaster = CameraMaster::GetInstance();
  meshMaster = MeshMaster::GetInstance();
  materialMaster = MaterialMaster::GetInstance();
  timeMaster = TimeMaster::GetInstance();
  //initialize everything else
  init();
  //main loop
  while(!glfwWindowShouldClose(windowMaster->GetWindow()) && glfwGetKey(windowMaster->GetWindow(),GLFW_KEY_ESCAPE)!=GLFW_PRESS)
    update();

  windowMaster->ReleaseInstance();
  shaderMaster->ReleaseInstance();
  inputMaster->ReleaseInstance();
  cameraMaster->ReleaseInstance();
  meshMaster->ReleaseInstance();
  materialMaster->ReleaseInstance();
  timeMaster->ReleaseInstance();
  _CrtDumpMemoryLeaks();
}

//run this once
void init()
{	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f); //cornflower blue, for nostalgia's sake.

	
	

	//hook up our shaders
	uint programindex = shaderMaster->CreateShaderProgram();
	shaderMaster->BindShaderProgram(programindex);
	shaderMaster->AddShader("vertexshader.glsl", ShaderMaster::VERTEX_SHADER);
	shaderMaster->AddShader("fragmentshader.glsl", ShaderMaster::FRAGMENT_SHADER);
	shaderMaster->CompileProgram(programindex);

	
	Mesh* cube = Mesh::Cube(1.0f);
	if (cube != nullptr)
	{
		String cubeName = "cube";
		uint materialIndex;
		materialIndex = materialMaster->CreateMaterial();
		materialMaster->SetMaterialColor(materialIndex, BLUE);
		materialMaster->SetProgramIndex(materialIndex, programindex);
		cube->SetMaterialIndex(materialIndex);
		meshMaster->AddMesh(cube, cubeName);
		uint cubeinst1 = meshMaster->AddInstance(cubeName, glm::translate(vec3(-5.0f, 0.0f, 0.0f)));
	}
	mesh = Mesh::Sphere(1.0f,20);
	if (mesh != nullptr)
	{
		String meshName = "sphere";
		mesh->SetWireframe(true);
		uint materialIndex;
		materialIndex = materialMaster->CreateMaterial();
		materialMaster->SetMaterialColor(materialIndex, RED);
		materialMaster->SetProgramIndex(materialIndex,programindex);
		mesh->SetMaterialIndex(materialIndex);
		meshMaster->AddMesh(mesh, meshName);
		uint meshinst1 = meshMaster->AddInstance(meshName, mat4(1.0f));
		uint meshinst2 = meshMaster->AddInstance(meshName, glm::translate(vec3(1.0, 0, 0)));
		
	}

	Mesh* icosphere = Mesh::Icosphere(2, 2);
	if (icosphere != nullptr)
	{
		icosphere->SetWireframe(true);
		String meshName = "icosphere";
		uint materialIndex = materialMaster->CreateMaterial();
		materialMaster->SetMaterialColor(materialIndex, BLACK);
		materialMaster->SetProgramIndex(materialIndex, programindex);
		icosphere->SetMaterialIndex(materialIndex);
		meshMaster->AddMesh(icosphere, meshName);
		uint meshinst1 = meshMaster->AddInstance(meshName, glm::translate(vec3(6.0,3.0,-2.0)));

	}

}

//run once a frame
void update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//meshMaster->Render();
	//swap buffers and catch keyboard input
	meshMaster->Render();
	timeMaster->UpdateTime();
	//fprintf(stdout, "FPS: %d \n", timeMaster->GetFPS());
	glfwSwapBuffers(windowMaster->GetWindow());
	glfwPollEvents();
}

