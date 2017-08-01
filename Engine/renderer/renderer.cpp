#include "renderer.h"
#include "platform/platform_definitions_pc.h"
#include "platform\window.h"

ShaderManager* g_shaderManager = nullptr;

Renderer::Renderer()
{
	m_d3d = nullptr;

	// Create the Direct3D object.
	m_d3d = new Dx11Manager;
	if (!m_d3d)
	{
		// TODO: add debug message
		return;
	}

	HWND hwnd = Window::GetPlatformWindowId(0);
	bool result;
	// Initialize the Direct3D object.
	result = m_d3d->Initialize(Window::GetWindowWidth(0), Window::GetWindowHeight(0), k_vsync_enabled, hwnd, k_fullscreen, k_screen_depth, k_screen_near);
	if (!result)
	{
		// TODO: Change MessageBox to debug thing to something else?
		// possible divergence for release?
		// this could happen in release build
		MessageBox(hwnd, (LPCSTR)L"Could not initialize Direct3D", (LPCSTR)L"Error", MB_OK);
		return;
	}

}


Renderer::Renderer(const Renderer& other)
{
}


Renderer::~Renderer()
{
	// Release the Direct3D object.
	if (m_d3d)
	{
		m_d3d->Shutdown();
		delete m_d3d;
		m_d3d = nullptr;
	}
}


void Renderer::Release()
{
	if (g_Renderer)
	{
		delete g_Renderer;
		g_Renderer = nullptr;
	}
}

void Renderer::InitializeRenderer()
{
	if (!g_Renderer)
	{
		g_Renderer = new Renderer();
	}
}

bool Renderer::Frame()
{
	bool result;


	// Render the graphics scene.
	result = Render();
	if (!result)
	{
		return false;
	}
	return true;
}


bool Renderer::Render()
{
	// Clear the buffers to begin the scene.
	m_d3d->BeginScene(.392f, .584f, .929f, 1.0f);


	// Present the rendered scene to the screen.
	m_d3d->EndScene();
	return true;
}