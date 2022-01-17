#include <conio.h>
#include "Display.h"
#include "Board.h"
#include "wdw.h"
#include "Typewriter.h"

void type(Typewriter&);

int main() {
	Display::Terminal dspMgr{ 60, 31 };

	dspMgr.Reset();
	_getch();
}