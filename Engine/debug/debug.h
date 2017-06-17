#pragma once

#ifndef _DEBUG_H

#define _DEBUG_H
#include "debug/debug_definitions.h"
#include "debug/console.h"
// #include "debug/print.h"
#include "log/log_settings.h"
#include "log/log.h"
// #include "utility/data_structures.h"

// TODO: Remove when utilities are implemented
#include <vector>

// Singleton class to handle debugging utilities
// may change later to allow for static memory allocation of singletons
// still needs to be implemented

class Debug
{
public:

// Indirect constructor and destructor
	static void InitializeDebug();
	static void Release();

// Determining which streams we print to when we print..
	void SetActiveStreams(stream_field streams);

// Print just does the string, printarg uses variable arguments... think of printf if you must
	void Print(const char* str);
	void PrintArg(const char* str, int argc, ...);

// Log file functions
	void CreateLogFile(const char* path, uint &id);
	void CloseLogFile(uint id);
	void MakeLogFileActive(uint id); // Active logs are written to by print functions if the log stream is enabled
	void MakeLogFileInactive(uint id); // Inactive logs still have resources created for them, but are not currently written to

// Console functions
	void ClearConsole();
	void CloseConsole();

// Event functions
	
	// TO BE IMPLEMENTED
	
private:
// make constructor, destructor, copy constructor inaccessible
	Debug();
	~Debug();
	Debug(const Debug& other) {}

	stream_field m_streamfield;
	std::vector<c_debug_log> m_log_files;
	std::vector<uint> m_active_log_files;
	std::vector<uint> m_available_indices;
};

extern Debug* g_Debug;
#endif