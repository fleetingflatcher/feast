#include "DisplayManager.h"

Display::DisplayManager::DisplayManager(int w, int h) :
	sdout(GetStdHandle(STD_OUTPUT_HANDLE)),
	loc({ 0,0 }),
	paint(PAINT::_white),
	width(w),
	height(h)
{};

void Display::DisplayManager::DrawPixel(COORD at, PAINT p, char ch) {
	loc = at;
	paint = p;
	prepTerminal();
	cout << ch;
}
void Display::DisplayManager::DrawPixel(int x, int y, PAINT p, char ch) {
	COORD location{ x, y };
	Display::DisplayManager::DrawPixel(location, p, ch);
}

void Display::DisplayManager::DrawChar(COORD at, char c, PAINT p) {
	loc = at;
	paint = p;
	prepTerminal();
	cout << c;
}
void Display::DisplayManager::DrawString(COORD at, std::string s, PAINT p) {
	loc = at;
	paint = p;
	prepTerminal();
	cout << s;
}

void Display::DisplayManager::DrawBox(COORD topLeft, short width, short height, PAINT p) {
	loc = topLeft;
	paint = p;
	prepTerminal();
	for (auto i = 0; i < width; ++i) {
		cout << "0";
	}
	for (auto i = 1; i < height; ++i) {
		loc = { (short)(topLeft.X + width - 1), (short)(i + topLeft.Y) };
		prepTerminal();
		cout << "0";
	}
	for (auto i = width - 2; i > 0; --i) {
		loc = { (short)(topLeft.X + i), (short)(topLeft.Y + height - 1) };
		prepTerminal();
		cout << "0";
	}
	for (auto i = height - 1; i > 0; --i) {
		loc = { topLeft.X, (short)(topLeft.Y + i) };
		prepTerminal();
		cout << "0";
	}
}
void Display::DisplayManager::DrawBox(COORD topLeft, COORD dimensions, PAINT p) {
	Display::DisplayManager::DrawBox(topLeft, dimensions.X, dimensions.Y, p);
}
void Display::DisplayManager::FillBox(COORD topLeft, short width, short height, PAINT p) {
	loc = topLeft;
	paint = p;
	prepTerminal();
	short maxY = topLeft.Y + height;
	short maxX = topLeft.X + width;
	for (int y = topLeft.Y; y < maxY; ++y) {
		for (int x = topLeft.X; x < maxX; ++x) {
			cout << "0";
		}
		loc.Y++;
		prepTerminal();
	}
}
void Display::DisplayManager::FillBox(COORD topLeft, COORD dimensions, PAINT p) {
	Display::DisplayManager::FillBox(topLeft, dimensions.X, dimensions.Y, p);
}


void Display::DisplayManager::SetColor(PAINT p) {
	paint = p;
}
void Display::DisplayManager::SetColor(PAINT bg, PAINT fg) {
	short c = bg + fg;
	paint = (PAINT)c;
}

//	Planned Private method definitions
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

//	Private Method definitions

void Display::DisplayManager::prepTerminal() {
	SetConsoleCursorPosition(sdout, loc);
	SetConsoleTextAttribute(sdout, paint);
}
void Display::DisplayManager::Reset() {
	resetTerminal();
}
void Display::DisplayManager::resetTerminal() {
	SetConsoleTextAttribute(sdout, PAINT::_black);
}