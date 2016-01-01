//Margaret Dorsey
//Rochester Institute of Technology
//main.cpp is going to be our sandbox during development
//
//Currently setting up OPENGL for use and initializing everything
//and testing compilation with g++ and openGL. Most of this stuff will
//be moved out of the main file and put into a master init function once it's ironed out.

//include the libraries
#define _CRTDBG_MAP_ALLOC
#include"definitions.h"
#include"WindowMaster.h"
#include"ShaderMaster.h"
#include"InputMaster.h"
#include"CameraMaster.h"
#include"Mesh.h"

//---------------------
//variable declarations
//---------------------

//for window creation
WindowMaster* windowMaster;
ShaderMaster* shaderMaster;
InputMaster* inputMaster;
CameraMaster* cameraMaster;
Mesh* mesh;

mat4 mvp;
GLuint mvp_handle;
GLuint VertexArrayID;
GLuint vertexbuffer;
GLuint colorbuffer;
//function prototypes
void init();
void update();
//main
int main(int argc, char** argv)
{
  windowMaster = WindowMaster::GetInstance();
  shaderMaster = ShaderMaster::GetInstance();
  inputMaster = InputMaster::GetInstance();
  cameraMaster = CameraMaster::GetInstance();
  //initialize everything else
  init();
  //main loop
  while(!glfwWindowShouldClose(windowMaster->GetWindow()) && glfwGetKey(windowMaster->GetWindow(),GLFW_KEY_ESCAPE)!=GLFW_PRESS)
    update();

  windowMaster->ReleaseInstance();
  shaderMaster->ReleaseInstance();
  inputMaster->ReleaseInstance();
  cameraMaster->ReleaseInstance();
  delete mesh;
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
	shaderMaster->AddShader("vertexshader.glsl", ShaderMaster::VERTEX_SHADER);
	shaderMaster->AddShader("fragmentshader.glsl", ShaderMaster::FRAGMENT_SHADER);
	shaderMaster->LoadProgram();

	mesh = Mesh::Torus(3.0f, 5.0f, 60);
	mesh->SetWireframe(true);
	

	


}

//run once a frame
void update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mesh->Render(mat4(1.0f));
	
	//swap buffers and catch keyboard input
	glfwSwapBuffers(windowMaster->GetWindow());
	glfwPollEvents();
}