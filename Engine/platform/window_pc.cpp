#include"platform.h"



#ifdef PLATFORM_WINDOWS_64
#include<Windows.h>
#include<windowsx.h>
//#include "input/input.h"

// must include the platform definitions before window.h
// so that window_id works correctly
#include "platform_definitions_pc.h"
#include"window.h"

//private declarations
LRESULT CALLBACK window_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
window_id get_platform_window_id(uint engine_window_id);

extern s_platform_data g_platform_data;

static LPCSTR g_window_array[Window::k_max_windows_registered];
static LPCSTR g_current_window_class;
static HWND g_window_hwnd_array[Window::k_max_windows_registered];
static Window::s_window_params g_window_params[Window::k_max_windows_registered];

//function definitions
void Window::InitializeWindowSystem()
{
	WNDCLASSEX window_class =
	{
		sizeof(WNDCLASSEX),
		CS_DBLCLKS | //double clicks can be recognized
		CS_HREDRAW | CS_VREDRAW, //redraws window if resized in either direction
		window_proc, //our window procedure
		0, 0, //no extra bytes (partially because I have no idea how to use them)
		g_platform_data.hInstance,
		NULL, //default icon for now
		LoadCursor(NULL, IDC_ARROW), //normal arrow
		(HBRUSH)COLOR_WINDOW,
		NULL,
		LPCSTR(L"DefaultWindowClass"),
		NULL
	};

	RegisterClassEx(&window_class);

	g_current_window_class = LPCSTR(L"DefaultWindowClass");
	
	//compiler should unroll this for us
	for (int i = 0; i < k_max_windows_registered; i++)
	{
		g_window_array[i] = NULL;
		g_window_hwnd_array[i] = 0;
	}
}

uint Window::MakeWindow(s_window_params* parameters, e_window_option options)
{
	int i;
	for (i = 0; i < k_max_windows_registered; i++)
	{
		if (g_window_array[i] == NULL)
		{
			break;
		}
	}
	assert(i < k_max_windows_registered);

	assert(parameters);
	assert(parameters->m_title);
	
	if (g_platform_data.hInstance == k_hinstance_not_set)
	{
		//TODO: Debug message here!
		return -1;
	}
	HWND hWnd = CreateWindowEx(NULL,
		g_current_window_class,			// window class
		LPCSTR(parameters->m_title),	// title
		WS_OVERLAPPEDWINDOW,			// window style
		parameters->m_xpos,				// x-position
		parameters->m_ypos,				// y-position
		parameters->m_width,			// width
		parameters->m_height,			// height 
		parameters->m_parent,			// parent
		NULL,							// we aren't using menus, NULL
		g_platform_data.hInstance,   // application handle
		NULL);							// used with multiple windows, NULL
	
	// display the window on the screen
	//TODO: Use command line show arg for first window? Possibly an overload?
	ShowWindow(hWnd, SW_SHOW);

	g_window_array[i] = parameters->m_title;
	g_window_hwnd_array[i] = hWnd;
	g_window_params[i] = *parameters;
	return i;
}
uint Window::MakeDialogWindow(const char* title, const char* text, e_dialog_option options)
{
	uint win_options = 0;

	//set options here

	//hard coded for now
	win_options = MB_ICONEXCLAMATION | MB_OK;

	return MessageBoxA(NULL,
		LPCSTR(text),
		LPCSTR(title),
		win_options);
}

window_id Window::GetPlatformWindowId(uint engine_window_id)
{
	return g_window_hwnd_array[engine_window_id];
}

LRESULT CALLBACK window_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch (message)
	{
	case WM_KEYUP:
	case WM_KEYDOWN:
	case WM_MOUSEMOVE:
	case WM_MOUSEHOVER:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
	case WM_MBUTTONDBLCLK:
	case WM_MOUSEWHEEL:
	{
		//process_input(hWnd, message, wParam, lParam);
		break;
	}
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	} break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}

uint Window::GetWindowWidth(uint index)
{
	return g_window_params[index].m_width;
}

uint Window::GetWindowHeight(uint index)
{
	return g_window_params[index].m_height;
}
#endif