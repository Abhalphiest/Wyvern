#include "WindowMaster.h"

WindowMaster* WindowMaster::m_instance = nullptr;


///singleton functions
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
		
		m_window = other.m_window; //give them the same memory

	}

	///assignment operator
	WindowMaster& WindowMaster::operator=(const WindowMaster& other)
	{
		if (this != &other)
		{

			
			if (m_window != other.m_window)
			{
				if (m_window != nullptr)
				{
					glfwSetWindowShouldClose(m_window, GL_TRUE);
					free(m_window);
					
				}
				m_window = other.m_window; //give them the same memory
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


	//setters
	void WindowMaster::SetWindowFullscreen(bool fullscreen)
	{
		if (m_fullScreen == fullscreen)
			return; //we don't need to do anything, so don't waste the time

		m_fullScreen = fullscreen;
		if (m_fullScreen)
		{
			//get the video mode of the main monitor
			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
			//windowed fullscreen - chosen over true fullscreen due to speed and flexibility. put it on the primary monitor
			GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, m_windowName.c_str(), glfwGetPrimaryMonitor(), NULL);
		}
		else //back to window, doesn't matter what monitor since we're giving our own mode stuff
		{
			GLFWwindow* window = glfwCreateWindow(m_windowWidth, m_windowHeight, m_windowName.c_str(), NULL, NULL);
		}
	}

	void WindowMaster::SetWindowHeight(uint height)
	{
		if (m_windowHeight == height)
			return; //don't bother doing any costly function calls if we don't need to change anything

		m_windowHeight = height;
		glfwSetWindowSize(m_window, m_windowWidth, m_windowHeight);
	}
	void WindowMaster::SetWindowWidth(uint width)
	{
		if (m_windowWidth == width)
			return; //don't bother doing any costly function calls if we don't need to change anything

		m_windowWidth = width;
		glfwSetWindowSize(m_window, m_windowWidth, m_windowHeight);

	}

	void WindowMaster::SetWindowX(uint x)
	{
		if (m_windowX == x)
			return; //don't bother doing anything

		m_windowX = x;
		glfwSetWindowPos(m_window, m_windowX, m_windowY);
	}

	void WindowMaster::SetWindowY(uint y)
	{
		if (m_windowY == y)
			return; //don't bother doing anything

		m_windowY = y;
		glfwSetWindowPos(m_window, m_windowX, m_windowY);
	}

	void WindowMaster::SetWindowName(String nm)
	{
		//more costly to string compare than it is to just reassign and call it good
		m_windowName = nm;
		glfwSetWindowTitle(m_window, m_windowName.c_str());
		

	}