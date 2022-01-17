#include "Board.h"
using namespace std;
using namespace Display;

bool Board::matchlist_Find(int x, int y) {
	COORD c; c.X = x; c.Y = y;
	for (int i = 0; i < (int)matchList.size(); i++) {
		if (matchList[i].X == c.X && matchList[i].Y == c.Y)
			return true;
	}
	return false;
}
void Board::emptylist_Prune() {
	for (int i = (int)emptyList.size(); i > 0; i--) {
		if (eatlist_Find(emptyList[i].X, emptyList[i].Y)) {
			emptyList.erase(emptyList.begin() + i);
		}
	}
}
bool Board::emptylist_Find(int x, int y) {
	COORD c; c.X = x; c.Y = y;
	for (int i = 0; i < (int)emptyList.size(); i++) {
		if (emptyList[i].X == c.X && emptyList[i].Y == c.Y)
			return true;
	}
	return false;
}
bool Board::eatlist_Find(int x, int y) {
	COORD c; c.X = x; c.Y = y;
	for (int i = 0; i < (int)eatList.size(); i++) {
		if (eatList[i].X == c.X && eatList[i].Y == c.Y)
			return true;
	}
	return false;
}


COORD Board::screenLocation(int x, int y) {
	COORD screenLoc;
	screenLoc.X = 2 + (5 * x);
	screenLoc.Y = 1 + (2 * y);
	return screenLoc;
}
COORD Board::screenLocation(int x, int y, direction d) {
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
COORD Board::screenLocation(int x, int y, direction d1, direction d2) {
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

void Board::ResetTiles() {
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			GameBoard[x][y] = rnd(6) + 1;
		}
	}
}
void Board::Czech(COORD c) {
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
void Board::subCheck(int x, int y, short s) {
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
void Board::clearTile(COORD c) {
	GameBoard[c.X][c.Y] = 0;
	tilesEmpty++;	  	//count the empty tiles
	emptyList.push_back(c);	 //mark the tile empty for eating
	score += 5;
}

void Board::feast() {
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
void Board::eatN() {
	eat_at.X = 0; eat_at.Y = N;
	N++;
	//count for cardinal direction
	compass = east;
	//indicates heading along which eating will take place
}
void Board::eatE() {
	eat_at.X = 8 + E; eat_at.Y = 0;
	E--;
	compass = south;
}
void Board::eatS() {
	eat_at.X = 8; eat_at.Y = S + 8;
	S--;
	compass = west;
}
void Board::eatW() {
	eat_at.X = W; eat_at.Y = 8;
	W++;
	compass = north;
}
void Board::eat() {

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
	else if (_eating) {
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
	else if (!_eating) EndFeast();
} //end eat

void Board::EndFeast() {
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
void Board::guard() {
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

void Board::draw(Display::Terminal& dsp) {
	//starting position
	COORD loc{ 0 ,0 };

	// Draw the game board
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			loc = screenLocation(x, y);
			switch (GameBoard[x][y]) {
			case 0:
				dsp.DrawPixel(loc, _black, 'O');
				break;
			case 1:
				dsp.DrawPixel(loc, _ltred, 'O');
				break;
			case 2:
				dsp.DrawPixel(loc, _ltblue, 'O');
				break;
			case 3:
				dsp.DrawPixel(loc, _green, 'O');
				break;
			case 4:
				dsp.DrawPixel(loc, _yellow, 'O');
				break;
			case 5:
				dsp.DrawPixel(loc, _pink, 'O');
				break;
			case 6:
				dsp.DrawPixel(loc, _white, 'O');
				break;
			}
		}
	}

	// Debugging, mark eaten tiles, and matched tiles
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			loc = screenLocation(x, y);
			if (emptylist_Find(x, y)) {
				dsp.DrawPixel(loc, yellow, 'M');
			}
			dsp.setLn(loc);
			if (eatlist_Find(x, y)) {
				dsp.DrawPixel(loc, yellow, 'E');
			}
		}
	}

	if (_grabbing) {
		loc = screenLocation(c_grab.X, c_grab.Y, east, east);
		dsp.DrawPixel(loc, ltgreen, '>');
		loc = screenLocation(c_grab.X, c_grab.Y, west, west);
		dsp.DrawPixel(loc, ltgreen, '<');
	}
} //END DRAW

void Board::swap(COORD c) {
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

void Board::grab(COORD c) {
	c_grab.X = (c.X - 1);
	c_grab.Y = (c.Y - 1);
	_grabbing = true;
} // END GRAB		