#ifndef _WYVERN_H
#define _WYVERN_H

#include "definitions.h"

//forward declarations
class Debug;

// all the things
#include"debug/debug.h"
// #include"audio/audio.h"
// #include"input/input.h"
// #include"renderer/renderer.h"
// #include"platform/platform.h"

// globals
Debug* g_Debug;

// engine functions
namespace Wyvern
{
	void Launch() 
	{
		Debug::InitializeDebug();
	}
	void Exit() 
	{
		Debug::Release();
	}

	Debug* DebugUtilities() { return g_Debug; }
}



#endif