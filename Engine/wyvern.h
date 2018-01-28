#ifndef _WYVERN_H
#define _WYVERN_H

#include "definitions.h"


// include order may be important, modify at your own risk

#include "platform/platform_definitions_pc.h"
#include "platform/platform.h"
#include "input/input.h"



// User-facing engine functions
namespace Wyvern
{
	void Launch();
	bool Update();
	void Exit();

	Platform* GetPlatform();
	Input* GetInput();


}



#endif