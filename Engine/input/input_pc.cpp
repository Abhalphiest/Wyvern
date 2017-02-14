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

LRESULT CALLBACK input_proc(
	_In_ int    code,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{

	return CallNextHookEx(NULL, code, wParam, lParam);
}

void input_system_init()
{
	HHOOK handle = SetWindowsHookEx(
		WH_KEYBOARD,
		input_proc,
		g_platform_globals.hInstance,
		0 //bind to all threads
	);
	
	handle = SetWindowsHookEx(
		WH_MOUSE,
		input_proc,
		g_platform_globals.hInstance,
		0
	);
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