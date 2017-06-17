//#include"window.h"
//#include"platform.h"
//
//#ifdef PLATFORM_WINDOWS_64
//#include<Windows.h>
//#include<windowsx.h>
//#include "input/input.h"
//
////private declarations
//LRESULT CALLBACK window_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//
////constants
//const uint k_max_windows_registered = 10;
//
//extern s_platform_globals g_platform_globals;
//
//static LPCSTR g_window_array[k_max_windows_registered];
//static LPCSTR g_current_window_class;
//
////function definitions
//void window_system_init()
//{
//	WNDCLASSEX window_class =
//	{
//		sizeof(WNDCLASSEX),
//		CS_DBLCLKS | //double clicks can be recognized
//		CS_HREDRAW | CS_VREDRAW, //redraws window if resized in either direction
//		window_proc, //our window procedure
//		0, 0, //no extra bytes (partially because I have no idea how to use them)
//		g_platform_globals.hInstance,
//		NULL, //default icon for now
//		LoadCursor(NULL, IDC_ARROW), //normal arrow
//		(HBRUSH)COLOR_WINDOW,
//		NULL,
//		LPCSTR(L"DefaultWindowClass"),
//		NULL
//	};
//
//	RegisterClassEx(&window_class);
//
//	g_current_window_class = LPCSTR(L"DefaultWindowClass");
//	
//	//compiler should unroll this for us
//	for (int i = 0; i < k_max_windows_registered; i++)
//	{
//		g_window_array[i] = NULL;
//	}
//}
//
//uint make_window(s_window_params* parameters, e_window_option options)
//{
//	int i;
//	for (i = 0; i < k_max_windows_registered; i++)
//	{
//		if (g_window_array[i] == NULL)
//		{
//			break;
//		}
//	}
//	assert(i < k_max_windows_registered);
//
//	assert(parameters);
//	assert(parameters->m_title);
//	
//	if (g_platform_globals.hInstance == k_hinstance_not_set)
//	{
//		//TODO: Debug message here!
//		return -1;
//	}
//	HWND hWnd = CreateWindowEx(NULL,
//		g_current_window_class,			// window class
//		LPCSTR(parameters->m_title),	// title
//		WS_OVERLAPPEDWINDOW,			// window style
//		parameters->m_xpos,				// x-position
//		parameters->m_ypos,				// y-position
//		parameters->m_width,			// width
//		parameters->m_height,			// height 
//		parameters->m_parent,			// parent
//		NULL,							// we aren't using menus, NULL
//		g_platform_globals.hInstance,   // application handle
//		NULL);							// used with multiple windows, NULL
//	
//	// display the window on the screen
//	//TODO: Use command line show arg for first window? Possibly an overload?
//	ShowWindow(hWnd, SW_SHOW);
//
//	g_window_array[i] = parameters->m_title;
//	return i;
//}
//uint make_dialog(const char* title, const char* text, e_dialog_option options)
//{
//	uint win_options = 0;
//
//	//set options here
//
//	//hard coded for now
//	win_options = MB_ICONEXCLAMATION | MB_OK;
//
//	return MessageBoxA(NULL,
//		LPCSTR(text),
//		LPCSTR(title),
//		win_options);
//}
//
//window_id get_platform_window_id(uint engine_window_id)
//{
//	return 0;
//}
//
//LRESULT CALLBACK window_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	// sort through and find what code to run for the message given
//	switch (message)
//	{
//	case WM_KEYUP:
//	case WM_KEYDOWN:
//	case WM_MOUSEMOVE:
//	case WM_MOUSEHOVER:
//	case WM_LBUTTONDBLCLK:
//	case WM_RBUTTONDBLCLK:
//	case WM_MBUTTONDBLCLK:
//	case WM_MOUSEWHEEL:
//	{
//		process_input(hWnd, message, wParam, lParam);
//		break;
//	}
//		// this message is read when the window is closed
//	case WM_DESTROY:
//	{
//		// close the application entirely
//		PostQuitMessage(0);
//		return 0;
//	} break;
//	}
//
//	// Handle any messages the switch statement didn't
//	return DefWindowProc(hWnd, message, wParam, lParam);
//}
//#endif