#pragma once
#include <sstream>
#include <deque>
#include "DisplayManager.h"
#include "wdw.h"

class Typewriter
{
//	Private data members
private:
	wdw& container;
	Display::DisplayManager& dspMgr;
	PAINT p;

	short sz;
	short w;
	
	std::string printing;
	std::deque<std::string> history;
	
//	Public interface members
public:
	Typewriter(wdw& containerWindow, Display::DisplayManager& displayManager, PAINT textColor = PAINT::white);
	bool stillTyping();
	void Type();
	void PrintLine();
	void PrintLine(std::string);
	void AppendToLine(std::string);
	void AppendToLine(int);

//	Private method members
private:
	void drawChar();
	void drawNewLine();
	void clean();
};