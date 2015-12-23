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
#include"ShaderMaster.h"
//---------------------
//variable declarations
//---------------------

//for window creation
WindowMaster* windowMaster;
ShaderMaster* shaderMaster;

GLuint VertexArrayID;
GLuint vertexbuffer;
//function prototypes
void init();
void update();
//main
int main(int argc, char** argv)
{
  windowMaster = WindowMaster::GetInstance();
  shaderMaster = ShaderMaster::GetInstance();
  glfwSetInputMode(windowMaster->GetWindow(), GLFW_STICKY_KEYS, GL_TRUE); //keyboard input
  //initialize everything else
  init();
  //main loop
  while(!glfwWindowShouldClose(windowMaster->GetWindow()) && glfwGetKey(windowMaster->GetWindow(),GLFW_KEY_ESCAPE)!=GLFW_PRESS)
    update();

  windowMaster->ReleaseInstance();
  shaderMaster->ReleaseInstance();
  _CrtDumpMemoryLeaks();
}

//run this once
void init()
{	
	//create and bind VAO
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f); //cornflower blue, for nostalgia's sake.

	static const GLfloat g_vertex_buffer_data[] = 
	{
		-1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	//hook up our shaders
	shaderMaster->AddShader("vertexshader.glsl", ShaderMaster::VERTEX_SHADER);
	shaderMaster->AddShader("fragmentshader.glsl", ShaderMaster::FRAGMENT_SHADER);
	shaderMaster->LoadProgram();

}

//run once a frame
void update()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderMaster->GetProgramID());
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
	//swap buffers and catch keyboard input
	glfwSwapBuffers(windowMaster->GetWindow());
	glfwPollEvents();
}