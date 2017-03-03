#include "wyvern.h"

#ifdef PLATFORM_WINDOWS_64

#include "input.h"
#include "inputhash.h"
#include "platform/platform.h"
#include <Windows.h>

//globals
static s_key_data g_key_data_table[WINDOWS_KEYCODE_MAX] = { 0 };
static void(*g_key_up_callback_array[WINDOWS_KEYCODE_MAX])() = { 0 };
static void(*g_key_down_callback_array[WINDOWS_KEYCODE_MAX])() = { 0 };

extern s_platform_globals g_platform_globals;

void process_input(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYUP:
	{
		g_key_data_table[wParam].frames_down = 0;
		g_key_data_table[wParam].is_down = false;
		if (g_key_up_callback_array[wParam])
		{
			g_key_up_callback_array[wParam]();
		}
		break;
	}
	case WM_KEYDOWN:
	{
		g_key_data_table[wParam].frames_down = (0xFFFF & lParam);
		g_key_data_table[wParam].is_down = true;
		//only call back if we were up the previous frame
		if (g_key_down_callback_array[wParam] && ((lParam & 0x40000000) == 0))
		{
			g_key_down_callback_array[wParam]();
		}
		break;
	}
	}
}

void input_system_init()
{

}

void register_input_callback(e_input_type key, void(*callback)(), e_callback_type callback_type)
{
	if (callback_type & call_on_key_down)
	{
		g_key_down_callback_array[k_input_hash[key]] = callback;
	}
	if (callback_type & call_on_key_up)
	{
		g_key_up_callback_array[k_input_hash[key]] = callback;
	}
}

s_key_data get_key_data(e_input_type key)
{
	return g_key_data_table[k_input_hash[key]];
}

#endif