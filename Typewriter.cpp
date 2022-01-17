#include "Typewriter.h"



//	Public Method Definitions
Typewriter::Typewriter(wdw& containerWindow, Display::DisplayManager& displayManager, PAINT textColor) :
	container(containerWindow),
	dspMgr(displayManager),
	sz(containerWindow.GetHeight()),
	w(containerWindow.GetWidth()),
	p(textColor) {};
bool Typewriter::stillTyping() {
	return !printing.empty();
}
void Typewriter::Type() {
	if (!printing.empty()) {
		history.front() += printing[0];
		printing.replace(0, 1, "");
		drawChar();
	}
}
void Typewriter::PrintLine() {
	history.push_front(std::string());
	clean();
	drawNewLine();
}
void Typewriter::PrintLine(std::string str) {
	history.push_front(std::string());
	printing = str;
	clean();
	drawNewLine();
}
void Typewriter::AppendToLine(std::string str) {
	printing += str;
}
void Typewriter::AppendToLine(int i) {
	printing += i;
}

//	Private Method Definitions
void Typewriter::drawChar() {
	if (auto l = ((short)history.front().length()) - 1; l >= 0) {
		dspMgr.DrawPixel(
			{ (short)(container.GetLocationX() + l), container.GetLocationY() },
			p,
			history.front()[l]
		);
	}
}
void Typewriter::drawNewLine() {
	container.Draw(dspMgr);
	for (int i = 0; i < history.size(); ++i) {
		auto l = history[i].size();
		for (int j = 0; j < l; ++j) {
			dspMgr.DrawPixel(
				{ (short)(container.GetLocationX() + j), (short)(container.GetLocationY() + i) },
				p,
				history[i][j]
			);
		}
	}
}
void Typewriter::clean() {
	while (history.size() > sz) {
		history.pop_back();
	}
}