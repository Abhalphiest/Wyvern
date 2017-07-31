#ifndef __PLATFORM_H__
#define __PLATFORM_H__
#pragma once
//includes
#include "definitions.h"

struct s_platform_globals;

void platform_init();
bool platform_update();
void platform_exit();

#endif