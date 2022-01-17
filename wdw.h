#pragma once
#include "Options.h"
#include "Display.h"

class wdw
{
private: 
	COORD topLeft;
	COORD dim; // Width and height
	Display::PAINT c_outline, c_fill; // Primary color enums
	bool fill;
public:
	wdw(Display::PAINT outlineColor, Display::PAINT fillColor, COORD location, COORD dimensions);
	wdw(Display::PAINT color, COORD location, COORD dimensions);
	wdw(COORD location, COORD dimensions);
	
	void Draw(Display::Terminal& terminal);
	short GetWidth();
	short GetHeight();
	short GetLocationX();
	short GetLocationY();
};
