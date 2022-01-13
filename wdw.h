#pragma once
#include "Options.h"
#include "DisplayManager.h"

class wdw
{
private: 
	COORD topLeft;
	COORD dim; // Width and height
	PAINT c_outline, c_fill; // Primary color enums
	bool fill;
public:
	wdw(PAINT outlineColor, PAINT fillColor, COORD location, COORD dimensions);
	wdw(PAINT color, COORD location, COORD dimensions);
	wdw(COORD location, COORD dimensions);
	
	void Draw(Display::DisplayManager& dsp);
};
