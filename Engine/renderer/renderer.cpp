#include "renderer.h"


Renderer::Renderer()
{
	m_d3d = 0;
}


Renderer::Renderer(const Renderer& other)
{
}


Renderer::~Renderer()
{
}


bool Renderer::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{

	bool result;


	// Create the Direct3D object.
	m_d3d = new Dx11Manager;
	if (!m_d3d)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_d3d->Initialize(screenWidth, screenHeight, k_vsync_enabled, hwnd, k_fullscreen, k_screen_depth, k_screen_near);
	if (!result)
	{
		MessageBox(hwnd, (LPCSTR)L"Could not initialize Direct3D", (LPCSTR)L"Error", MB_OK);
		return false;
	}

	return true;
}


void Renderer::Shutdown()
{
	// Release the Direct3D object.
	if (m_d3d)
	{
		m_d3d->Shutdown();
		delete m_d3d;
		m_d3d = 0;
	}
	return;
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