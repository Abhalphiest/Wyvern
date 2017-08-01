#ifndef _WYVERN_H
#define _WYVERN_H

#include "definitions.h"

//forward declarations
class Debug;

// all the things
#include"debug/debug.h"
// #include"audio/audio.h"
// #include"input/input.h"
#include"renderer/renderer.h"
#include"platform/platform_definitions_pc.h"
#include"platform/platform.h"
#include"platform/window.h"
#include"memory/memorymanager.h"

// globals
Debug* g_Debug;
MemoryManager* g_MemoryManager;
Renderer* g_Renderer;

// engine functions
namespace Wyvern
{
	void Launch() 
	{
		MemoryManager::InitializeMemoryManager();
		Debug::InitializeDebug();
		Platform::InitializePlatform();
		g_Renderer = new Renderer();
		g_Renderer->Initialize(800, 400, Window::get_platform_window_id(0));
	}
	void Exit() 
	{
		Debug::Release();
		Platform::PlatformExit();
		g_Renderer->Shutdown();
		if (g_Renderer)
			delete g_Renderer;

		// should probably be last, just for safety..
		// can re-evaluate release order once more architecture is in place
		MemoryManager::Release();
	}

	Debug* DebugUtilities() { return g_Debug; }
}



#endif