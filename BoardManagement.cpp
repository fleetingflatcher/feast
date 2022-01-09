#include "Options.h"


using namespace std;
using namespace l_n;

void chatPrint(string);

class Board
{
public:
	// stores list of matching COORDs whilst neighbors are checked
	vector<COORD> matchList;
	vector<COORD> emptyList;
	vector<COORD> eatList;

	// searches a vector for a COORD, to see if it has already been processed
	bool matchlist_Find(int x, int y) {
		COORD c; c.X = x; c.Y = y;
		for (int i = 0; i < (int)matchList.size(); i++) {
			if (matchList[i].X == c.X && matchList[i].Y == c.Y)
				return true;
		}
		return false;
	}
	void emptylist_Prune() {
		for (int i = (int)emptyList.size(); i > 0; i--) {
			if (eatlist_Find(emptyList[i].X, emptyList[i].Y)) {
				emptyList.erase(emptyList.begin() + i);
			}
		}
	}
	bool emptylist_Find(int x, int y) {
		COORD c; c.X = x; c.Y = y;
		for (int i = 0; i < (int)emptyList.size(); i++) {
			if (emptyList[i].X == c.X && emptyList[i].Y == c.Y)
				return true;
		}
		return false;
	}
	bool eatlist_Find(int x, int y) {
		COORD c; c.X = x; c.Y = y;
		for (int i = 0; i < (int)eatList.size(); i++) {
			if (eatList[i].X == c.X && eatList[i].Y == c.Y)
				return true;
		}
		return false;
	}


	COORD eat_at;
	enum direction {
		north, east, south, west
	} compass;
	int N, E, S, W;		// 'eat' count for each cardinal direction
	int tilesEmpty, bonus_tilesFilled, pnlty_tilesDestroyed;


public:
	short GameBoard[BOARD_SIZE][BOARD_SIZE];
	COORD c_grab; bool _grabbing, _eating;
	//Constructor
	Board() {
		N = E = S = W = tilesEmpty = 0;
		clear(); _grabbing = false;
	}
	/*
	screenLocation(int, int): returns the location on the screen of the argument tile coordinates.
	Overloads accept one or two directional enums to return all adjacent tiles.
	IE; screenlocation(4,4,north,east) returns the cursor location above
	and to the left of the fifth tile down and from the left.
	*/

	/* Update on 12/13/2021 :: Draw Utility Functions (screenLocation)
	Wrote these functions to replace this sort of thing:
	_Draw.X += 5;
	_Draw.Y = 1;
	Moving the draw cursor like a claw crane game...

	This function replaces ad hoc movements, enabling a 'point and click'
	for drawing at and around any tile.
	*/
	COORD screenLocation(int x, int y) {
		COORD screenLoc;
		screenLoc.X = 2 + (5 * x);
		screenLoc.Y = 1 + (2 * y);
		return screenLoc;
	}
	COORD screenLocation(int x, int y, direction d) {
		COORD screenLoc;
		screenLoc.X = 2 + (5 * x);
		screenLoc.Y = 1 + (2 * y);
		switch (d) {
		case north:
			screenLoc.Y--;
			break;
		case east:
			screenLoc.X--;
			break;
		case south:
			screenLoc.Y++;
			break;
		case west:
			screenLoc.X++;
		}
		return screenLoc;
	}
	COORD screenLocation(int x, int y, direction d1, direction d2) {
		COORD screenLoc;
		screenLoc.X = 2 + (5 * x);
		screenLoc.Y = 1 + (2 * y);
		switch (d1) {
		case north:
			screenLoc.Y--;
			break;
		case east:
			screenLoc.X--;
			break;
		case west:
			screenLoc.X++;
			break;
		case south:
			screenLoc.Y++;
		}
		switch (d2) {
		case north:
			screenLoc.Y--;
			break;
		case east:
			screenLoc.X--;
			break;
		case west:
			screenLoc.X++;
			break;
		case south:
			screenLoc.Y++;
		}
		return screenLoc;
	}

