#ifndef __WINDOW_H__
#define __WINDOW_H__
#pragma once
//includes
#include"wyvern.h"

//defines
#ifdef PLATFORM_WINDOWS_64
#include<Windows.h>
#define window_id HWND
#else
#define window_id uint
#endif

//enums
enum e_window_option
{

};

enum e_dialog_option
{
	filler_option,
};

//structs
struct s_window_keys
{
	window_id* m_windows;
	bool* m_is_open;
	uint m_num_windows;
};

struct s_window_params
{
	const char* m_title;
	uint m_xpos, m_ypos, m_width, m_height;
	window_id m_parent;
};

//function declarations
void window_system_init();
uint make_window(s_window_params parameters, e_window_option options);
uint make_dialog(const char* title, const char* text, e_dialog_option options);
window_id get_platform_window_id(uint engine_window_id);


#endif
