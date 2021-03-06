#include "debug.h"
#include <stdarg.h>

void Debug::Initialize()
{
	if (!g_Debug)
	{
		g_Debug = new Debug();
	}
}
void Debug::Release()
{
	if (g_Debug)
	{
		delete g_Debug;
		g_Debug = nullptr;
	}
}

void Debug::SetActiveStreams(stream_field streams)
{
	if (((streams & console_stream) || (streams & error_stream)) && !is_console_active())
	{
		create_console();
	}

	m_streamfield = streams;
}

// Print just does the string, printarg uses variable arguments... think of printf if you must
void Debug::Print(const char* str)
{
	if (m_streamfield & debug_stream)
	{

	}
	if (m_streamfield & event_stream)
	{

	}
	if (m_streamfield & error_stream)
	{
		
	}
	if (m_streamfield & console_stream)
	{
		fprintf(stdout, str);
	}
}
void Debug::PrintArg(const char* str, int argc, ...)
{
	if (m_streamfield & console_stream)
	{
		va_list args;
		va_start(args, str);
		vfprintf(stdout,str,args);
		va_end(args);
	}
}

// Log file functions
void Debug::CreateLogFile(const char* path, uint &id) {}
void Debug::CloseLogFile(uint id) {}
void Debug::MakeLogFileActive(uint id) {} // Active logs are written to by print functions if the log stream is enabled
void Debug::MakeLogFileInactive(uint id) {} // Inactive logs still have resources created for them, but are not currently written to

									 // Console functions
void Debug::ClearConsole() {}
void Debug::CloseConsole() {}

Debug::Debug()
{

}
Debug::~Debug()
{

}