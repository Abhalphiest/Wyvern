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
	if (p_key == GLFW_KEY_O)
		m_cameraMaster->orbitCamera(.01f,XAXIS);
	if (p_key == GLFW_KEY_R)
	{
		m_cameraMaster->rotateCamera(.01f, YAXIS);
	}
	if (p_key == GLFW_KEY_T)
	{
		m_cameraMaster->truckCamera(.1f, XAXIS);
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

}
void InputMaster::JoystickManager()
{

}