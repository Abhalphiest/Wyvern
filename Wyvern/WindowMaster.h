#ifndef _WINDOWMASTER_H
#define _WINDOWMASTER_H

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
	///<summary> Gets the Window Master singleton </summary>
	///<returns> A pointer to the Window Master singleton object </returns>
	///<remark>GetInstance is the only place where the WindowMaster constructor will ever be called.</remark>
	static WindowMaster* GetInstance(void); 
	///<summary> Destroys the WindowMaster singleton </summary>
	///<remark>ReleaseInstance is the only place where the WindowMaster destructor will ever be called.</remark>
	static void ReleaseInstance(void); 

	///<summary>Property for the GLFW window object.</summary>
	///<returns> A pointer to the GLFW window </returns>
	GLFWwindow* GetWindow(void){ return m_window; }

	///<summary>Property for the fullscreen boolean.</summary>
	///<param name="fullscreen"> A boolean value for whether or not the window will be in fullscreen mode. </param>
	void SetWindowFullscreen(bool fullscreen);
	///<summary>Property for the GLFW window object.</summary>
	///<returns> a boolean value representing whether or not the window is fullscreen. </returns>
	bool IsWindowFullscreen(void){ return m_fullScreen; }

	///<summary>Property for the window width.</summary>
	///<param name="width"> The desired width of the window in screen coordinates. </param>
	void SetWindowWidth(uint width);
	///<summary>Property for the window's width.</summary>
	///<returns> The width of the window, in screen coordinates. </returns>
	uint GetWindowWidth(void){ return m_windowWidth; }


	///<summary>Property for the window height.</summary>
	///<param name="height"> The desired height of the window in screen coordinates. </param>
	void SetWindowHeight(uint height);
	///<summary>Property for the window's height.</summary>
	///<returns> The height of the window, in screen coordinates. </returns>
	uint GetWindowHeight(void){ return m_windowHeight; }


	///<summary>Property for the window's x position.</summary>
	///<param name="fullscreen"> The desired x position of the window's top left corner, in screen coordinates with the screen top left corner as origin.</param>
	void SetWindowX(uint x);
	///<summary>Property for the window's x position.</summary>
	///<returns> The x position of the of the window's top left corner, in screen coordinates with the screen top left corner as origin </returns>
	uint GetWindowX(void){ return m_windowX; }


	///<summary>Property for the window's y position.</summary>
	///<param name="y"> The desired x position of the window's top left corner, in screen coordinates with the screen top left corner as origin </param>
	void SetWindowY(uint y);
	///<summary>Property for the window's y position.</summary>
	///<returns> The y position of the of the window's top left corner, in screen coordinates with the screen top left corner as origin </returns>
	uint GetWindowY(void){ return m_windowY; }


	///<summary>Property for the window name.</summary>
	///<param name="fullscreen"> The window name. </param>
	void SetWindowName(String nm);
	///<summary>Property for the window name.</summary>
	///<returns> The window name. </returns>
	String GetWindowName(void){return m_windowName;};

	///<summary>Property for the aspect ratio, primarily for use by the camera.</summary>
	///<returns>the proportion of the width of the window to its height.</returns>
	float GetWindowRatio(void){ return (float)m_windowWidth / (float)m_windowHeight; }

private:
	///<summary> Window Master singleton constructor </summary>
	WindowMaster(void); 
	///<summary> Window Master singleton copy constructor </summary>
	WindowMaster(WindowMaster const& other); 
	///<summary> Window Master singleton assignment operator </summary>
	WindowMaster & operator=(WindowMaster const& other); 
	///<summary> Window Master singleton destructor </summary>
	~WindowMaster(void); 

	bool m_fullScreen = false;
	bool m_borderless = false; //for borderless window

	//window dimensions
	uint m_windowWidth = 1280;
	uint m_windowHeight = 720;
	uint m_windowX = 0;
	uint m_windowY = 0;
	GLFWwindow* m_window = nullptr;
	static WindowMaster* m_instance; //singleton
	String m_windowName; //name for the window

};

#endif