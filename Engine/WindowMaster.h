#define _CRTDBG_MAP_ALLOC //for tracking memory leaks
#include<stdlib.h>
#include<crtdbg.h> //for tracking memory leaks
#include<Windows.h> //can't honestly remember why I wanted this, I'll take it out later and see if anything explodes
#include"GL\glew.h" //needs to go first
#include<GL\GLU.h>  //openGL libraries
#include<GL\GL.h>
#include"glfw3.h" //for windowing and input
#include "definitions.h" //a bunch of typedefs and whatnot
class WindowMaster{

public:
	static WindowMaster* GetInstance(void); //accessor
	static void ReleaseInstance(void); //release

	//properties
	GLFWwindow* GetWindow(void){ return m_window; }

	void SetWindowFullscreen(bool fullscreen);
	bool IsWindowFullscreen(void){ return m_fullScreen; }

	void SetWindowWidth(uint width);
	uint GetWindowWidth(void){ return m_windowWidth; }

	void SetWindowHeight(uint height);
	uint GetWindowHeight(void){ return m_windowHeight; }

	void SetWindowX(uint x);
	uint GetWindowX(void){ return m_windowX; }

	void SetWindowY(uint y);
	uint SetWindowY(void){ return m_windowY; }

	void SetWindowName(char* nm);
	char* GetWindowName(void){return m_windowName;};

	//returns aspect ratio of the window, or the proportion of the width to the height
	float GetWindowRatio(void){ return (float)m_windowWidth / (float)m_windowHeight; }

private:
	WindowMaster(void); //constructor
	WindowMaster(WindowMaster const& other); //copy constructor
	WindowMaster & operator=(WindowMaster const& other); //copy assignment operator
	~WindowMaster(void); //destructor

	void Release(void); //give up our memory
	int Init(void); //initialize, return value is for error reporting

	bool m_fullScreen = false;
	bool m_borderless = false; //for borderless window

	//window dimensions
	uint m_windowWidth = 1280;
	uint m_windowHeight = 720;
	uint m_windowX = 0;
	uint m_windowY = 0;
	GLFWwindow* m_window = nullptr;
	static WindowMaster* m_instance; //singleton
	//name for the window, 20 character limit
	char* m_windowName;

};