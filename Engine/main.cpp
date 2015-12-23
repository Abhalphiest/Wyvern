//Margaret Dorsey
//Rochester Institute of Technology
//main.cpp is going to be our sandbox during development
//
//Currently setting up OPENGL for use and initializing everything
//and testing compilation with g++ and openGL. Most of this stuff will
//be moved out of the main file and put into a master init function once it's ironed out.

//include the libraries
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>
#include<stdio.h>
#include<Windows.h>
#include"GL\glew.h"
#include<GL\GLU.h>
#include<GL\GL.h>
#include"glfw3.h"
#include"WindowMaster.h"
//---------------------
//variable declarations
//---------------------

//for window creation
const int windowWidth = 800;
const int windowHeight = 600;
const char* windowString = "Test Window";
WindowMaster* windowMaster;

//function prototypes
void init();
void update();
//main
int main(int argc, char** argv)
{
  windowMaster = WindowMaster::GetInstance();
  glfwSetInputMode(windowMaster->GetWindow(), GLFW_STICKY_KEYS, GL_TRUE); //keyboard input
  //initialize everything else
  _CrtSetBreakAlloc(155);
  init();
  //main loop
  while(!glfwWindowShouldClose(windowMaster->GetWindow()) && glfwGetKey(windowMaster->GetWindow(),GLFW_KEY_ESCAPE)!=GLFW_PRESS)
    update();

  windowMaster->ReleaseInstance();
  _CrtDumpMemoryLeaks();
}

//run this once
void init()
{	
	
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f); //cornflower blue, for nostalgia's sake.
}

//run once a frame
void update()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//swap buffers and catch keyboard input
	glfwSwapBuffers(windowMaster->GetWindow());
	glfwPollEvents();
}