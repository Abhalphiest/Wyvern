#ifndef __PLATFORM_H__
#define __PLATFORM_H__
#pragma once

//includes
#include "definitions.h"
#include "input/input.h"

struct s_platform_data;

class Platform
{

public:
	static void Initialize();
	static void Release();

	bool Update();
	uint MakeWindow(const char* title, int x, int y, uint width, uint height);
	uint MakeDialogueWindow(const char* title, const char* text);
	void MakeWindowFullscreen(uint index);
	void MakeWindowWindowed(uint index);
private:
	Platform();
	~Platform();
	Platform(const Platform& other){}

	s_platform_data* m_platform_data;

};

extern Platform* g_Platform;

#endif