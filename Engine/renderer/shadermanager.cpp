#include"shadermanager.h"
#include"dx11\dx11.h"
#include"renderer.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>

using namespace DirectX;

// best to keep these private to this file to abstract id implementation away
const unsigned short k_vertex_shader_mask	= 0x8000;
const unsigned short k_pixel_shader_mask	= 0x4000;
const unsigned short k_compute_shader_mask	= 0x2000;
const unsigned short k_shader_id_mask		= 0x1FFF;

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
Shader ShaderManager::CreateShaderProgram(const char* filename, ShaderType type)
{
	HRESULT result;
	ID3D11Device* device = g_Renderer->m_d3d->GetDevice();

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

		return 0;
	}


	Shader shaderId = 0;
	//create shader

	//TODO: check that vectors aren't full, put a max on vector length (13 bits)
	switch (type)
	{
	case VertexShader:
	{
		vertex_shader* vertexShader;
		result = device->CreateVertexShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, &vertexShader);
		shaderId = (short)m_vertex_shaders.size() & k_vertex_shader_mask;
		m_vertex_shaders.push_back(vertexShader);
		break;
	}
	case PixelShader:
	{
		pixel_shader* pixelShader;
		result = device->CreatePixelShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, &pixelShader);
		shaderId = (short)m_pixel_shaders.size() & k_pixel_shader_mask;
		m_pixel_shaders.push_back(pixelShader);
		break;
	}
	case ComputeShader:
	{
		ID3D11ComputeShader* computeShader;
		result = device->CreateComputeShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), NULL, &computeShader);
		shaderId = (short)m_compute_shaders.size() & k_compute_shader_mask;
		m_compute_shaders.push_back(computeShader);
		break;
	}
	default:
	{
		return 0; //TODO: Debug assert here
	}
	}

	if (type == VertexShader)
	{
		//make buffer layout for vertex shader
		//TODO: make this not hard coded, obviously

		// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
		polygonLayout[0].SemanticName = "POSITION";
		polygonLayout[0].SemanticIndex = 0;
		polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		polygonLayout[0].InputSlot = 0;
		polygonLayout[0].AlignedByteOffset = 0;
		polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		polygonLayout[0].InstanceDataStepRate = 0;

		polygonLayout[1].SemanticName = "COLOR";
		polygonLayout[1].SemanticIndex = 0;
		polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		polygonLayout[1].InputSlot = 0;
		polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		polygonLayout[1].InstanceDataStepRate = 0;

		// Get a count of the elements in the layout.
		numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

		buffer_layout* layout;

		// Create the vertex input layout.
		result = device->CreateInputLayout(polygonLayout, numElements, shaderBuffer->GetBufferPointer(),
			shaderBuffer->GetBufferSize(), &layout);

		m_layouts.push_back(layout);
	}
	if (FAILED(result))
	{
		return 0;
	}

	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	shaderBuffer->Release();
	shaderBuffer = 0;

	return shaderId;
}

void ShaderManager::ReleaseShaderProgram(Shader shader)
{
	// TODO : nullptr checking necessary?

	int index = shader & k_shader_id_mask;
	if (shader & k_vertex_shader_mask)
	{
		m_vertex_shaders[index]->Release();
		m_vertex_shaders[index] = nullptr;
		m_layouts[index]->Release();
	}
	else if (shader & k_pixel_shader_mask)
	{
		m_pixel_shaders[index]->Release();
		m_pixel_shaders[index] = nullptr;
	}
	else if (shader & k_compute_shader_mask)
	{
		m_compute_shaders[index]->Release();
		m_compute_shaders[index] = nullptr;
	}
}

ShaderManager::ShaderType ShaderManager::GetShaderType(Shader shader)
{
	if (shader & k_vertex_shader_mask)
	{
		return VertexShader;
	}
	else if (shader & k_pixel_shader_mask)
	{
		return PixelShader;
	}
	else if (shader & k_compute_shader_mask)
	{
		return ComputeShader;
	}
	else
	{
		return UnknownType;
	}
}

void ShaderManager::SetShader(Shader shader)
{
	int index = shader & k_shader_id_mask;
	ID3D11DeviceContext* context = g_Renderer->m_d3d->GetDeviceContext();
	if (shader & k_vertex_shader_mask)
	{
		// context->IASetInputLayout(m_layouts[index]);
		// context->VSSetShader(m_vertex_shaders[index], NULL, 0);
	}
	else if (shader & k_pixel_shader_mask)
	{
		// context->PSSetShader(m_pixel_shaders[index], NULL, 0);
	}
	else if (shader & k_compute_shader_mask)
	{
		// context->CSSetShader(m_compute_shaders[index], NULL, 0);
	}
}

ShaderManager::ShaderManager()
{
	// m_vertex_shaders = std::vector<vertex_shader*>();
	// m_pixel_shaders = std::vector<pixel_shader*>();
	// m_compute_shaders = std::vector<compute_shader*>();
	// m_layouts = std::vector<buffer_layout*>();
	// m_buffers = std::vector<buffer>();
}
ShaderManager::~ShaderManager()
{

}
ShaderManager::ShaderManager(const ShaderManager& other)
{

}

//void ShaderManager::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
//{
//	char* compileErrors;
//	unsigned long long bufferSize, i;
//	ofstream fout;
//
//
//	// Get a pointer to the error message text buffer.
//	compileErrors = (char*)(errorMessage->GetBufferPointer());
//
//	// Get the length of the message.
//	bufferSize = errorMessage->GetBufferSize();
//
//	// Open a file to write the error message to.
//	fout.open("shader-error.txt");
//
//	// Write out the error message.
//	for (i = 0; i<bufferSize; i++)
//	{
//		fout << compileErrors[i];
//	}
//
//	// Close the file.
//	fout.close();
//
//	// Release the error message.
//	errorMessage->Release();
//	errorMessage = 0;
//
//	// Pop a message up on the screen to notify the user to check the text file for compile errors.
//	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);
//
//	return;
//}