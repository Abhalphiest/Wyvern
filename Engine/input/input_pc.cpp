#ifdef PLATFORM_WINDOWS_32

#include "input.h"
#include "inputhash.h"
#include "platform/platform.h"
#include <Windows.h>
#include <Windowsx.h>

// avoids branch to check for null function ptr
void no_op(){}
void no_op(int null_data){}


void Input::Initialize()
{
	if(!g_Input)
	{
		g_Input = new Input();
	}
}

Input::Input(){
	//these loops will be unrolled by the compiler
	for (int i = 0; i < WINDOWS_KEYCODE_MAX; i++)
	{
		m_key_down_callback_array[i] = no_op;
		m_key_up_callback_array[i] = no_op;
	}
	for (int i = 0; i < k_mouse_count; i++)
	{
		m_mouse_callback_array[i] = no_op;
	}
	m_mouse_wheel_callback = no_op;
}

void Input::Release()
{
	if (g_Input)
	{
		delete g_Input;
		g_Input = nullptr;
	}
}

Input::~Input() {

}

s_KeyData Input::PollKey(e_input_type key)
{
	return get_key_data(key);
}

s_MouseData Input::PollMouse()
{
	return get_mouse_data();
}

void Input::RegisterKeyCallback(e_input_type key, void (*callback)(), e_callback_type callback_type)
{
	register_input_callback(key, callback, callback_type);
}

void Input::RegisterMouseCallback(e_mouse_event mouse_event, void(*callback)())
{
	register_mouse_callback(mouse_event,callback);
}

void Input::RegisterMouseWheelCallback(void(*callback)(int wheel_delta))
{
	register_mouse_wheel_callback(callback);
}


void Input::process_input(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYUP:
	{
		m_key_data_table[wParam].frames_down = 0;
		m_key_data_table[wParam].is_down = false;
		m_key_up_callback_array[wParam]();
		break;
	}
	case WM_KEYDOWN:
	{
		m_key_data_table[wParam].frames_down = (0xFFFF & lParam);
		m_key_data_table[wParam].is_down = true;
		// only call back if we were up the previous frame
		if (((lParam & 0x40000000) == 0))
		{
			m_key_down_callback_array[wParam]();
		}
		break;
	}
	case WM_LBUTTONDBLCLK:
	{
		m_mouse_callback_array[left_doubleclick]();
		break;
	}
	case WM_RBUTTONDBLCLK:
	{
		m_mouse_callback_array[right_doubleclick]();
		break;
	}
	case WM_MOUSEHOVER:
	{
		m_mouse_callback_array[mouse_hover]();
		break;
	}
	case WM_MOUSEMOVE:
	{
		m_mouse_data.xpos = GET_X_LPARAM(lParam);
		m_mouse_data.ypos = GET_Y_LPARAM(lParam);
		m_mouse_callback_array[mouse_cursor_move]();
		break;
	}
	case WM_MOUSEWHEEL:
	{
		m_mouse_wheel_callback(GET_WHEEL_DELTA_WPARAM(wParam));
		break;
	}
	}
}

void Input::register_input_callback(e_input_type key, void(*callback)(), e_callback_type callback_type)
{
	if (callback_type & call_on_key_down)
	{
		m_key_down_callback_array[k_input_hash[key]] = callback;
	}
	if (callback_type & call_on_key_up)
	{
		m_key_up_callback_array[k_input_hash[key]] = callback;
	}
}


void Input::register_mouse_callback(e_mouse_event mouse_event, void(*callback)())
{
	m_mouse_callback_array[mouse_event] = callback;
}
void Input::register_mouse_wheel_callback(void(*callback)(int wheel_delta))
{
	m_mouse_wheel_callback = callback;
}

s_KeyData Input::get_key_data(e_input_type key)
{
	return m_key_data_table[k_input_hash[key]];
}

s_MouseData Input::get_mouse_data()
{
	return m_mouse_data;
}

#endif