#pragma once

#include "definitions.h"

#ifdef PLATFORM_WINDOWS_64
#define WIN32_LEAN_AND_MEAN
#include<Windows.h>

#define window_id HWND

const HINSTANCE k_hinstance_not_set = 0;

struct s_platform_data
{
	HINSTANCE hInstance = k_hinstance_not_set;
};
#endif