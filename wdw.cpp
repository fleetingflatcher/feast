#include "wdw.h"
#include "DisplayManager.h"


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
	c_fill(PAINT::null),
	fill(false) {};

wdw::wdw(COORD location, COORD dimensions) :
	topLeft(location),
	dim(dimensions),
	c_outline(PAINT::_ltgray),
	c_fill(PAINT::null),
	fill(false) {};

void wdw::Draw(Display::DisplayManager& dsp) {
	if (fill) {
		dsp.FillBox(topLeft, dim, c_fill);
	}
	dsp.DrawBox(topLeft, dim, c_outline);
}