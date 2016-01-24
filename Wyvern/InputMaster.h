#ifndef _INPUTMASTER_H
#define _INPUTMASTER_H
#include"definitions.h"
#include"WindowMaster.h" //we need to be able to get an instance of this
#include"CameraMaster.h" //need to be able to affect the camera
class InputMaster
{
	public:
		///<summary>Gives the instance of the master, and if none exists, creates one first. </summary>
		static InputMaster* GetInstance(void); 
		///<summary>Destroys the instance of the master.</summary>
		static void ReleaseInstance(void); 
	private:
		///<summary> Private constructor. Gets singleton instances, sets up input settings, and binds callback functions.</summary>
		InputMaster(void); 
		///<summary> Private copy constructor. Does nothing, just can't be called.</summary>
		InputMaster(const InputMaster &other); 
		///<summary> Private assignment operator. Does nothing, just can't be called.</summary>
		InputMaster& operator=(const InputMaster &other); 
		///<summary> Private destructor. Does nothing, just can't be called.</summary>
		~InputMaster(void); 
		
		//Master Singletons
		static WindowMaster* m_windowMaster;
		static CameraMaster* m_cameraMaster;
		static InputMaster* m_instance;

		//input handling - made static to comply with GLFW callback needs
		//we cant have a this pointer being passed in

		///<summary> The function called by GLFW whenever a key is pressed. Signature is in compliance with the needs
		/// of GLFW.</summary>
		///<param name="p_window"> The window that the keypress came from </param>
		///<param name="p_key"> The key pressed </param>
		///<param name ="p_scancode"> The system specific scan code of the key </param>
		///<param name ="p_action">Whether the key is pressed, released, or repeated </param>
		///<param name ="p_mods"> Bit field for which modifier keys were engaged</param>
		static void KeyPressCallback(GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods);
		///<summary> The function called by GLFW whenever a unicode character is entered. Signature is in compliance with the needs
		/// of GLFW.</summary>
		///<param name="p_window"> The window that the keypress came from </param>
		///<param name="p_codepoint"> The unicode code point of the character </param>
		static void CharCallback(GLFWwindow* p_window, uint p_codepoint);
		///<summary> The function called by GLFW whenever the cursor moves. Signature is in compliance with the needs
		/// of GLFW.</summary>
		///<param name="p_window"> The window that the keypress came from </param>
		///<param name="p_xpos"> x position of the cursor </param>
		///<param name="p_codepoint"> y position of the cursor </param>
		static void CursorPosCallback(GLFWwindow* p_window, double p_xpos, double p_ypos);
		///<summary> The function called by GLFW whenever a mouse button is pressed. Signature is in compliance with the needs
		/// of GLFW.</summary>
		///<param name="p_window"> The window that the keypress came from </param>
		///<param name="p_button"> The button pressed </param>
		///<param name ="p_action">Whether the key is pressed, released, or repeated </param>
		///<param name ="p_mods"> Bit field for which modifiers were engaged</param>
		static void MouseButtonCallback(GLFWwindow* p_window, int p_button, int p_action, int p_mods);
		///<summary> The function called by GLFW whenever the user scrolls. Signature is in compliance with the needs
		/// of GLFW.</summary>
		///<param name="p_window"> The window that the keypress came from </param>
		///<param name="p_xoffset"> amount scrolled in x direction </param>
		///<param name="p_yoffset">the amount scrolled in the y direction </param>
		static void ScrollCallback(GLFWwindow* p_window, double p_xoffset, double p_yoffset);
		///<summary> Not currently implemented </summary>
		static void JoystickManager(); //won't be using right now
		//won't be using these for now, but they could be fun in the future!
		//void DropCallback(GLFWwindow* p_window, int p_count, const char** p_paths);
		//void GetClipboard();

		uint numJoysticksDetected; //won't be using right now
};
#endif