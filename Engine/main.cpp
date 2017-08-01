#include"wyvern.h"
#include <vector>

#ifdef PLATFORM_WINDOWS_64
#include<windowsx.h>
#include<Windows.h>
#include"testing/testing.h"
#include"memory/linearmemoryallocator.h"

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	std::vector<int> myvector;
	Wyvern::Launch();
	Wyvern::DebugUtilities()->SetActiveStreams(console_stream);
	Wyvern::DebugUtilities()->Print("Hello, world!\n");
	Wyvern::DebugUtilities()->Print("This is a test of the console debug text system.\n");
	//Wyvern::DebugUtilities()->PrintArg("max vector size: %lu \n", myvector.max_size());

	
	while (true)
	{
		Platform::PlatformUpdate();
		g_Renderer->Frame();
	}
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
