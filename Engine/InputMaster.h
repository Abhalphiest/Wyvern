#ifndef _INPUTMASTER_H
#define _INPUTMASTER_H
#include"definitions.h"
#include"WindowMaster.h" //we need to be able to get an instance of this
#include"CameraMaster.h" //need to be able to affect the camera
class InputMaster
{
	public:
		static InputMaster* GetInstance(void); //accessor
		static void ReleaseInstance(void); //release
	private:
		void Init(void); //for initialization
		InputMaster(void); //constructor
		InputMaster(const InputMaster &other); //copy constructor
		InputMaster& operator=(const InputMaster &other); //assignment overload
		~InputMaster(void); //destructor
		
		WindowMaster* windowMaster;
		static InputMaster* m_instance;

		//input handling - made static to comply with GLFW callback needs
		//we cant have a this pointer being passed in
		static void KeyPressCallback(GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods);
		static void CharCallback(GLFWwindow* p_window, uint p_codepoint);
		static void CursorPosCallback(GLFWwindow* p_window, double p_xpos, double p_ypos);
		static void MouseButtonCallback(GLFWwindow* p_window, int p_button, int p_action, int p_mods);
		static void ScrollCallback(GLFWwindow* p_window, double p_xoffset, double p_yoffset);
		static void JoystickManager(); //won't be using right now
		//won't be using these for now, but they could be fun in the future!
		//void DropCallback(GLFWwindow* p_window, int p_count, const char** p_paths);
		//void GetClipboard();

		uint numJoysticksDetected; //won't be using right now
};
#endif