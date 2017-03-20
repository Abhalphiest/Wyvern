#include "wyvern.h"

#ifdef PLATFORM_WINDOWS_64

#include "input.h"
#include "inputhash.h"
#include "platform/platform.h"
#include <Windows.h>
#include <Windowsx.h>

//avoids branch to check for null function ptr
void no_op(){}
void no_op(int null_data){}

//globals
static s_key_data g_key_data_table[WINDOWS_KEYCODE_MAX] = { 0 };
static s_mouse_data g_mouse_data = { 0 };
static void(*g_key_up_callback_array[WINDOWS_KEYCODE_MAX])() = { 0 };
static void(*g_key_down_callback_array[WINDOWS_KEYCODE_MAX])() = { 0 };
static void(*g_mouse_callback_array[k_mouse_count])() = { 0 };
static void(*g_mouse_wheel_callback)(int wheel_delta) = 0;

extern s_platform_globals g_platform_globals;

void process_input(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYUP:
	{
		g_key_data_table[wParam].frames_down = 0;
		g_key_data_table[wParam].is_down = false;
		g_key_up_callback_array[wParam]();
		break;
	}
	case WM_KEYDOWN:
	{
		g_key_data_table[wParam].frames_down = (0xFFFF & lParam);
		g_key_data_table[wParam].is_down = true;
		//only call back if we were up the previous frame
		if (((lParam & 0x40000000) == 0))
		{
			g_key_down_callback_array[wParam]();
		}
		break;
	}
	case WM_LBUTTONDBLCLK:
	{
		g_mouse_callback_array[left_doubleclick]();
		break;
	}
	case WM_RBUTTONDBLCLK:
	{
		g_mouse_callback_array[right_doubleclick]();
		break;
	}
	case WM_MOUSEHOVER:
	{
		g_mouse_callback_array[mouse_hover]();
		break;
	}
	case WM_MOUSEMOVE:
	{
		g_mouse_data.xpos = GET_X_LPARAM(lParam);
		g_mouse_data.ypos = GET_Y_LPARAM(lParam);
		g_mouse_callback_array[mouse_cursor_move]();
	}
	case WM_MOUSEWHEEL:
	{
		g_mouse_wheel_callback(GET_WHEEL_DELTA_WPARAM(wParam));
	}
	}
}

void input_system_init()
{
	//these loops will be unrolled by the compiler
	for (int i = 0; i < WINDOWS_KEYCODE_MAX; i++)
	{
		g_key_down_callback_array[i] = no_op;
		g_key_up_callback_array[i] = no_op;
	}
	for (int i = 0; i < k_mouse_count; i++)
	{
		g_mouse_callback_array[i] = no_op;
	}
	g_mouse_wheel_callback = no_op;
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


void register_mouse_callback(e_mouse_event mouse_event, void(*callback)())
{
	g_mouse_callback_array[mouse_event] = callback;
}
void register_mouse_wheel_callback(void(*callback)(int wheel_delta))
{
	g_mouse_wheel_callback = callback;
}

s_key_data get_key_data(e_input_type key)
{
	return g_key_data_table[k_input_hash[key]];
}

s_mouse_data get_mouse_data()
{
	return g_mouse_data;
}
#endif