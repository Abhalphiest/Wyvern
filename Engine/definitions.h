#ifndef _def_h_
#define _def_h_

//all our headers
#include<stdlib.h>
#include<crtdbg.h> //for tracking memory leaks
#include<Windows.h> //can't honestly remember why I wanted this, I'll take it out later and see if anything explodes
#include"GL\glew.h" //needs to go first
#include<GL\GLU.h>  //openGL libraries
#include<GL\GL.h>
#include"glfw3.h" //for windowing and input
#include<Windows.h>
#include<iostream>
#include<stdio.h>
#include<string>
#include<algorithm>
#include<assert.h>
#include<math.h>
#include<vector>
#include<locale>
#include<fstream>
#include<sstream>
#include"include/glm/glm.hpp"

typedef std::string String;
typedef unsigned int uint;

//reimplementation of glm classes
//for my own education
//class vector2{

//};
//class vector3{
	//private:
		//float x, y, z;

	//public:
		//vector3(GLfloat x, GLfloat y, GLfloat z); //standard constructor, componentwise

//};
//class vector4{

//};
//class matrix4{
//private:
	//int elements [16];
//};
//class quaternion{

//};

//typedefs for easy replacement later
typedef glm::mat4 mat4;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::mat3 mat3;

#define SafeDelete(p){if(p){delete p; p = nullptr;}} //so we won't try to delete a null pointer in the chaos that is our program

//constants

//waste of time to continually recalculate common trigonometric values, might as well just have em
#define PI 3.1415926535897932384626433832795028841971693993751058
#define HALF_PI 1.5707963267948966192313216916397514420985846996875529
#define QUARTER_PI 0.7853981633974483096156608458198757210492923498437764
#define TWO_PI 6.2831853071795864769252867665590057683943387987502116

//colors
#define BLACK vector3(0.0f, 0.0f, 0.0f)
#define WHITE vector3(1.0f, 1.0f, 1.0f)
#define GREY  vector3(.5f, .5f, .5f)

#define RED vector3(1.0f, 0.0f, 0.0f)
#define GREEN vector3(0.0f, 1.0f, 0.0f)
#define BLUE vector3(0.0f, 0.0f, 1.0f)

#define ZEROVECTOR vector3(0.0f,0.0f,0.0f)
#define XAXIS vector3(1.0f, 0.0f, 0.0f)
#define YAXIS vector3(0.0f, 1.0f, 0.0f)
#define ZAXIS vector3(0.0f, 0.0f, 1.0f)

//Enums

enum OPTIONS
{
	NO = 0,
	YES = 1
};

enum CAMERAMODE
{
	PERSPECTIVE = 0,
	ORTHOGONALX = 1,
	ORTHOGONALY = 2,
	ORTHOGONALZ = 3
};

#endif