	//Game-Set functions
	void clear() {
		for (int x = 0; x < BOARD_SIZE; x++) {
			for (int y = 0; y < BOARD_SIZE; y++)
			{
				GameBoard[x][y] = 0;
			}
		}
	}
	void set() {
		for (int x = 0; x < BOARD_SIZE; x++)
			for (int y = 0; y < BOARD_SIZE; y++) {
				GameBoard[x][y] = rnd(6) + 1;
			}
	}
	// Game-play functions
	void Czech(COORD c) {
		bool isMatch = false;
		short mem;
		// Store value to check
		mem = GameBoard[c.X][c.Y];

		if (mem != 0) {							 //Some unhandled exception involving checking zeros?

			// Add original tile to our list of possible matches
			matchList.push_back(c);

			// Search neighbors... vFind keeps us from going in circles
			if (GameBoard[c.X - 1][c.Y] == mem) {
				subCheck(c.X - 1, c.Y, mem);
			}
			if (GameBoard[c.X + 1][c.Y] == mem) {
				if (!matchlist_Find(c.X + 1, c.Y))
					subCheck(c.X + 1, c.Y, mem);
			}
			if (GameBoard[c.X][c.Y - 1] == mem) {
				if (!matchlist_Find(c.X, c.Y - 1))
					subCheck(c.X, c.Y - 1, mem);
			}
			if (GameBoard[c.X][c.Y + 1] == mem) {
				if (!matchlist_Find(c.X, c.Y + 1))
					subCheck(c.X, c.Y + 1, mem);
			}

			// Check if a bona fide match has been achieved
			if (matchList.size() > 2) isMatch = true;
			if (isMatch) {
				score += (int)pow((matchList.size() - 1), 2) * 5;
				string s = "matched ";
				s += to_string(matchList.size());
				s += " tiles for ";
				s += to_string(int(pow((matchList.size() - 1), 2) * 5));
				s += " points";
				chatPrint(s);
				for (int i = matchList.size(); i > 0; i--) {
					COORD c = matchList.back();
					matchList.pop_back();
					clearTile(c);
				}
			}
			matchList.clear();
		}
	}
	void subCheck(int x, int y, short s) {
		COORD c; c.X = x; c.Y = y;
		matchList.push_back(c);

		if (GameBoard[x - 1][y] == s) {
			if (!matchlist_Find(c.X - 1, c.Y))
				subCheck(x - 1, y, s);
		}
		if (GameBoard[x + 1][y] == s) {
			if (!matchlist_Find(c.X + 1, c.Y))
				subCheck(x + 1, y, s);
		}
		if (GameBoard[x][y - 1] == s) {
			if (!matchlist_Find(c.X, c.Y - 1))
				subCheck(x, y - 1, s);
		}
		if (GameBoard[x][y + 1] == s) {
			if (!matchlist_Find(c.X, c.Y + 1))
				subCheck(x, y + 1, s);
		}

	}
	void clearTile(COORD c) {
		GameBoard[c.X][c.Y] = 0;
		tilesEmpty++;	  	//count the empty tiles
		emptyList.push_back(c);	 //mark the tile empty for eating
		score += 5;
	}

	// Function called to beginneth the feast (12/22/2021)
	void feast() {
		_eating = true;
		switch (rnd(4)) {
		case 0:
			eatN();
			break;
		case 1:
			eatE();
			break;
		case 2:
			eatS();
			break;
		case 3:
			eatW();
			break;
		}
	}
	void eatN() {
		eat_at.X = 0; eat_at.Y = N;
		N++;
		//count for cardinal direction
		compass = east;
		//indicates heading along which eating will take place
	}
	void eatE() {
		eat_at.X = 8 + E; eat_at.Y = 0;
		E--;
		compass = south;
	}
	void eatS() {
		eat_at.X = 8; eat_at.Y = S + 8;
		S--;
		compass = west;
	}
	void eatW() {
		eat_at.X = W; eat_at.Y = 8;
		W++;
		compass = north;
	}

