#pragma once
#include <Windows.h>
#include <cmath>

//Anonymous Namespace of Global Declaration
namespace {
	const short BOARD_SIZE = 9;		//Loop bools and constants
	bool _isRunning, _Gaming;

	//short c;						//User I/O variables

	//Score and UNDERscore
	//Board score and total score respectively
	int score, _score;
	//Score screen info, highest board score and time bonus to add to total score
	int highest, time_bonus;
	//Number of boards user has been given. Default max is 3
	short num;
}

//A random number function; mod by arg
static int rnd(int t) {
	return (rand() % t);
}