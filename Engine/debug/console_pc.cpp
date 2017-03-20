#include "console.h"
#ifdef PLATFORM_WINDOWS_64
#include <Windows.h>


static FILE* g_out = 0;
static FILE* g_err = 0;

void create_console()
{
	AllocConsole();
	freopen_s(&g_out,"CONOUT$", "w", stdout);
	freopen_s(&g_err,"CONOUT$", "w", stderr);
}
void destroy_console()
{
	FreeConsole();
	fclose(g_out);
	fclose(g_err);
}
void clear_console()
{
	system("cls");
}

#endif