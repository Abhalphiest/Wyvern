#ifndef __PLATFORM_H__
#define __PLATFORM_H__
#pragma once
//includes
#include"wyvern.h"

#ifdef PLATFORM_WINDOWS_64
#include<Windows.h>
#endif


struct s_platform_globals
#ifdef PLATFORM_WINDOWS_64
{
	HINSTANCE hInstance;
};
#else
{

};
#endif

//globals
static s_platform_globals g_platform_globals;

void platform_init();

#endif