#include"wyvern.h"


#ifdef PLATFORM_WINDOWS_64
#include<windowsx.h>
#include<Windows.h>


int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	Wyvern::Launch();
	Wyvern::DebugUtilities()->SetActiveStreams(console_stream);
	Wyvern::DebugUtilities()->Print("Hello, world!\n");
	Sleep(10000);
	Wyvern::Exit();
}


#else

void main()
{
	std::cout << "Hello, world!" << std::endl;
	int x = 0;
	std::cin >> x;


}
#endif //PLATFORM_WINDOWS_64
