#include"wyvern.h"


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
	Wyvern::Launch();
	Wyvern::DebugUtilities()->SetActiveStreams(console_stream);
	Wyvern::DebugUtilities()->Print("Hello, world!\n");

	
	//void* memory = malloc(1000);
	//LinearMemoryAllocator allocator(1000, memory);
	//testMemoryAllocator(allocator);
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
