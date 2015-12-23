#include "WindowMaster.h"
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>
WindowMaster* WindowMaster::m_instance = nullptr;
WindowMaster* WindowMaster::GetInstance(void)
{
	if (!m_instance) //our singleton doesn't exist yet
		m_instance = new WindowMaster();
	return m_instance; //send back our singleton
}

void WindowMaster::ReleaseInstance(void)
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
		
}
///Constructor
	WindowMaster::WindowMaster(void)
	{
		m_windowName = "Engine";
		Init();
	}
	///copy constructor
	WindowMaster::WindowMaster(WindowMaster const& other)
	{
		//m_windowName = other.m_windowName;
		m_window = other.m_window;

	}

	///assignment operator
	WindowMaster& WindowMaster::operator=(const WindowMaster& other)
	{
		if (this != &other)
		{

			m_windowName = other.m_windowName;
			if (m_window != other.m_window)
			{
				if (m_window != nullptr)
				{
					glfwSetWindowShouldClose(m_window, GL_TRUE);
					free(m_window);
					
				}
				m_window = other.m_window;
			}
		}
		return *this;
	}
	//destructor
	WindowMaster:: ~WindowMaster(void)
	{
		
		if (m_window != nullptr)
		{
			glfwSetWindowShouldClose(m_window, GL_TRUE);
			glfwTerminate();
		}
	}


	int WindowMaster::Init(void)
	{
		//initialize glfw library and make a window
		if (!glfwInit())
		{
			fprintf(stderr, "Failed to initialize GLFW. \n");
			return -1; //exit failure
		}
		m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, "Engine", NULL, NULL);

		if (m_window == NULL)
		{
			fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not compatible with GL 3.3+.");
			glfwTerminate();
			return -2; //exit failure
		}
		//makes openGL context current for created window
		glfwMakeContextCurrent(m_window);
		glewExperimental = true;
		if (glewInit() != GLEW_OK) //Initialize GLEW
		{
			fprintf(stderr, "Failed to initialize GLEW \n");
			return -3;
		}
		return 0; //exit success
	}

