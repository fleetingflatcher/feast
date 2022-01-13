#pragma once
#include "Options.h"
#include <iostream>
#include <complex>

using namespace std;

namespace Display {

	namespace Location {
		constexpr COORD TIMER = { 5, 21 };
		constexpr COORD BOARDSCORE = { 2, 21 };
		constexpr COORD GAMESCORE = { 37, 21 };
	};
	class DisplayManager {
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
		DisplayManager(int w, int h);
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