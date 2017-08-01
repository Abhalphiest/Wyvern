#include"shadermanager.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>

using namespace DirectX;

void ShaderManager::InitializeShaderManager()
{
	if (!g_shaderManager)
		g_shaderManager = new ShaderManager();
}
void ShaderManager::Release()
{
	if (g_shaderManager)
		delete g_shaderManager;
}
void ShaderManager::CreateShaderProgram(const char* filename, ShaderType type)
{
	HRESULT result;

	// TODO: Find Dx11 equivalents?
	ID3D10Blob* errorMessage;
	ID3D10Blob* shaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	uint numElements;

	//initialize pointers to null
	errorMessage = nullptr;
	shaderBuffer = nullptr;

	//compile shader code
	const char* compilationType;
	switch (type)
	{
	case PixelShader:
		compilationType = "ps_5_0";
		break;
	case VertexShader:
		compilationType = "vs_5_0";
		break;
	case ComputeShader:
		compilationType = "cs_5_0"; // TODO: Is this actually a thing? I'm just extrapolating
		break;
	default:
		compilationType = "";
	}
	result = D3DCompileFromFile((LPCWSTR)filename, NULL, NULL, "", 
							compilationType, D3D10_SHADER_ENABLE_STRICTNESS, 
							0, &shaderBuffer, &errorMessage);

	if (FAILED(result))
	{
		if (errorMessage)
		{
			// TODO: Error message..
		}
		else 
		{
			// missing shader file
		}

		return;
	}


}

ShaderManager::ShaderManager()
{
	m_vertex_shaders = std::vector<vertex_shader>();
	m_pixel_shaders = std::vector<pixel_shader>();
	m_layouts = std::vector<buffer_layout>();
	m_buffers = std::vector<buffer>();
}
ShaderManager::~ShaderManager()
{

}
ShaderManager::ShaderManager(const ShaderManager& other)
{

}