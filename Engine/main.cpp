#include"wyvern.h"
#include <vector>

#ifdef PLATFORM_WINDOWS_32

#include<windowsx.h>
#include<Windows.h>

#include"testing/testing.h" // testing suite

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{

	Wyvern::Launch();

	Wyvern::GetPlatform()->MakeWindow("Test Window", 80, 80, 800, 400);

	Wyvern::Update();
	testInput();
	
	while(Wyvern::Update())
	{

	}

	Wyvern::Exit();
}

#else // end PLATFORM_WINDOWS_32

void main()
{

	std::cout << "Hello, world!" << std::endl;
	int x = 0;
	std::cin >> x;

}

#endif // end PLATFORM_*
