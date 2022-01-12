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
	private: 
		HANDLE sdout;
	public:
		DisplayManager();
		void setLn(COORD c);
		void clrLn(COORD c, int a);
		void clrLn(COORD c, int a, int b);
		void clrLn(COORD c, PAINT p, int a);
		void clrLn(COORD c, PAINT p, int a, int b);
		//	Next, a few painting tools...
		void SetColor(PAINT p) {
			SetConsoleTextAttribute(sdout, p);
		}
		void SetColor(PAINT bg, PAINT fg) {
			short c = bg + fg;
			SetConsoleTextAttribute(sdout, c);
		}
	};
}