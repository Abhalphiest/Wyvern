#ifdef PLATFORM_WINDOWS_64
#include"platform.h"
#include<Windows.h>

//globals
s_platform_globals g_platform_globals;

void platform_init()
{
	//NOTE: May cause unexpected behavior if/when the engine is compiled into a DLL
	// keep an eye on this!
	g_platform_globals.hInstance = GetModuleHandle(NULL); 
}
#endif

