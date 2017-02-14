#ifndef _INPUT_H_
#define _INPUT_H_
#pragma once

#include"wyvern.h"

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

struct s_key_data
{
	bool is_down;
	unsigned long long frames_down;
};

enum e_callback_type
{
	call_on_key_down = 1,
	call_on_key_up = 2,
	call_on_state_change = 3
};

void input_system_init();
void register_input_callback(e_input_type key, void (*callback)(), e_callback_type callback_type);
s_key_data get_key_data(e_input_type key);


#endif