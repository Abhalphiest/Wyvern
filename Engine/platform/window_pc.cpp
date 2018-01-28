#include "platform.h"

#ifdef PLATFORM_WINDOWS_32
#include <Windows.h>
#include <windowsx.h>
#include "input/input.h"

// must include the platform definitions before window.h
// so that window_id works correctly
#include "platform_definitions_pc.h"
#include "window.h"

//private declarations

LRESULT CALLBACK window_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

static LPCSTR g_window_array[Window::k_max_windows_registered];
static LPCSTR g_current_window_class;
static HWND g_window_hwnd_array[Window::k_max_windows_registered];
static Window::s_window_params g_window_params[Window::k_max_windows_registered];

//function definitions
void Window::window_system_init(s_platform_data platform_data)
{
	WNDCLASSEX window_class =
	{
		sizeof(WNDCLASSEX),
		CS_DBLCLKS | //double clicks can be recognized
		CS_HREDRAW | CS_VREDRAW, //redraws window if resized in either direction
		window_proc, //our window procedure
		0, 0, //no extra bytes (partially because I have no idea how to use them)
		platform_data.hInstance,
		NULL, //default icon for now
		LoadCursor(NULL, IDC_ARROW), //normal arrow
		(HBRUSH)COLOR_WINDOW,
		NULL,
		LPCSTR(L"DefaultWindowClass"),
		NULL
	};

	RegisterClassEx(&window_class);

	g_current_window_class = LPCSTR(L"DefaultWindowClass");
	
	// any modern compiler should unroll this for us, since it's a constant length
	// loop with no break statements

	for (int i = 0; i < k_max_windows_registered; i++)
	{
		g_window_array[i] = NULL;
		g_window_hwnd_array[i] = 0;
	}
}

uint Window::make_window(s_window_params* parameters, e_window_option options, s_platform_data platform_data)
{
	int i; // Somewhat charming holdover from when I was using C99..

	for (i = 0; i < k_max_windows_registered; i++)
	{
		if (g_window_array[i] == NULL)
		{
			break;
		}
	}

	// trying to make more windows than supported by the engine
	// TODO: replace assert with error message, since asserts will be compiled
	// out in a release build
	assert(i < k_max_windows_registered);


	// ensure our parameters are good (or at least not null..)
	assert(parameters);
	assert(parameters->m_title);
	
	if (platform_data.hInstance == k_hinstance_not_set)
	{
		//TODO: Debug/Error message here!
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
		platform_data.hInstance,   		// application handle
		NULL);							// used with multiple windows, NULL
	
	// 	display the window on the screen
	//	TODO: Use command line show arg for first window? Possibly an overload?
	ShowWindow(hWnd, SW_SHOW);

	g_window_array[i] = parameters->m_title;
	g_window_hwnd_array[i] = hWnd;
	g_window_params[i] = *parameters;
	return i;
}
uint Window::make_dialog_window(const char* title, const char* text, e_dialog_option options)
{
	uint win_options = 0;

	//set options here

	//hard coded for now
	win_options = MB_ICONEXCLAMATION | MB_OK;


	// TODO: What the hell does this return?
	return MessageBoxA(NULL,
		LPCSTR(text),
		LPCSTR(title),
		win_options);
}

window_id Window::get_platform_window_id(uint engine_window_id)
{
	return g_window_hwnd_array[engine_window_id];
}

LRESULT CALLBACK window_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch (message)
	{
		case WM_KEYUP:  // These event names are fairly self-documenting
		case WM_KEYDOWN:
		case WM_MOUSEMOVE:
		case WM_MOUSEHOVER:
		case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDBLCLK:
		case WM_MBUTTONDBLCLK:
		case WM_MOUSEWHEEL:		// intentional fallthrough to handle all user input
		{
			g_Input->process_input(hWnd, message, wParam, lParam);
			break;
		}
		// this message is read when the window is closed
		case WM_DESTROY:
		{
			// close the application entirely
			PostQuitMessage(0);
			return 0;
		} 
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}

uint Window::get_window_width(uint index)
{
	return g_window_params[index].m_width;
}

uint Window::get_window_height(uint index)
{
	return g_window_params[index].m_height;
}

void Window::close_window(uint index)
{
	// TBI (to be implemented)
}

bool Window::make_window_fullscreen(uint index, int width, int height, int colourBits, int refreshRate) 
{

	DEVMODE fullscreenSettings;
	bool success;
	RECT windowBoundary;
	HWND hwnd = g_window_hwnd_array[index];

	EnumDisplaySettings(NULL, 0, &fullscreenSettings);
	fullscreenSettings.dmPelsWidth = width;
	fullscreenSettings.dmPelsHeight = height;
	fullscreenSettings.dmBitsPerPel = colourBits;
	fullscreenSettings.dmDisplayFrequency = refreshRate;
	fullscreenSettings.dmFields = DM_PELSWIDTH |
		DM_PELSHEIGHT |
		DM_BITSPERPEL |
		DM_DISPLAYFREQUENCY;

	SetWindowLongPtr(hwnd, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_TOPMOST);
	SetWindowLongPtr(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, width, height, SWP_SHOWWINDOW);
	success = ChangeDisplaySettings(&fullscreenSettings, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL;
	ShowWindow(hwnd, SW_MAXIMIZE);

	g_window_params[index].fullscreen = success;

	return success;
}

bool Window::make_window_windowed(uint index) 
{
	HWND hwnd = g_window_hwnd_array[index];
	bool success = false;
	s_window_params params = g_window_params[index];

	SetWindowLongPtr(hwnd, GWL_EXSTYLE, WS_EX_LEFT);
	SetWindowLongPtr(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
	success = ChangeDisplaySettings(NULL, CDS_RESET) == DISP_CHANGE_SUCCESSFUL;
	SetWindowPos(hwnd, HWND_NOTOPMOST, params.m_xpos, params.m_ypos, params.m_width, params.m_height, SWP_SHOWWINDOW);
	ShowWindow(hwnd, SW_RESTORE);

	g_window_params[index].fullscreen = !success;
	return success;
}
#endif