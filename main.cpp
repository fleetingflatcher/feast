#include <conio.h>
#include "DisplayManager.h"
#include "wdw.h"


int main() {
	system("mode 60, 31");
	Display::DisplayManager dspMgr{ 60, 31 };
	wdw Box{PAINT:: _red, PAINT::_yellow, {5,5}, {11,5} };
	Box.Draw(dspMgr);
	dspMgr.Reset();
	_getch();
}