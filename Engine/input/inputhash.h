#pragma once
#ifndef _INPUT_HASH_H_
#define _INPUT_HASH_H_

#include"input.h"

#ifdef PLATFORM_WINDOWS_64
const int k_input_hash[k_keybind_count] =
{
	0x01,	//mouse_left
	0x02,	//mouse_right
	0x04,	//mouse_center
	0x08,	//key_backspace
	0x0C,	//key_clear
	0x0D,	//key_enter
	0x10,	//key_shift
	0x11,	//key_control
	0x12,	//key_alt
	0x13,	//key_pause
	0x14,	//key_caps_lock
	0x1B,	//key_escape
	0x20,	//key_spacebar
	0x21,	//key_page_up
	0x22,	//key_page_down
	0x23,	//key_end
	0x24,	//key_home
	0x25,	//key_left
	0x26,	//key_up
	0x27,	//key_right
	0x28,	//key_down
	0x29,	//key_select
	0x2A,	//key_print
	0x2C,	//key_print_screen
	0x2D,	//key_insert
	0x2E,	//key_delete
	0x2F,	//key_help
	0x30,	//key_0
	0x31,	//key_1
	0x32,	//key_2
	0x33,	//key_3
	0x34,	//key_4
	0x35,	//key_5
	0x36,	//key_6
	0x37,	//key_7
	0x38,	//key_8
	0x39,	//key_9
	0x41,	//key_a
	0x42,	//key_b
	0x43,	//key_c
	0x44,	//key_d
	0x45,	//key_e
	0x46,	//key_f
	0x47,	//key_g
	0x48,	//key_h
	0x49,	//key_i
	0x4A,	//key_j
	0x4B,	//key_k
	0x4C,	//key_l
	0x4D,	//key_m
	0x4E,	//key_n
	0x4F,	//key_o
	0x50,	//key_p
	0x51,	//key_q
	0x52,	//key_r
	0x53,	//key_s
	0x54,	//key_t
	0x55,	//key_u
	0x56,	//key_v
	0x57,	//key_w
	0x58,	//key_x
	0x59,	//key_y
	0x5A,	//key_z
	0x60,	//key_numpad_0
	0x61,	//key_numpad_1
	0x62,	//key_numpad_2
	0x63,	//key_numpad_3
	0x64,	//key_numpad_4
	0x65,	//key_numpad_5
	0x66,	//key_numpad_6
	0x67,	//key_numpad_7
	0x68,	//key_numpad_8
	0x69,	//key_numpad_9
	0x70,	//key_f1
	0x71,	//key_f2
	0x72,	//key_f3
	0x73,	//key_f4
	0x74,	//key_f5
	0x75,	//key_f6
	0x76,	//key_f7
	0x77,	//key_f8
	0x78,	//key_f9
	0x79,	//key_f10
	0x7A,	//key_f11
	0x7B,	//key_f12
	0x90,	//key_num_lock
	0x91,	//key_scroll_lock
	0xA0,	//key_left_shift
	0xA1,	//key_right_shift
	0xA2,	//key_left_ctrl
	0xA3,	//key_right_ctrl
	0xAE,	//key_volume_down
	0xAF,	//key_volume_up
	0xAD	//key_volume_mute
};


#define WINDOWS_KEYCODE_MAX 0xAF

#endif
#endif //_INPUT_HASH_H