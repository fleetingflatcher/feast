#pragma once
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
// A fun enum containing text and background colors, as well as _color for solid paint
enum PAINT
{
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
//A namespace for a few console text tools
namespace l_n {
	void setLn();
	void clrLn(int);
	void clrLn(int, int);
	void clrLn(PAINT, int);
	void clrLn(PAINT, int, int);
}

//Anonymous Namespace of Global Declaration
namespace {
	const short BD_SZ = 9;		//Loop bools and constants
	bool _isRunning, _Gaming;  
	
	HANDLE sdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD _Draw; short c;						//User I/O variables

	//Score and UNDERscore
	//Board score and total score respectively
	int score, _score;
	//Score screen info, highest board score and time bonus to add to total score
	int highest, time_bonus;
	//Number of boards user has been given. Default max is 3
	short num;

	//	Next, a few painting tools...

	short RtnColor(PAINT c) {
		return c;
	}
	short RtnColor(PAINT b, PAINT c) {
		short a = b + c;
		return a;
	}
	void SetColor(PAINT c) {
		SetConsoleTextAttribute(sdout, c);
	}
	void SetColor(PAINT b, PAINT c) {
		short a = b + c;
		SetConsoleTextAttribute(sdout, a);
	}

}
	//The Guts of the Main Menu

	//A random number function; mod by arg
static int rnd(int t) {
	return (rand()%t);
}