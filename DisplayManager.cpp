#include "DisplayManager.h"

Display::DisplayManager::DisplayManager() : sdout(GetStdHandle(STD_OUTPUT_HANDLE)) {};

void Display::DisplayManager::setLn(COORD c) {
	SetConsoleCursorPosition(sdout, c);
}
void Display::DisplayManager::clrLn(COORD c, int a) {
	SetConsoleCursorPosition(sdout, c);
	for (; a > 0; a--) cout << " ";
	SetConsoleCursorPosition(sdout, c);
}
void Display::DisplayManager::clrLn(COORD c, int a, int b) {
	SetConsoleCursorPosition(sdout, c);
	for (int y = b; y > 0; y--) {
		for (int x = a; x > 0; x--)
			cout << " ";
		cout << endl;
	}
	SetConsoleCursorPosition(sdout, c);
}
void Display::DisplayManager::clrLn(COORD c, PAINT p, int a) {
	SetConsoleCursorPosition(sdout, c);
	CONSOLE_SCREEN_BUFFER_INFO info; short temp;
	GetConsoleScreenBufferInfo(sdout, &info); temp = info.wAttributes;
	SetConsoleTextAttribute(sdout, p);
	for (; a > 0; a--) cout << " ";
	SetConsoleCursorPosition(sdout, c);
	SetConsoleTextAttribute(sdout, temp);
}
void Display::DisplayManager::clrLn(COORD c, PAINT p, int a, int b) {
	SetConsoleCursorPosition(sdout, c);
	CONSOLE_SCREEN_BUFFER_INFO info; short temp;
	GetConsoleScreenBufferInfo(sdout, &info); temp = info.wAttributes;
	SetConsoleTextAttribute(sdout, p);
	for (; b > 0; b--) { for (; a > 0; a--) cout << " "; }
	SetConsoleCursorPosition(sdout, c);
	SetConsoleTextAttribute(sdout, temp);
}