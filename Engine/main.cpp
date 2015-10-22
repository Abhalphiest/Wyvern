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
#include "include/glew.h"
#include<GL/GLU.h>
#include<GL/GL.h>
#include "include/glfw3.h"
//---------------------
//variable declarations
//---------------------

//for window creation
const int windowWidth = 800;
const int windowHeight = 600;
const char* windowString = "Test Window";

//function prototypes
void init();
void update();
//main
int main(int argc, char** argv)
{
  //initialize glfw library and make a window
  glfwInit();
  GLFWwindow* window = glfwCreateWindow(windowWidth,windowHeight, windowString, nullptr, nullptr);
 
  //makes openGL context current for created window
  glfwMakeContextCurrent(window);
  //number of screen updates to wait before swapping buffers
  glfwSwapInterval(1);
 
  //initialize everything else
  init();

  //main loop
  while(!glfwWindowShouldClose(window))
    update();

  glfwTerminate(); //cleanup after we're done
}

//run this once
void init()
{
	
}

//run once a frame
void update()
{

}