#include "InteractiveInterface.h"
#include <windows.h>

// This function would be overided in derived classes
// However, they all use code to hide cursor and set it's position
// From this function in override
void InteractiveInterface::draw()
{
	// Get current cursor info
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle, &cursorInfo);

	// Hide cursor
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);

	// Set cursor position in top-left corner of the console
	COORD cursorPosition;
	cursorPosition.X = 0;
	cursorPosition.Y = 0;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
