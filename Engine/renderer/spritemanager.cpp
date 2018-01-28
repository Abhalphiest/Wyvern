#include "spritemanager.h"

struct s_vertex
{
	vec3 position;
	vec2 uv;
};

SpriteManager::SpriteManager()
{
	m_active_sprites = std::vector<s_sprite>();
	m_inactive_sprites = std::vector<s_sprite>();
	s_vertex vertices[4]; //just need a single quad for 2d rendering
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	HRESULT result;

	// TODO: is this reasonable to hard code here?

	// bottom left
	vertices[0].position = XMFLOAT3(-.5f, -.5f, 0.0f);
	vertices[0].uv = XMFLOAT2(-1.0f, -1.0f);

	// top left
	vertices[1].position = XMFLOAT3(-.5f, .5f, 0.0f);
	vertices[1].uv = XMFLOAT2(-1.0f, 1.0f);

	// top right
	vertices[2].position = XMFLOAT3(.5f, .5f, 0.0f);
	vertices[2].uv = XMFLOAT2(1.0f, 1.0f);

	// bottom right
	vertices[3].position = XMFLOAT3(.5f, -.5f, 0.0f);
	vertices[3].uv = XMFLOAT2(1.0f, -1.0f);

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(s_vertex) * m_vertex_count;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Create the vertex buffer.
	result = g_Renderer->m_d3d->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertex_buffer);
	if (FAILED(result))
	{
		// TODO: Error message
	}
}

SpriteManager::~SpriteManager()
{
	m_vertex_buffer->Release();
}

void SpriteManager::RenderSprites()
{
	// TODO: finish, needs texture, draw call, etc

	unsigned int stride;
	unsigned int offset;
	ID3D11DeviceContext* context = g_Renderer->m_d3d->GetDeviceContext();

	// Set vertex buffer stride and offset.
	stride = sizeof(s_vertex);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	context->IASetVertexBuffers(0, 1, &m_vertex_buffer, &stride, &offset);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

Sprite SpriteManager::RegisterSprite()
{
	// TODO: hash for sprite ids
	return 0;
}
