#include "input.h"

static void (*g_key_up_callback_array[k_keybind_count])();
static void(*g_key_down_callback_array[k_keybind_count])();
void input_init()
{
	for (int i = 0; i < k_keybind_count; i++)
	{
		g_key_down_callback_array[i] = NULL;
		g_key_up_callback_array[i] = NULL;
	}
}
void input_update()
{

}
void register_input_callback(e_input_type key, void(*callback)(), e_callback_type callback_type)
{
	if (callback_type & call_on_key_down)
	{
		g_key_down_callback_array[key] = callback;
	}
	if (callback_type & call_on_key_up)
	{
		g_key_up_callback_array[key] = callback;
	}
}
