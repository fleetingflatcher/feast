#include "wdw.h"
#include "Display.h"

using namespace Display;

wdw::wdw(PAINT c, PAINT f, COORD location, COORD dimensions) :
	topLeft(location),
	dim(dimensions),
	c_outline(c),
	c_fill(f),
	fill(true) {};

wdw::wdw(PAINT c, COORD location, COORD dimensions) :
	topLeft(location),
	dim(dimensions),
	c_outline(c),
	c_fill(Display::PAINT::null),
	fill(false) {};

wdw::wdw(COORD location, COORD dimensions) :
	topLeft(location),
	dim(dimensions),
	c_outline(Display::PAINT::_ltgray),
	c_fill(Display::PAINT::null),
	fill(false) {};

void wdw::Draw(Terminal& dsp) {
	if (fill) {
		dsp.FillBox(topLeft, dim, c_fill);
	}
	dsp.DrawBox(topLeft, dim, c_outline);
}

short wdw::GetWidth() {
	return dim.X;
}
short wdw::GetHeight() {
	return dim.Y;
}
short wdw::GetLocationX() {
	return topLeft.X;
}
short wdw::GetLocationY() {
	return topLeft.Y;
}