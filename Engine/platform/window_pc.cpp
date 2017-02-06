#include"window.h"

#ifdef PLATFORM_WINDOWS_64
#include<Windows.h>
#include<windowsx.h>

//private declarations
LRESULT CALLBACK window_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//constants
HINSTANCE k_hinstance_not_set = 0;

//globals
static WNDCLASSEX g_window_class =
{
	sizeof(WNDCLASSEX),
	CS_DBLCLKS | //double clicks can be recognized
	CS_HREDRAW | CS_VREDRAW, //redraws window if resized in either direction
	window_proc, //our window procedure
	0, 0, //no extra bytes (partially because I have no idea how to use them)
	k_hinstance_not_set, //the hInstance, to be set in window_system_init
	NULL, //default icon for now
	NULL, //we have to manually set the cursor
	(HBRUSH) COLOR_WINDOW,
	LPCSTR(L"DefaultWindowClass")
};

//function definitions
void window_system_init()
{
	g_window_class.hCursor = LoadCursor(NULL, IDC_ARROW); //normal arrow
	RegisterClassEx(&g_window_class);
}

uint make_window(s_window_params parameters, e_window_option options)
{
	return 0;
}
uint make_dialog(const char* title, const char* text, e_dialog_option options)
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

window_id get_platform_window_id(uint engine_window_id)
{
	return 0;
}

LRESULT CALLBACK window_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return 0;
}
#endif