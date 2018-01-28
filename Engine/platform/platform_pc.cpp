
#include "platform.h"

#ifdef PLATFORM_WINDOWS_32

#include "platform_definitions_pc.h"
#include "window.h"


void Platform::Initialize()
{

	if(!g_Platform)
	{
		g_Platform = new Platform();
	}
}

Platform::Platform()
{

	// NOTE: May cause unexpected behavior if/when the engine is compiled into a DLL
	// keep an eye on this!
	m_platform_data = new s_platform_data;
	m_platform_data->hInstance = GetModuleHandle(NULL); 

	// make it so we can create windows
	assert(m_platform_data);
	Window::window_system_init(*m_platform_data);

}

void Platform::Release()
{
	if (g_Platform)
	{
		delete g_Platform->m_platform_data;
		g_Platform->m_platform_data = nullptr;
		delete g_Platform;
		g_Platform = nullptr;
	}
}

Platform::~Platform()
{
	// TODO: clean this up!
	exit(0);
}

bool Platform::Update()
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

uint Platform::MakeWindow(const char* title, int x, int y, uint width, uint height)
{

	Window::s_window_params params = { title, x, y, width, height, false, NULL };
	
	assert(m_platform_data);
	return Window::make_window(&params, Window::window_filler_option, *m_platform_data);
	
}

uint Platform::MakeDialogueWindow(const char* title, const char* text)
{
	return Window::make_dialog_window(title, text, Window::dialog_filler_option);
}

void Platform::MakeWindowFullscreen(uint index)
{
	Window::make_window_fullscreen(index, 1920, 1080, 256, 60);
}

void Platform::MakeWindowWindowed(uint index)
{
	Window::make_window_windowed(index);
}

#endif

