
#include "platform.h"

#ifdef PLATFORM_WINDOWS_64
#include"platform_definitions_pc.h"
#include"window.h"

s_platform_data g_platform_data;

void Platform::InitializePlatform()
{
	//NOTE: May cause unexpected behavior if/when the engine is compiled into a DLL
	// keep an eye on this!
	g_platform_data.hInstance = GetModuleHandle(NULL); 
	Window::InitializeWindowSystem();
	Window::s_window_params params = { "Test Window", 80, 80, 800, 400, NULL };
	Window::MakeWindow(&params, Window::window_filler_option);
	
}

bool Platform::PlatformUpdate()
{
	// this struct holds Windows event messages
	MSG msg;
	bool returnval = true;

	// wait for the next message in the queue, store the result in 'msg'
	if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		// translate keystroke messages into the right format
		TranslateMessage(&msg);

		// send the message to the WindowProc function
		DispatchMessage(&msg);
	}

	if(msg.message == WM_QUIT)
	{
		returnval = false;
	}

	return returnval;

}

void Platform::PlatformExit()
{
	exit(0);
}
#endif

