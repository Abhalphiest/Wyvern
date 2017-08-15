#pragma once

#ifndef _RENDERER_H

#define _RENDERER_H

#include "text_renderer.h"
#include "shadermanager.h"
#include "dx11/dx11.h"
#include <Windows.h>

const bool k_fullscreen = false;
const bool k_vsync_enabled = true;
const float k_screen_depth = 1000.0f;
const float k_screen_near = 0.1f;

class Renderer
{

	friend class ShaderManager;
	friend class SpriteManager;
public:
	static void InitializeRenderer();
	static void Release();
	bool Frame();

private:
	bool Render();
	Dx11Manager* m_d3d;
	SpriteManager* m_sprite_manager;
	Renderer();
	Renderer(const Renderer&);
	~Renderer();
};

extern Renderer* g_Renderer;
#endif