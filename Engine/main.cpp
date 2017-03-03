#include"wyvern.h"
#include"platform/window.h"
#include"platform/platform.h"
#include"input/input.h"


#ifdef PLATFORM_WINDOWS_64
#include<windowsx.h>

void a_callback()
{
	int i = 0;
	i++;
}

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

	uint window_id = make_window(&win_params, e_window_option::window_filler_option);

	input_system_init();
	register_input_callback(key_a, a_callback, call_on_key_down);
	while(platform_update());

	platform_exit();

}


#else

void main()
{
	std::cout << "Hello, world!" << std::endl;
	int x = 0;
	std::cin >> x;


}
#endif //PLATFORM_WINDOWS_64
