#include "testing.h"


void testInput() 
{
	Wyvern::GetInput()->RegisterKeyCallback(key_spacebar, testDialogueWindow, call_on_key_down);
	Wyvern::GetInput()->RegisterMouseCallback(left_doubleclick, testFullscreen);
}



void testDialogueWindow()
{
	Wyvern::GetPlatform()->MakeDialogueWindow("Test Dialogue", "This is a test of the emergency window system.");
}

void testFullscreen() {
	static bool full = false;

	if (full)
		Wyvern::GetPlatform()->MakeWindowWindowed(0);
	else
		Wyvern::GetPlatform()->MakeWindowFullscreen(0);

	full = !full;
}