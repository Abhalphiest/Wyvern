#include "wyvern.h"

// need a way to have these globals available throughout the engine but not to outside user of lib
Platform* g_Platform = nullptr;
Input* g_Input = nullptr;

namespace Wyvern{


	void Launch() 
	{
		Input::Initialize();
		Platform::Initialize();
	}

	bool Update()
	{
		bool quitRequest = g_Platform->Update();
		

		return quitRequest;
	}

	void Exit() 
	{
		Platform::Release();
		Input::Release();

	}

	Platform* GetPlatform(){ return g_Platform; }
	Input* GetInput(){ return g_Input; }


}