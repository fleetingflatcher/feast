#pragma once
#include "Options.h"
#include <iostream>
#include <complex>

using namespace std;

namespace Display {
	// A fun enum containing text and background colors, as well as _color for solid paint
	enum PAINT
	{
		null = 0,
		black = 0,
		blue = 1,
		green = 2,
		teal = 3,
		red = 4,
		purple = 5,
		ltgray = 7,
		dkgray = 8,
		ltblue = 9,
		ltgreen = 10,
		ltred = 12,
		pink = 13,
		yellow = 14,
		white = 15,
		bgblack = 0,
		bgblue = 16,
		bggreen = 32,
		bgteal = 48,
		bgred = 64,
		bgpurple = 80,
		bgltgray = 112,
		bgdkgray = 128,
		bgltblue = 144,
		bgltgreen = 160,
		bgltred = 192,
		bgpink = 208,
		bgyellow = 224,
		bgwhite = 240,
		_black = black + bgblack,
		_blue = blue + bgblue,
		_green = green + bggreen,
		_teal = teal + bgteal,
		_red = red + bgred,
		_purple = purple + bgpurple,
		_ltgray = ltgray + bgltgray,
		_ltgreen = ltgreen + bgltgreen,
		_dkgray = dkgray + bgdkgray,
		_ltblue = ltblue + bgltblue,
		_ltred = ltred + bgltred,
		_pink = pink + bgpink,
		_yellow = yellow + bgyellow,
		_white = white + bgwhite
	};
	namespace Location {
		constexpr COORD TIMER = { 5, 21 };
		constexpr COORD BOARDSCORE = { 2, 21 };
		constexpr COORD GAMESCORE = { 37, 21 };
	};
	class Terminal {
	//Private data members
	private:
		HANDLE sdout;
		COORD loc;
		PAINT paint;
		int width, height;

	//	Private operational methods
	private:
		void prepTerminal();
		void resetTerminal();
	//	Public method interface
	public:
		Terminal(int w, int h);
		void Reset();
		// Planned public interface
		void DrawPixel(COORD, PAINT = PAINT::_white, char = ' ');
		void DrawPixel(int, int, PAINT = PAINT::_white, char = ' ');

		void DrawChar(COORD, char, PAINT = PAINT::_white);
		void DrawString(COORD, std::string, PAINT = PAINT::_white);

		void DrawBox(COORD topLeft, short width, short height, PAINT = PAINT::_ltgray);
		void DrawBox(COORD topLeft, COORD dimensions, PAINT = PAINT::_ltgray);
		void FillBox(COORD topLeft, short width, short height, PAINT = PAINT::_ltgray);
		void FillBox(COORD topLeft, COORD dimensions, PAINT = PAINT::_ltgray);

		//To be implemented.
		void DrawLine(COORD, COORD, PAINT = PAINT::_white);

		void SetColor(PAINT p);
		void SetColor(PAINT bg, PAINT fg);

		// Planned private methods
		void setLn(COORD c);
		void clrLn(COORD c, int a);
		void clrLn(COORD c, int a, int b);
		void clrLn(COORD c, PAINT p, int a);
		void clrLn(COORD c, PAINT p, int a, int b);
		//	Next, a few painting tools...
		
	};
}