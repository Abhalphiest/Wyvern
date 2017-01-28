#include"window.h"

#ifdef PLATFORM_WINDOWS_64

uint make_window(const char* title, e_window_option options)
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
#endif