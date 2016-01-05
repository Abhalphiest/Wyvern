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

	/*mesh = Mesh::Sphere(3.0f, 10);
	
	String sphereName = "sphere";
	meshMaster->AddMesh(mesh, sphereName);
	Mesh* cube = Mesh::Cube(1.0f);
	fprintf(stdout, "%X",cube);
	String cubeName = "cube";
	meshMaster->AddMesh(cube, cubeName);
	uint cubeinst1 = meshMaster->AddInstance(cubeName,glm::translate(vec3(-5.0f,0.0f,0.0f)));
	uint sphereinst1 = meshMaster->AddInstance(sphereName, mat4(1.0f));*/
	
	mesh = Mesh::LoadObj("test.obj");
	if (mesh != nullptr)
	{
		String meshName = "suzanne";
		meshMaster->AddMesh(mesh, meshName);
		uint meshinst1 = meshMaster->AddInstance(meshName, mat4(1.0f));
		
	}

}

//run once a frame
void update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//meshMaster->Render();
	//swap buffers and catch keyboard input
	meshMaster->Render();
	glfwSwapBuffers(windowMaster->GetWindow());
	glfwPollEvents();
}

GLuint loadBMP(const char* imgpath)
{
	unsigned char header[54]; //bmp files begin with a 54 byte header
	uint dataPos; //position where the actual date begins
	uint width, height;
	uint imageSize; //width*height*3
	//rgb data
	unsigned char* data;
	//open the file
	FILE* file = fopen(imgpath, "rb");
	if (!file){ fprintf(stderr, "Image could not be opened \n"); return false;}
	if (fread(header, 1, 54, file) != 54)
	{
		fprintf(stderr, "Not a correct BMP file \n");
		return false;
	}
	if (header[0] != 'B' || header[1] != 'M')
	{
		fprintf(stderr, "Not a correct BMP file \n");
		return false;
	}
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	//some bmp files are misformatted, guess missing info
	if (imageSize == 0)
	{
		imageSize = width*height * 3;
	}
	if (dataPos = 0)
	{
		dataPos = 54; //start after the bmp header
	}
	data = new unsigned char[imageSize];
	fread(data, 1, imageSize, file);
	fclose(file);

	GLuint textureID;
	glGenTextures(1, &textureID);
	//bind the newly created texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	//give the image to open gl
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return 0;
}