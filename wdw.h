#include "Options.h"

class wdw
	// Class of objects I call Windows
{
public:
	COORD loc; 
	short wdt, hgt; // Width and height

	PAINT t_outline, t_fill; // Occasionally used text color enums
	PAINT c_outline, c_fill; // Primary color enums
	
	wdw(PAINT outlineColor, PAINT fillColor, short x, short y, short width, short height);
	wdw(PAINT color, short x, short y, short width, short height);
	wdw(short x, short y, short width, short height);
	
	void draw(Display::DisplayManager& dsp);
	void fill(Display::DisplayManager& dsp, std::string);
	void fill(Display::DisplayManager& dsp, std::string, std::string);
	//end of class
};
