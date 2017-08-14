#pragma once

#ifndef _SHADER_MANAGER_H
#define _SHADER_MAANGER_H

#include "definitions.h"
#include "renderer_definitions_pc.h"

// TODO: replace with in engine type when ready
#include<vector>

typedef unsigned short Shader;

// TODO: Also want geom/hull shaders or something?

class ShaderManager
{
public:
	enum ShaderType
	{
		VertexShader, PixelShader, ComputeShader, UnknownType
	};
	static void InitializeShaderManager();
	static void Release();
	Shader CreateShaderProgram(const char* filename, ShaderType type);
	void ReleaseShaderProgram(Shader shader);
	ShaderType GetShaderType(Shader shader);
	void SetShader(Shader shader);
private:
	ShaderManager();
	~ShaderManager();
	ShaderManager(const ShaderManager& other);


	std::vector<vertex_shader*> m_vertex_shaders;
	std::vector<pixel_shader*> m_pixel_shaders;
	std::vector<compute_shader*> m_compute_shaders;
	std::vector<buffer_layout*> m_layouts;
	std::vector<buffer> m_buffers;
};

extern ShaderManager* g_shaderManager;

#endif