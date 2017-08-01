#pragma once

#ifndef _RENDERER_H

#define _RENDERER_H

#include "text_renderer.h"
#include "dx11/dx11.h"
#include <Windows.h>

const bool k_fullscreen = false;
const bool k_vsync_enabled = true;
const float k_screen_depth = 1000.0f;
const float k_screen_near = 0.1f;


class Renderer
{
public:
	Renderer();
	Renderer(const Renderer&);
	~Renderer();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();

private:
	Dx11Manager* m_d3d;

};

#endif