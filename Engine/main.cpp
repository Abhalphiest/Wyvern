//Margaret Dorsey
//Rochester Institute of Technology
//main.cpp is going to be our sandbox during development
//
//Currently setting up OPENGL for use and initializing everything
//and testing compilation with g++ and openGL. Most of this stuff will
//be moved out of the main file and put into a master init function once it's ironed out.

//include the libraries
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include"GL\glew.h"
#include<GL\GLU.h>
#include<GL\GL.h>
#include"glfw3.h"
//---------------------
//variable declarations
//---------------------

//for window creation
const int windowWidth = 800;
const int windowHeight = 600;
const char* windowString = "Test Window";
GLFWwindow* window;

//function prototypes
void init();
void update();
//main
int main(int argc, char** argv)
{
  //initialize glfw library and make a window
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW. \n");
		return -1; //exit failure
	}
  window = glfwCreateWindow(windowWidth,windowHeight, windowString, NULL, NULL);
 
  if (window == NULL)
  {
	  fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not compatible with GL 3.3+.");
	  glfwTerminate();
	  return -1;
  }
  //makes openGL context current for created window
  glfwMakeContextCurrent(window); 
  glewExperimental = true;
  if (glewInit() != GLEW_OK) //Initialize GLEW
  {
	  fprintf(stderr, "Failed to initialize GLEW \n");
	  return -1; //exit failure
  }
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); //keyboard input
  //initialize everything else
  init();

  //main loop
  while(!glfwWindowShouldClose(window) && glfwGetKey(window,GLFW_KEY_ESCAPE)!=GLFW_PRESS)
    update();

  glfwTerminate(); //cleanup after we're done
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
	glfwSwapBuffers(window);
	glfwPollEvents();
}