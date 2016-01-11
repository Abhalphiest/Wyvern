#include"InputMaster.h"
InputMaster* InputMaster::m_instance = nullptr;
WindowMaster* InputMaster::m_windowMaster = nullptr;
CameraMaster* InputMaster::m_cameraMaster = nullptr;
//singleton functions
InputMaster* InputMaster::GetInstance(void)
{
	if (m_instance == nullptr)
		m_instance = new InputMaster();
	return m_instance;
}
void InputMaster::ReleaseInstance(void)
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

InputMaster::InputMaster(void)
{
	Init();
}
InputMaster::InputMaster(const InputMaster &other)
{

}
InputMaster& InputMaster:: operator=(const InputMaster &other)
{
	return *this;
}
InputMaster::~InputMaster(void)
{

}
void InputMaster::Init(void)
{
	m_windowMaster = WindowMaster::GetInstance();
	GLFWwindow* window = m_windowMaster->GetWindow();
	m_cameraMaster = CameraMaster::GetInstance();

	//set up modes
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GL_TRUE); //might want to kill stickies once we're actually running a game
																	//but they're dependable and predictable for debugging


	//set up callbacks
	glfwSetKeyCallback(window, KeyPressCallback);
	glfwSetCharCallback(window, CharCallback);
	glfwSetCursorPosCallback(window, CursorPosCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetScrollCallback(window, ScrollCallback);



}

void InputMaster::KeyPressCallback(GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods)
{
	if (p_key == GLFW_KEY_X)
		m_cameraMaster->orbitCamera(.005f,XAXIS);
	if (p_key == GLFW_KEY_Y)
		m_cameraMaster->orbitCamera(.005f, YAXIS);
	if (p_key == GLFW_KEY_Z)
		m_cameraMaster->orbitCamera(.005f, ZAXIS);

	if (p_key == GLFW_KEY_I)
	{
		m_cameraMaster->rotateCamera(.001f, XAXIS);
	}
	if (p_key == GLFW_KEY_J)
	{
		m_cameraMaster->rotateCamera(.001f, YAXIS);
	}
	if (p_key == GLFW_KEY_K)
	{
		m_cameraMaster->rotateCamera(.001f, ZAXIS);
	}
	if (p_key == GLFW_KEY_UP)
	{
		m_cameraMaster->truckCamera(.1f, YAXIS);
	}
	if (p_key == GLFW_KEY_DOWN)
	{
		m_cameraMaster->truckCamera(-.1f, YAXIS);
	}
	if (p_key == GLFW_KEY_LEFT)
	{
		m_cameraMaster->truckCamera(.1f, XAXIS);
	}
	if (p_key == GLFW_KEY_RIGHT)
	{
		m_cameraMaster->truckCamera(-.1f, XAXIS);
	}
}
void InputMaster::CharCallback(GLFWwindow* p_window, uint p_codepoint)
{

}
void InputMaster::CursorPosCallback(GLFWwindow* p_window, double p_xpos, double p_ypos)
{

}
void InputMaster::MouseButtonCallback(GLFWwindow* p_window, int p_button, int p_action, int p_mods)
{

}
void InputMaster::ScrollCallback(GLFWwindow* p_window, double p_xoffset, double p_yoffset)
{
	m_cameraMaster->zoomCamera((float)p_yoffset);
}
void InputMaster::JoystickManager()
{

}