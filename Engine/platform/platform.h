#ifndef __PLATFORM_H__
#define __PLATFORM_H__
#pragma once
//includes
#include "definitions.h"

struct s_platform_data;


namespace Platform
{
	void InitializePlatform();
	bool PlatformUpdate();
	void PlatformExit();
};

#endif