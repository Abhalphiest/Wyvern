#include"wyvern.h"
#include"platform/window.h"
#include"platform/platform.h"



#ifdef PLATFORM_WINDOWS_64
#include<windowsx.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	platform_init();
	window_system_init();

	s_window_params win_params;
	win_params.m_height = 400;
	win_params.m_width = 400;
	win_params.m_title = "Test Window";
	win_params.m_parent = NULL;
	win_params.m_xpos = 100;
	win_params.m_ypos = 100;

	uint window_id = make_window(&win_params,e_window_option::window_filler_option);

	// this struct holds Windows event messages
	MSG msg;

	// wait for the next message in the queue, store the result in 'msg'
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// translate keystroke messages into the right format
		TranslateMessage(&msg);

		// send the message to the WindowProc function
		DispatchMessage(&msg);
	}

	// return this part of the WM_QUIT message to Windows
	return msg.wParam;
}


#else

void main()
{
	std::cout << "Hello, world!" << std::endl;
	int x = 0;
	std::cin >> x;


}
#endif //PLATFORM_WINDOWS_64
