#include "wdw.h"

wdw::wdw(PAINT c, PAINT f, short x, short y, short a, short b) {
	loc.X = x; loc.Y = y;
	wdt = a; hgt = b;
	c_outline = c; c_fill = f;
}
wdw::wdw(PAINT c, short x, short y, short a, short b) {
	loc.X = x; loc.Y = y;
	wdt = a; hgt = b;
	c_outline = c; c_fill = c;
}
wdw::wdw(short x, short y, short a, short b) {
	loc.X = x; loc.Y = y;
	wdt = a; hgt = b;
	c_outline = PAINT::_dkgray; c_fill = PAINT::_ltgray;
}

// In case we'd like to display our window,
void wdw::draw() {
	_Draw.X = loc.X; _Draw.Y = loc.Y;
	l_n::setLn();
	SetColor(c_outline);
	for (int i = wdt; i > 0; i--) {
		if (_Draw.X < 0) {
			_Draw.X++;
			l_n::setLn();
			continue;
		}
		else if (_Draw.Y < 0) {
			_Draw.X += i;
			break;
		}
		std::cout << " ";
		_Draw.X++;
		l_n::setLn();
	}
	for (int i = hgt; i > 0; i--) {
		if (_Draw.X > 60) {
			_Draw.Y += hgt;
			l_n::setLn();
			break;
		}
		else if (_Draw.Y < 0) {
			_Draw.Y++;
			l_n::setLn();
			continue;
		}
		else if (_Draw.Y > 30) {
			_Draw.Y += i;
			break;
		}
		std::cout << " ";
		_Draw.Y++;
		l_n::setLn();
	}
	for (int i = wdt; i > 0; i--) {
		if (_Draw.Y > 30) {
			_Draw.X -= wdt;
			break;
		}
		if (_Draw.X > 60) {
			_Draw.X--;
			l_n::setLn();
			continue;
		}
		std::cout << " ";
		_Draw.X--;
		l_n::setLn();
	}
	for (int i = hgt; i > 0; i--) {
		if (_Draw.Y < 0 || _Draw.X < 0) {
			_Draw.Y -= hgt;
			l_n::setLn();
			break;
		}
		else if (_Draw.Y > 30) {
			_Draw.Y--;
			l_n::setLn();
			continue;
		}
		else if (_Draw.X > 59) break;

		std::cout << " ";
		_Draw.Y--;
		l_n::setLn();
	}
	//end of draw()
}
// Fill, either with background color or text
void wdw::fill(std::string s) {
	_Draw.X = loc.X + 1; _Draw.Y = loc.Y + 1;
	SetColor(PAINT::bgltgreen);

	for (int y = hgt - 1; y > 0; y--) { 
		if (_Draw.Y < 0) {
			_Draw.Y++;
			continue;
		}
		else if (_Draw.Y > 30) break;
		for (int x = wdt - 1; x > 0; x--) {
			if (_Draw.X < 0) {
				_Draw.X++;
				continue;
			}
			else if (_Draw.X > 59) break;
			l_n::setLn();
			std::cout << 'a';
			_Draw.X++;
		}
		_Draw.Y++;
		_Draw.X = loc.X + 1;
	}
	l_n::setLn();
}
// Alternate fill that makes an elementary pattern
void wdw::fill(std::string s, std::string a) {
	_Draw.X = loc.X + 1; _Draw.Y = loc.Y + 1;
	SetColor(c_fill); bool alt = true;
	for (int y = hgt - 1; y > 0; y--) {
		alt = !alt;
		if (_Draw.Y < 0) {
			_Draw.Y++;
			continue;
		}
		else if (_Draw.Y > 30) break;
		for (int x = wdt - 1; x > 0; x--) {
			l_n::setLn();
			if (_Draw.X < 0) {
				_Draw.X++;
				continue;
			}
			else if (_Draw.X > 59) break;

			if (!alt) {
				if (x % 2) std::cout << s;
				else std::cout << a;
			}
			else {
				if ((x + 1) % 2) std::cout << s;
				else std::cout << a;
			}

			_Draw.X++;
		}
		_Draw.Y++;
		_Draw.X = loc.X + 1;
	}
	l_n::setLn();
}