	// A function called every frame that the feast is in-progresseth (12/22/2021)
	void eat() {
		
		// check if we're done eating?
		switch (compass) {
		case north:
			if (eat_at.Y < 0)
				_eating = false;
			break;
		case east:
			if (eat_at.X > 8)
				_eating = false;
			break;
		case south:
			if (eat_at.Y > 8)
				_eating = false;
			break;
		case west:
			if (eat_at.X < 0)
				_eating = false;
			break;
		}

		// if the tile is empty, move along. Still add to eatList. 
		while (GameBoard[eat_at.X][eat_at.Y] == 0 && _eating) {
			if (eat_at.X < 0 || eat_at.X > 8 || eat_at.Y < 0 || eat_at.Y > 8) _eating = false;
			else if (!eatlist_Find(eat_at.X, eat_at.Y)) eatList.push_back(eat_at);
			switch (compass) {
			case north:
				eat_at.Y--;
				break;
			case east:
				eat_at.X++;
				break;
			case south:
				eat_at.Y++;
				break;
			case west:
				eat_at.X--;
			}
		}

		// Got ourselves a tile,
		if (_eating) eatList.push_back(eat_at);
		// now what to do with it?

		// If there are no matches made, start killing tiles
		if (emptyList.empty() && _eating) {
			GameBoard[eat_at.X][eat_at.Y] = 0;
			pnlty_tilesDestroyed++;
			switch (compass) {
			case north:
				eat_at.Y--;
				break;
			case east:
				eat_at.X++;
				break;
			case south:
				eat_at.Y++;
				break;
			case west:
				eat_at.X--;
			}
		}
		else if (_eating){
			COORD c;
			if (!emptyList.empty()) c = emptyList.back();
			int temp = GameBoard[eat_at.X][eat_at.Y];
			GameBoard[eat_at.X][eat_at.Y] = 0;
			GameBoard[c.X][c.Y] = temp;
			emptyList.pop_back();
			tilesEmpty--;
			bonus_tilesFilled++;
			switch (compass) {
			case north:
				eat_at.Y--;
				break;
			case east:
				eat_at.X++;
				break;
			case south:
				eat_at.Y++;
				break;
			case west:
				eat_at.X--;
			}
		}
		// if we haven't filled all of the empty tiles, keep eating
		/* UPDATE (12/22/2021) Perhaps this was not a good gameplay mechanic.
		* This mechanic leaves it up to chance whether a player ends up receiving 
		a score penalty as a result of the feast. If the player makes many matches,
		and as a result, the feast continues; they are just as likely to have not 
		satisifed the number of tiles that will be feasted *perfectly*.
		if (!_eating && !emptyList.empty()) feast();
		*/
		else if (!_eating) reset();
	} //end eat

	// A function called when the feast is endeth (12/22/2021)
	void reset() {
		string s;
		_eating = false;
		if (pnlty_tilesDestroyed && bonus_tilesFilled) {
			s = "'Tile Fill' bonus: ";
			s += to_string(int(pow(bonus_tilesFilled, 2)) * 5);
			score += (int)(pow(bonus_tilesFilled, 2) * 5);
			s += "  ; 'Lost Tile' penalty: ";
			s += to_string(int(pow(float(pnlty_tilesDestroyed) / 2, 2)) * 5);
			score -= int(pow(float(pnlty_tilesDestroyed) / 2, 2)) * 5;

		}
		else if (bonus_tilesFilled) {
			s = "'Tile Fill' bonus: ";
			s += to_string(int(pow(bonus_tilesFilled, 2)) * 5);
			score += (int)(pow(bonus_tilesFilled, 2) * 5);
		}
		else {
			s = "'Lost Tile' penalty: ";
			s += to_string(int(pow(float(pnlty_tilesDestroyed) / 2, 2)) * 5);
			score -= int(pow(float(pnlty_tilesDestroyed) / 2, 2)) * 5;
		}
		chatPrint(s);
		pnlty_tilesDestroyed = bonus_tilesFilled = 0;

	}

