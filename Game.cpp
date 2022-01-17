#include "Options.h"
#include "Display.h"
#include "Timer.hpp"
#include "wdw.h"
#include "Board.h"

using namespace Display;

namespace DEFAULT_TIMES {
	const double FEAST = 11.5;
	const double GAME = 180.0;
}

// GAMETIME DECLARATIONS

//Window for scrolling in-game announcements and events
wdw chatbox({ 2, 24 }, { 54, 5 });
//Window for scrolling score change notifications
wdw scorebox({ 49, 1 }, { 9, 17 });
//Wrapper window for scorebox and feast timer
wdw hud_rt({ 46, -1 }, { 13, 32 });
//Wrapper window for chatbox and scoreboard/game timer
wdw hud_bt({ 0, 19 }, { 58, 15 });
//Gameboard background?
wdw ActiveGameBoard_bg({ -1, -1 }, { 47, 20 });

Timer eat_Timer;
Timer Game_Timer;

// MENUS WINDOW DECLARATIONS

void scoreScreen();

/*12/26/2021
* THE gameSet() FUNCTION DOES WAY TOO MUCH.
  Divide this up into more functions, possibly divy 
  responsibility out to multiple classes/cpp files.
  Details in to-do.
*/

void gameSet() {
	Board ActiveGameBoard;

	if (Game_Timer.isTicking) {
		//Game_Timer.set();
	}
	else Game_Timer.set(DEFAULT_TIMES::GAME);
	cout << endl << "Game board initialized" << endl; 
	Sleep(37);
	ActiveGameBoard.ResetTiles();
	cout << "Game board cleared" << endl; 
	Sleep(37);
	cout << "Game board generated" << endl; 
	Sleep(37);
	
	//Declare and initialize typewriters.
	//cout << "Typewriters declared and initialized" << endl;	
	Sleep(37);
	
	// Game Board Cursor, X and Y relate directly to game pieces
	COORD _Curs;
	cout << "Game cursor created" << endl; Sleep(37);

	/*
	The 'delta' bools are used to indicate unresolved discrepancy in program output
	 Set to true when something changes, then set to 
	 false once the discrepancy has been cout / resolved
	*/

/*
	bool dBoard, dScore;
	//Whether or not the user has grabbed a tile
	//12/26/2021 ==TODO==
	// tileGrabbed seems like a redeclaration of the _grabbed property of BoardManagement.cpp
	bool tileGrabbed;


	cout << "Booleans declared" << endl; Sleep(37);
	score = 0;
	cout << "Integers initialized" << endl; Sleep(37);
	cout << "Printing game board"; Sleep(666);

	system("CLS");			 //Clear Screen

	_Gaming = _Curs.X = _Curs.Y = 1; //Set _Gaming bool for gametime loop, set _Curs to initial position
				/* NOTE: _Curs (1,1) refers to ActiveGameBoard.ray[0][0] */

	//set _Draw based on curs and ray location for Cursor
/*
	tileGrabbed = dBoard = dScore = false;  //initializing
	hud_rt.c_outline = _ltgray; 
	hud_rt.c_fill = ltgray;
	hud_rt.draw(); 
	hud_rt.fill();

	scorebox.c_outline = _red; 
	scorebox.draw();

	hud_bt.c_outline = _dkgray;
	hud_bt.draw(); hud_bt.fill("_");

	chatbox.c_outline = _black; 
	chatbox.c_fill = _black;
	chatbox.draw(); 
	chatbox.fill(" ");

	ActiveGameBoard_bg.c_fill = _black;
	eat_Timer.set(DEFAULT_TIMES::FEAST);

	//FIRST DRAW
	ActiveGameBoard_bg.fill(" ");
	SetColor(ltblue);
	ActiveGameBoard.draw();	  // Draw Board

	chatPrint(string("ready player one"));

	_Draw.X = 49; _Draw.Y = 0;
	SetColor(_red); setLn();
	cout << "!";
	SetColor(dkgray);
	cout << ":";
	SetColor(white);
	cout << "scores";
	SetColor(dkgray);
	cout << ":";
	SetColor(_red);
	cout << "!";

	_Draw.X = 5; _Draw.Y = 21;		 //Initial user output, including score field
	SetColor(bgwhite, black); setLn();
	cout << "BOARD :  ";
	_Draw.X = 21; _Draw.Y = 21;
	SetColor(bgwhite, black); setLn();
	cout << "SCORE :  ";
	_Draw.X = 37; _Draw.Y = 21;
	SetColor(bgwhite, black); setLn();
	cout << "TIMER :  ";


	//GAME START
	do {
		//BOARD START
		if (dBoard) {
			ActiveGameBoard_bg.fill(" ");
			dBoard = false;
		}
		SetColor(ltblue);
		ActiveGameBoard.draw();
		//BOARD END


		//CURSOR START
		if (true) {
			SetColor(_white);
			_Draw.X = (_Curs.X * 5) - 4;
			if (anim < -2) {
				_Draw.Y = (_Curs.Y * 2);
				setLn(); cout << "<";
				_Draw.Y -= 2;
				_Draw.X += 2;
				setLn(); cout << ">";

				SetColor(black);
				_Draw.Y++;
				setLn(); cout << " ";
				_Draw.X -= 2;
				setLn(); cout << " ";
			}
			else if (anim < 1) {
				_Draw.Y = (_Curs.Y * 2) - 2;
				_Draw.X++;
				setLn(); cout << "-";
			}
			else if (anim < 7) {

				_Draw.Y = (_Curs.Y * 2) - 2;
				setLn(); cout << ">";
				_Draw.X += 2;
				_Draw.Y += 2;
				setLn(); cout << "<";

				SetColor(black);
				if (anim == 3) {
					_Draw.Y = (_Curs.Y * 2) - 2;
					_Draw.X++;
					setLn(); cout << " ";
				}
				_Draw.X -= 2;
				setLn(); cout << " ";
				_Draw.X++;
				_Draw.Y -= 2;
				setLn(); cout << " ";
				_Draw.X++;
				setLn(); cout << " ";
			}
			else {
				_Draw.Y = (_Curs.Y * 2) - 1;
				setLn(); cout << ">";
				_Draw.X += 2;
				setLn(); cout << "<";


				SetColor(black);
				_Draw.Y++;
				setLn(); cout << " ";
				_Draw.X -= 2;
				_Draw.Y -= 2;
				setLn(); cout << " ";

			}

		}
		//CURSOR END

		//CONTROL START
		if (!tileGrabbed) {
			if (GetAsyncKeyState(VK_UP) && _Curs.Y > 1 + ActiveGameBoard.N) {
				dBoard = true;
				_Curs.Y--;
			}
			if (GetAsyncKeyState(VK_DOWN) && _Curs.Y < 9 + ActiveGameBoard.S) {
				dBoard = true;
				_Curs.Y++;
			}
			if (GetAsyncKeyState(VK_LEFT) && _Curs.X > 1 + ActiveGameBoard.W) {
				dBoard = true;
				_Curs.X--;
			}
			if (GetAsyncKeyState(VK_RIGHT) && _Curs.X < 9 + ActiveGameBoard.E) {
				dBoard = true;
				_Curs.X++;
			}

			if (GetAsyncKeyState(VK_RETURN)) {
				ActiveGameBoard.grab(_Curs);
				tileGrabbed = dBoard = true;
				Sleep(155);
				//chatPrint("tile grabbed");
			}
		}
		else if (tileGrabbed) {
			if (GetAsyncKeyState(VK_UP) && _Curs.Y > 1 && _Curs.Y > (ActiveGameBoard.c_grab.Y)) {
				dBoard = true;
				_Curs.Y--;
			}
			if (GetAsyncKeyState(VK_DOWN) && _Curs.Y < 9 && _Curs.Y < (ActiveGameBoard.c_grab.Y + 2)) {
				dBoard = true;
				_Curs.Y++;
			}
			if (GetAsyncKeyState(VK_LEFT) && _Curs.X > 1 && _Curs.X > (ActiveGameBoard.c_grab.X)) {
				dBoard = true;
				_Curs.X--;
			}
			if (GetAsyncKeyState(VK_RIGHT) && _Curs.X < 9 && _Curs.X < (ActiveGameBoard.c_grab.X + 2)) {
				dBoard = true;
				_Curs.X++;
			}

			if (GetAsyncKeyState(VK_RETURN)) {
				ActiveGameBoard.swap(_Curs);
				dBoard = true;
				tileGrabbed = false;
				//chatPrint("tiles swapped");
				Sleep(155);

			}
		}
		if (GetAsyncKeyState(0x52)) _Gaming = false;
		//CONTROL END


		//DATA START
		chatPrint();
		_Draw.X = 2; _Draw.Y = 21;
		SetColor(bgdkgray, ltgreen); setLn();
		switch (num) {
		case 0:
			cout << "1st";
			break;
		case 1:
			cout << "2nd";
			break;
		case 2:
			cout << "3rd";
			break;
		}
		_Draw.X = 14; _Draw.Y = 21;
		SetColor(bgblack, ltgreen); clrLn(7);
		cout << score;
		_Draw.X = 30; _Draw.Y = 21;
		SetColor(bgblack, ltgreen); clrLn(7);
		cout << _score;
		//DATA END

		//FUNCTION START

		//timers start
		Game_Timer.tick();
		
		if (eat_Timer.isTicking) {
			eat_Timer.tick();
			eat_Timer.stop();
		}
		else {
			eat_Timer.set(DEFAULT_TIMES::FEAST);
			chatPrint("! The Feast is begun!");
			ActiveGameBoard.feast();

		}
		eat_Timer.Draw();
		
		_Draw.X = 45; _Draw.Y = 21;
		SetColor(ltgreen); setLn();				 
		if (Game_Timer.remaining) cout << setw(5) << int(Game_Timer.remaining / 1000) / 60 << ":" << int(Game_Timer.remaining / 1000) % 60;

		//timers end

		if (ActiveGameBoard._eating) ActiveGameBoard.eat();
		if (Game_Timer.stop() == 1) {
			num = -2;
			scoreScreen();
			break;
		}
		//FUNCTION END

		if (/*win conditions here*//*0) _Gaming = false;
		_Draw.X = 59; 
		_Draw.Y = 30; 
		setLn();
		cout << ""; //Move the cursor before sleep
		Sleep(65); anim++;
		ActiveGameBoard.guard();
		if (anim > 10) anim = -15;
	} while (_Gaming); //GAME END
	_score += score;
	num++;
	if (score > highest) highest = score;
	if (num == -1);
	else if (num < 3) gameSet();
	else {
		Game_Timer.stop();
		scoreScreen();
	}
	_Gaming = false;
}

//A simple, mostly self-explanatory score screen
void scoreScreen() {
	SetColor(bgltgray);
	system("CLS");
	SetColor(bgltgray, red);
	_Draw.X = 10; _Draw.Y = 1; setLn();
	//Output title
	cout << "F" << setw(9) << "E" << setw(11) << "A" << setw(11) << "S" << setw(9) << "T";
	SetColor(bgltgray, black);
	_Draw.X = 0; _Draw.Y = 3;
	setLn(); cout << "__________________________________________________________" << endl << endl;
	cout << "	Game score :	" << _score << endl << endl;
	cout << "	Best board :	" << highest << endl << endl;
	cout << "	Time spent :	" << int(180 - (Game_Timer.remaining / 1000)) << " seconds" << endl << endl;
	// Decided on a formula that made a curvy time bonus coefficent,
	// starting at a 4x bonus if you finished in 3 seconds,
	// down to around 1.05x bonus if you had 3 seconds left.
	cout << "	Time Bonus :	" << 0.0079*(sqrt(Game_Timer.remaining)) << endl << endl;
	_score = (int)(_score * (0.0079*sqrt(Game_Timer.remaining)));			  
	cout << "	Final Score  :	" << _score << endl << endl;
	cout << endl;

	system("Pause");
}

void print_MainMenu() {	
	SetColor(_black); system("CLS");
	SetColor(red);
	_Draw.X = 10; _Draw.Y = 1; setLn();
	cout << "F" << setw(9) << "E" << setw(11) << "A" << setw(11) << "S" << setw(9) << "T";
	
	_Draw.X = 3; _Draw.Y = 4;
	for (int y = 0; y < 12; y++) {
		for (int x = 0; x < 24; x++) {
			rnd(3) ? SetColor(_green) : SetColor(_ltgreen);
			setLn(); cout << "O";

			SetColor(_black);
			setLn();
			if (y == 1) {

			}
			if (y == 2) {
				if (x == 3 || x == 8 || x == 9 || x == 10) cout << "O";

			}
			if (y == 3) {
				if (x == 2 || x == 3 || x == 4 || x==5 || x == 9 || x == 18 || x == 19) cout << "O";

			}
			if (y == 4) {
				if (x == 3 || x == 9 || x == 15 || x == 16) cout << "O";

			}
			if (y == 5) {
				if (x == 19 || x == 20) cout << "O";

			}
			if (y == 6) {
				if (x == 16 || x == 17) cout << "O";
			}
			if (y == 7) {
			}
			if (y == 8) {
				if (x == 3||x == 11||x==15||x==16||x==17||x==19||x==20||x==21) cout << "O";
			}
			if (y == 9) {
				if (x == 3||x == 11||x==16||x==20) cout << "O";
			}
			if (y == 10) {
				if (x == 3||x == 11) cout << "O";
			}

			_Draw.X++;
		}
		_Draw.Y++;
		_Draw.X = 3;
	}
	_Draw.X = 9; _Draw.Y = 16;
	setLn(); SetColor(ltgreen);
	cout << "P to Play";

	_Draw.X = 33; _Draw.Y = 4;
	for (int y = 0; y < 12; y++) {
		for (int x = 0; x < 24; x++) {
			rnd(3) ? SetColor(_blue) : SetColor(_ltblue);
			setLn(); cout << "O";

			SetColor(_black);
			setLn();
			if (y == 1) {
				if (x > 1 && x < 7) cout << "O";
				else if (x > 8 && x < 15) cout << "O";
				else if (x > 16 && x < 21) cout << "O";
			}
			if (y == 3) {
				if (x > 1 && x < 4) cout << "O";
				else if (x > 5 && x < 10) cout << "O";
				else if (x != 14 && x > 11 && x < 19) cout << "O";
			}
			if (y == 5) {
				if (x > 1 && x < 7) cout << "O";
				else if (x > 8 && x < 15) cout << "O";
				else if (x > 16 && x < 21) cout << "O";
			}
			if (y == 7) {
				if (x == 2) cout << "O";
				else if (x > 4 && x < 8) cout << "O";
				else if (x > 9 && x < 13) cout << "O";
				else if (x > 15 && x < 21) cout << "O";
				else if (x == 22) cout << "O";

			}
			if (y == 9) {
				if (x == 2) cout << "O";
				if (x > 4 && x < 7) cout << "O";
				else if (x != 11 && x > 8 && x < 15) cout << "O";
				else if (x > 16 && x < 21) cout << "O";
			}
			_Draw.X++;
		}
		_Draw.Y++;
		_Draw.X = 33;
	}
	_Draw.X = 36; _Draw.Y = 16;
	setLn(); SetColor(ltblue);
	cout << "I for Instructions";

	_Draw.X = 28; _Draw.Y = 18;
	for (int y = 1; y < 12; y++) {
		for (int x = 0; x < 24; x++) {
			rnd(3) ? SetColor(_red) : SetColor(_ltred);
			setLn(); cout << "O";

			SetColor(_black);
			setLn();
			if (y == 1) {

			}
			if (y == 2) {
				if (x > 5 && x < 19) cout << "O";
			}
			if (y == 3) {
				if (x == 6 || x == 18) cout << "O";
			}
			if (y == 4) {
				if (x == 6 || x == 18) cout << "O";
			}
			if (y == 5) {
				if (x == 6 || x == 18) cout << "O";
			}
			if (y == 6) {
				if (x == 6 || x == 18 || x == 14 || x == 15) cout << "O";
			}
			if (y == 7) {
				if (x == 6 || x == 18) cout << "O";
			}
			if (y == 8) {
				if (x == 6 || x == 18) cout << "O";
			}
			if (y == 9) {
				if (x == 6 || x == 18) cout << "O";
			}
			if (y == 10) {
				if (x > 5 && x < 19) cout << "O";
			}
			_Draw.X++;
		}
		_Draw.Y++;
		_Draw.X = 28;
	}
	_Draw.X = 36; _Draw.Y = 29;
	setLn(); SetColor(ltred);
	cout << "E to exit";

}
// Everything under the instructions label
/*
void instruct() {
	SetColor(_ltgray);
	system("CLS");
	SetColor(bgltgray, black);
	cout << "	Welcome to Candy Crush ALIENS: Feast Edition" << endl;
	SetColor(bgltgray, red);
	cout << "	   They mostly come out at a night" << endl <<  "	  		   mostly" << endl << endl;
	SetColor(bgltgray, black);
	cout << "|This is a fast-paced tile destruction game. " << endl;
	cout << "|  First, select a tile you'd like to move," << endl;
	cout << "|    then choose an adjacent tile." << endl;
	cout << "|  The chosen tiles will change positions, and this" << endl;
	cout << "|  is how the player interacts with the game board." << endl;
	cout << "|Making a match of two or more game pieces" << endl;
	cout << "|  is done by interacting with an exising pair on the " << endl;
	cout << "|  board, or by switching two tiles to create a new pair" << endl;
	cout << "|The primary gameplay mechanic is ";
	SetColor(bgltgray, red);
	cout << "the feast." << endl;
	SetColor(bgltgray);
	cout << "|  The feast timer is to the right of the game board," << endl;
	cout << "|  it turn from green to red as the feast approacheth." << endl;
	cout << "|During the feast, *something* will eat a random edge" << endl;
	cout << "| (either row or column) off of the game board." << endl;
	cout << "|These tiles will then be used to fill in" << endl;
	cout << "|  the existing holes in the game board." << endl;
	cout << "|";
	SetColor(bgltgray, red);
	cout << "If a tile is eaten and it has nowhere to go," << endl;
	SetColor(bgltgray);
	cout << "|";
	SetColor(bgltgray, red);
	cout << "it dies and you recieve a small score penalty" << endl;
	SetColor(bgltgray);
	cout << "|For every tile that is filled, you recieve a score bonus" << endl;
	cout << "|" << endl;
	cout << "|The feast continues both until all empty " << endl;
	cout << "|tiles on the board are filled and the" << endl;
	cout << "|current eating is finished." << endl;
	cout << "|" << endl;
	cout << "|Once in game, hit R to EndFeast the board. You have three" << endl;
	cout << "|boards and 3 minutes to get as high a score as possible!" << endl;
	cout << endl;
	system("Pause");
}

int MainMenu() {
	while (true) 
	{									
		if (GetAsyncKeyState(0x50)) {		//Press P
			return 4;
		}
		if (GetAsyncKeyState(0x45)) {		//Press E
			return 0;
		}
		if (GetAsyncKeyState(0x49)) {		//Press I
			return 2;
		}
	}
}
int main()
{
	system("mode 60, 31");
	srand((UINT)time(0));
	_isRunning = true;

do {
	//Print the main menu, and return the result. MainMenu() is in Options.h
	print_MainMenu();
	switch (MainMenu()) {
	case 4:
		num = 0;
		_score = highest = 0;
		gameSet();
		break;
	case 2:
		instruct();
		break;
	case 0:
		_isRunning = false;
	}

	} while (_isRunning);
}*/
