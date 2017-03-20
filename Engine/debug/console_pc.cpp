#include "console.h"
#ifdef PLATFORM_WINDOWS_64
#include <Windows.h>

bool g_console_active = false;
static FILE* g_out = 0;
static FILE* g_err = 0;

void create_console()
{
	AllocConsole();
	freopen_s(&g_out,"CONOUT$", "w", stdout); //redirect our stdout and stderr to this new console
	freopen_s(&g_err,"CONOUT$", "w", stderr);
	g_console_active = true;
}
void destroy_console()
{
	FreeConsole();
	fclose(g_out);
	fclose(g_err);
	g_console_active = false;
}
void clear_console()
{
	system("cls");
}

bool is_console_active()
{
	return g_console_active;
}
#endif