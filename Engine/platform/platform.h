#ifndef __PLATFORM_H__
#define __PLATFORM_H__
#pragma once
//includes
//#include"wyvern.h"
#include "definitions.h"

#ifdef PLATFORM_WINDOWS_64
#include<Windows.h>
#endif

#ifdef PLATFORM_WINDOWS_64
const HINSTANCE k_hinstance_not_set = 0;
#endif
struct s_platform_globals
#ifdef PLATFORM_WINDOWS_64
{
	HINSTANCE hInstance = k_hinstance_not_set;
};
#else
{

};
#endif

void platform_init();
bool platform_update();
void platform_exit();

#endif