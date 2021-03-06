#ifndef _INPUT_H_
#define _INPUT_H_
#pragma once


#ifdef PLATFORM_WINDOWS_32
#include <Windows.h>
#define WINDOWS_KEYCODE_MAX 0xAF
#endif

enum e_input_type
{
	mouse_left,
	mouse_right,
	mouse_center,
	key_backspace,
	key_clear,
	key_enter,
	key_shift,
	key_control,
	key_alt,
	key_pause,
	key_caps_lock,
	key_escape,
	key_spacebar,
	key_page_up,
	key_page_down,
	key_end,
	key_home,
	key_left,
	key_up,
	key_right,
	key_down,
	key_select,
	key_print,
	key_print_screen,
	key_insert,
	key_delete,
	key_help,
	key_0,
	key_1,
	key_2,
	key_3,
	key_4,
	key_5,
	key_6,
	key_7,
	key_8,
	key_9,
	key_a,
	key_b,
	key_c,
	key_d,
	key_e,
	key_f,
	key_g,
	key_h,
	key_i,
	key_j,
	key_k,
	key_l,
	key_m,
	key_n,
	key_o,
	key_p,
	key_q,
	key_r,
	key_s,
	key_t,
	key_u,
	key_v,
	key_w,
	key_x,
	key_y,
	key_z,
	key_numpad_0,
	key_numpad_1,
	key_numpad_2,
	key_numpad_3,
	key_numpad_4,
	key_numpad_5,
	key_numpad_6,
	key_numpad_7,
	key_numpad_8,
	key_numpad_9,
	key_f1,
	key_f2,
	key_f3,
	key_f4,
	key_f5,
	key_f6,
	key_f7,
	key_f8,
	key_f9,
	key_f10,
	key_f11,
	key_f12,
	key_num_lock,
	key_scroll_lock,
	key_left_shift,
	key_right_shift,
	key_left_ctrl,
	key_right_ctrl,
	key_volume_down,
	key_volume_up,
	key_volume_mute,
	k_keybind_count

};

enum e_mouse_event
{
	left_doubleclick = 0, 
	right_doubleclick,
	middle_doubleclick,
	mouse_hover,
	mouse_cursor_move,
	k_mouse_count
};

struct s_KeyData // note: mouse buttons count as keys
{
	bool is_down;
	unsigned long long frames_down;
};

struct s_MouseData
{
	int xpos;
	int ypos;
};

enum e_callback_type
{
	call_on_key_down = 1,
	call_on_key_up = 2,
	call_on_state_change = 3
};

class Input
{

public:
	static void Initialize();
	static void Release();

	s_KeyData PollKey(e_input_type key);
	s_MouseData PollMouse();
	void RegisterKeyCallback(e_input_type key, void (*callback)(), e_callback_type callback_type);
	void RegisterMouseCallback(e_mouse_event mouse_event, void(*callback)());
	void RegisterMouseWheelCallback(void(*callback)(int wheel_delta));
#ifdef PLATFORM_WINDOWS_32
	void process_input(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
#endif

private:
	// make constructor, destructor, copy constructor inaccessible
	Input();
	~Input();
	Input(const Input& other) {}
	void register_input_callback(e_input_type key, void (*callback)(), e_callback_type callback_type);
	void register_mouse_callback(e_mouse_event mouse_event, void(*callback)());
	void register_mouse_wheel_callback(void(*callback)(int wheel_delta));
	s_KeyData get_key_data(e_input_type key);
	s_MouseData get_mouse_data();

#ifdef PLATFORM_WINDOWS_32
	s_KeyData m_key_data_table[WINDOWS_KEYCODE_MAX] = { 0 };
	void(*m_key_up_callback_array[WINDOWS_KEYCODE_MAX])() = { 0 }; // these are arrays of function pointers.. syntax massacre
	void(*m_key_down_callback_array[WINDOWS_KEYCODE_MAX])() = { 0 };
#else
	s_KeyData m_key_data_table[k_keybind_count] = { 0 };
	void(*m_key_up_callback_array[k_keybind_count])() = { 0 }; // these are arrays of function pointers.. syntax massacre
	void(*m_key_down_callback_array[k_keybind_count])() = { 0 };
#endif

s_MouseData m_mouse_data = { 0 };
void(*m_mouse_callback_array[k_mouse_count])() = { 0 };
void(*m_mouse_wheel_callback)(int wheel_delta) = 0;

};

extern Input* g_Input;


#endif