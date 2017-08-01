#pragma once

#ifndef _SHADER_MANAGER_H
#define _SHADER_MAANGER_H

#include "definitions.h"
#include "renderer_definitions_pc.h"

// TODO: replace with in engine type when ready
#include<vector>

class ShaderManager
{
public:
	enum ShaderType
	{
		VertexShader, PixelShader, ComputeShader
	};
	static void InitializeShaderManager();
	static void Release();
	void CreateShaderProgram(const char* filename, ShaderType type);
private:
	ShaderManager();
	~ShaderManager();
	ShaderManager(const ShaderManager& other);

	std::vector<vertex_shader> m_vertex_shaders;
	std::vector<pixel_shader> m_pixel_shaders;
	std::vector<buffer_layout> m_layouts;
	std::vector<buffer> m_buffers;
};

extern ShaderManager* g_shaderManager;

#endif