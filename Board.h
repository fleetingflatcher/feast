#pragma once
#include "Options.h"
#include "Display.h"
#include <vector>

class Board
{
public:
	// stores list of matching COORDs whilst neighbors are checked
	std::vector<COORD> matchList;
	std::vector<COORD> emptyList;
	std::vector<COORD> eatList;

	// searches a vector for a COORD, to see if it has already been processed
	bool matchlist_Find(int, int);
	void emptylist_Prune();
	bool emptylist_Find(int x, int y);
	bool eatlist_Find(int x, int y);


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
		ResetTiles();
		_grabbing = false;
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
	COORD screenLocation(int x, int y);
	COORD screenLocation(int x, int y, direction d);
	COORD screenLocation(int x, int y, direction d1, direction d2);
	//Game-Set functions
	void ResetTiles();
	// Game-play functions
	void Czech(COORD c);
	void subCheck(int x, int y, short s);
	void clearTile(COORD c);
	// Function called to beginneth the feast (12/22/2021)
	void feast();
	void eatN();
	void eatE();
	void eatS();
	void eatW();
	// A function called every frame that the feast is in-progresseth (12/22/2021)
	void eat();
	// A function called when the feast is endeth (12/22/2021)
	void EndFeast();
	// (12/22/2021) SPECULATION: A function which prevents 
	// the player from moving the cursor over eaten tiles.
	void guard();
	// I/O functions
	void draw(Display::Terminal& dsp);
	void swap(COORD c);
	void grab(COORD c);

}; // END BOARD