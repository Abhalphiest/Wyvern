#pragma once
#include "definitions.h"
#if defined(PLATFORM_WINDOWS_64) && !defined(_RENDERER_DEFINITIONS_PC)

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <directxmath.h>
using namespace DirectX;

typedef ID3D11VertexShader vertex_shader;
typedef ID3D11PixelShader pixel_shader;
typedef ID3D11ComputeShader compute_shader;
typedef ID3D11Buffer buffer;
typedef ID3D11InputLayout buffer_layout;
typedef ID3D11Texture2D texture;
typedef XMFLOAT2 vec2;
typedef XMFLOAT3 vec3;
typedef XMFLOAT4 vec4;
typedef XMMATRIX Matrix;

#endif