	// (12/22/2021) SPECULATION: A function which prevents 
	// the player from 'cursoring' over eaten tiles.
	void guard() {
		bool rowEmpty;
		//North Guard
		rowEmpty = true;
		for (int i = 0;; i++) {
			N = i;
			for (int x = 0; x < 9; x++) {
				if (eatlist_Find(x, i))	continue;
				else rowEmpty = false;
			}
			if (!rowEmpty) break;
		}
		//East Guard
		rowEmpty = true;
		for (int i = 8;; i--) {
			E = i - 8;
			for (int y = 0; y < 9; y++) {
				if (eatlist_Find(i, y))	continue;
				else rowEmpty = false;
			}
			if (!rowEmpty) break;
		}
		//South Guard
		rowEmpty = true;
		for (int i = 8;; i--) {
			S = i - 8;
			for (int x = 0; x < 9; x++) {
				if (eatlist_Find(x, i))	continue;
				else rowEmpty = false;
			}
			if (!rowEmpty) break;
		}
		//West Guard
		rowEmpty = true;
		for (int i = 0;; i++) {
			W = i;
			for (int y = 0; y < 9; y++) {
				if (eatlist_Find(i, y))	continue;
				else rowEmpty = false;
			}
			if (!rowEmpty) break;
		}
		for (COORD c : eatList)
		{
			GameBoard[c.X][c.Y] = 0;
		}
	}


	// I/O functions
	void draw() {
		//starting position
		_Draw.X = 2;
		_Draw.Y = 1;

		// Draw the game board
		for (int x = 0; x < BOARD_SIZE; x++) {
			for (int y = 0; y < BOARD_SIZE; y++)
			{
				_Draw = screenLocation(x, y);
				setLn();
				switch (GameBoard[x][y]) {
				case 0:
					SetColor(_black);
					cout << "O";
					break;
				case 1:
					SetColor(_ltred);
					cout << "O";
					break;
				case 2:
					SetColor(_ltblue);
					cout << "O";
					break;
				case 3:
					SetColor(_green);
					cout << "O";
					break;
				case 4:
					SetColor(_yellow);
					cout << "O";
					break;
				case 5:
					SetColor(_pink);
					cout << "O";
					break;
				case 6:
					SetColor(_white);
					cout << "O";
					break;
				}
			}
		}

		// Debugging, mark eaten tiles, and matched tiles
		for (int x = 0; x < BOARD_SIZE; x++) {
			for (int y = 0; y < BOARD_SIZE; y++)
			{
				_Draw = screenLocation(x, y);
				setLn(); SetColor(yellow);
				if (emptylist_Find(x, y)) {
					cout << "M";
				}
				setLn();
				if (eatlist_Find(x, y)) {
					cout << "E";
				}
			}
		}
	
		if (_grabbing) {
 			_Draw = screenLocation(c_grab.X, c_grab.Y,east, east);

			SetColor(ltgreen);
			setLn(); cout << ">";
			_Draw.X += 4;
			setLn(); cout << "<";
		}
	} //END DRAW
	void swap(COORD c) {
		// account for cursor-board discrepancy
		c.X--; c.Y--;

		// store the value of the tile @ grab COORD
		short temp; 
		temp = GameBoard[c_grab.X][c_grab.Y];

		// set value of tile @ grab COORD to that of tile @ cursor COORD
		GameBoard[c_grab.X][c_grab.Y] = GameBoard[c.X][c.Y];

		// set tile @ cursor COORD to stored tile value
		GameBoard[c.X][c.Y] = temp;

		// Now check both new loci for matches,
		Czech(c_grab);
		Czech(c);
		_grabbing = false;
	} // END SWAP
	void grab(COORD c) {
		c_grab.X = (c.X - 1);
		c_grab.Y = (c.Y - 1);
		_grabbing = true;
	} // END GRAB						 

}; // END BOARD