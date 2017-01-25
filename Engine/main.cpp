#include"wyvern.h"
#ifdef PLATFORM_WINDOWS_64
#include <Windows.h>
#endif

#ifdef PLATFORM_WINDOWS_64

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	MessageBox(NULL, 
				LPCSTR("Hello World!"), 
				LPCSTR("Testing Dialog Box"), 
				MB_ICONEXCLAMATION | MB_OK);
}

#else
/*
void main()
{
	std::cout << "Hello, world!" << std::endl;
	int x = 0;
	std::cin >> x;


}
*/
#endif //WINDOWS_64