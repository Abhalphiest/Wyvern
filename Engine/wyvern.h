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
#include"platform/platform.h"
#include"platform/window.h"
#include"memory/memorymanager.h"

// globals
Debug* g_Debug;
MemoryManager* g_MemoryManager;

// engine functions
namespace Wyvern
{
	void Launch() 
	{
		MemoryManager::InitializeMemoryManager();
		Debug::InitializeDebug();
		Platform::InitializePlatform();
	}
	void Exit() 
	{
		Debug::Release();
		Platform::PlatformExit();

		// should probably be last, just for safety..
		// can re-evaluate release order once more architecture is in place
		MemoryManager::Release();
	}

	Debug* DebugUtilities() { return g_Debug; }
}



#endif