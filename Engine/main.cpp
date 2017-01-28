#include"wyvern.h"
#include"platform/window.h"



#ifdef PLATFORM_WINDOWS_64
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	make_dialog("Dialog Test", "Hello, World!", filler_option);
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