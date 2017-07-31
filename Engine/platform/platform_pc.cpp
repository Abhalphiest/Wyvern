
#include "platform.h"

#ifdef PLATFORM_WINDOWS_64
#include"platform_definitions_pc.h"
#include"window.h"

//globals
s_platform_globals g_platform_globals;

void platform_init()
{
	//NOTE: May cause unexpected behavior if/when the engine is compiled into a DLL
	// keep an eye on this!
	g_platform_globals.hInstance = GetModuleHandle(NULL); 
	window_system_init();
	s_window_params params = { "Test Window", 80, 80, 800, 400, NULL };
	make_window(&params, window_filler_option);
	
}

bool platform_update()
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

void platform_exit()
{
	exit(0);
}
#endif

