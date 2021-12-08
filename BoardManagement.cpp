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
		for (int i = 0; i < matchList.size(); i++) {
			if (matchList[i].X == c.X && matchList[i].Y == c.Y)
				return true;
		}
		return false;
	}
	void emptylist_Prune() {
		for (int i = emptyList.size(); i > 0; i--) {
			if (eatlist_Find(emptyList[i].X, emptyList[i].Y)) {
				emptyList.erase(emptyList.begin() + i);
			}
		}
	}
	bool emptylist_Find(int x, int y) {
		COORD c; c.X = x; c.Y = y;
		for (int i = 0; i < emptyList.size(); i++) {
			if (emptyList[i].X == c.X && emptyList[i].Y == c.Y)
				return true;
		}
		return false;
	}
	bool eatlist_Find(int x, int y) {
		COORD c; c.X = x; c.Y = y;
		for (int i = 0; i < eatList.size(); i++) {
			if (eatList[i].X == c.X && eatList[i].Y == c.Y)
				return true;
		}
		return false;
	}


	COORD eat_at;
	enum direction {
		north, east, south, west
	}compass;
	int N, E, S, W;		// 'eat' count for each cardinal direction
	int tilesEmpty, bonus_tilesFilled, pnlty_tilesDestroyed;


public:
	short ray[BD_SZ][BD_SZ];
	COORD drawLoc[BD_SZ][BD_SZ];
	COORD c_grab; bool _grabbing, _eating;
	//Constructor
	Board() {
		short ray[BD_SZ][BD_SZ];
		N = E = S = W = tilesEmpty = 0;
		clear(); _grabbing = false;
	}
	//Game-Set functions
	void clear() {
		for (int x = 0; x < BD_SZ; x++) {
			for (int y = 0; y < BD_SZ; y++)
			{
				ray[x][y] = 0;
			}
		}
	}
	void set() {
		for (int x = 0; x < BD_SZ; x++)
			for (int y = 0; y < BD_SZ; y++) {
				ray[x][y] = rnd(6) + 1;
			}
	}
	// Game-play functions
	void Czech(COORD c) {
		bool isMatch = false;
		short mem;
		// Store value to check
		mem = ray[c.X][c.Y];

		if (mem != 0) {							 //Some unhandled exception involving checking zeros?

			// Add original tile to our list of possible matches
			matchList.push_back(c);

			// Search neighbors... vFind keeps us from going in circles
			if (ray[c.X - 1][c.Y] == mem) {
				subCheck(c.X - 1, c.Y, mem);
			}
			if (ray[c.X + 1][c.Y] == mem) {
				if (!matchlist_Find(c.X + 1, c.Y))
					subCheck(c.X + 1, c.Y, mem);
			}
			if (ray[c.X][c.Y - 1] == mem) {
				if (!matchlist_Find(c.X, c.Y - 1))
					subCheck(c.X, c.Y - 1, mem);
			}
			if (ray[c.X][c.Y + 1] == mem) {
				if (!matchlist_Find(c.X, c.Y + 1))
					subCheck(c.X, c.Y + 1, mem);
			}

			// Check if a bona fide match has been achieved
			if (matchList.size() > 2) isMatch = true;
			if (isMatch) {
				score += pow((matchList.size() - 1), 2) * 5;
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

		if (ray[x - 1][y] == s) {
			if (!matchlist_Find(c.X - 1, c.Y))
				subCheck(x - 1, y, s);
		}
		if (ray[x + 1][y] == s) {
			if (!matchlist_Find(c.X + 1, c.Y))
				subCheck(x + 1, y, s);
		}
		if (ray[x][y - 1] == s) {
			if (!matchlist_Find(c.X, c.Y - 1))
				subCheck(x, y - 1, s);
		}
		if (ray[x][y + 1] == s) {
			if (!matchlist_Find(c.X, c.Y + 1))
				subCheck(x, y + 1, s);
		}

	}
	void clearTile(COORD c) {
		ray[c.X][c.Y] = 0;
		tilesEmpty++;	  	//count the empty tiles
		emptyList.push_back(c);	 //mark the tile empty for eating
		score += 5;
	}

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
	// a general eat function, only called if (_eating)
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
		while (ray[eat_at.X][eat_at.Y] == 0 && _eating) {
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
			ray[eat_at.X][eat_at.Y] = 0;
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
			int temp = ray[eat_at.X][eat_at.Y];
			ray[eat_at.X][eat_at.Y] = 0;
			ray[c.X][c.Y] = temp;
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
		if (!_eating && !emptyList.empty()) feast();
		else if (!_eating) reset();
	} //end eat


	void reset() {
		string s;
		_eating = false;
		if (pnlty_tilesDestroyed && bonus_tilesFilled) {
			s = "'Tile Fill' bonus: ";
			s += to_string(int(pow(bonus_tilesFilled, 2)) * 5);
			score += (pow(bonus_tilesFilled, 2) * 5);
			s += "  ; 'Lost Tile' penalty: ";
			s += to_string(int(pow(float(pnlty_tilesDestroyed) / 2, 2)) * 5);
			score -= int(pow(float(pnlty_tilesDestroyed) / 2, 2)) * 5;

		}
		else if (bonus_tilesFilled) {
			s = "'Tile Fill' bonus: ";
			s += to_string(int(pow(bonus_tilesFilled, 2)) * 5);
			score += (pow(bonus_tilesFilled, 2) * 5);
		}
		else {
			s = "'Lost Tile' penalty: ";
			s += to_string(int(pow(float(pnlty_tilesDestroyed) / 2, 2)) * 5);
			score -= int(pow(float(pnlty_tilesDestroyed) / 2, 2)) * 5;
		}
		chatPrint(s);
		pnlty_tilesDestroyed = bonus_tilesFilled = 0;

	}
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
		for each (COORD c in eatList)
		{
			ray[c.X][c.Y] = 0;
		}
	}


	// I/O functions
	void draw() {
		//starting position
		_Draw.X = 2;
		_Draw.Y = 1;

		// Draw the game board
		for (int x = 0; x < BD_SZ; x++) {
			for (int y = 0; y < BD_SZ; y++)
			{
				setLn();
				switch (ray[x][y]) {
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
					SetColor(_purple);
					cout << "O";
					break;
				}
				//cout << ray[x][y];
				_Draw.Y += 2;
			}
			_Draw.X += 5;
			_Draw.Y = 1;
		}

		_Draw.X = 2;
		_Draw.Y = 1;

		// Debugging, mark eaten tiles, and matched tiles
		for (int x = 0; x < BD_SZ; x++) {
			for (int y = 0; y < BD_SZ; y++)
			{
				setLn(); SetColor(yellow);
				if (eatlist_Find(x, y)) {
					cout << "E";
				}
				_Draw.X--; _Draw.Y++;
				setLn(); SetColor(yellow);
				if (emptylist_Find(x, y)) {
					cout << "M";
				}
				_Draw.X++;
				_Draw.Y++;
			}
			_Draw.X += 5;
			_Draw.Y = 1;
		}
	
		if (_grabbing) {
			_Draw.X = (c_grab.X * 5);
			_Draw.Y = (c_grab.Y * 2) + 1;
			SetColor(_ltgreen);
			setLn(); cout << ">";
			_Draw.X += 4;
			setLn(); cout << "<";
		}
	} //END DRAW
	void swap(COORD c) {
		// account for cursor-board discrepancy
		//
		c.X--; c.Y--;
		// store the value of the tile @ grab COORD
		//
		short temp; temp = ray[c_grab.X][c_grab.Y];
		// set value of tile @ grab COORD to that of tile @ cursor COORD
		//
		ray[c_grab.X][c_grab.Y] = ray[c.X][c.Y];
		// set tile @ cursor COORD to stored tile value
		//
		ray[c.X][c.Y] = temp;

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