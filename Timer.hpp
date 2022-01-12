#pragma once
#include "Options.h"
#include <Windows.h>

class Timer {

public:
	double sample, start, end, remaining;
	bool isTicking;

	//Constructors
	Timer() {
		start = sample = end = remaining = 0;
		isTicking = false;
	}


	//Functions
	void Draw(Display::DisplayManager& dsp) {
		COORD loc{ 47, 0 };
		dsp.SetColor(_dkgray); dsp.setLn(loc);
		for (int x = 0; x < 18; x++) {
			cout << "00";
			loc.Y++; dsp.setLn(loc);
		}
		if (remaining / 1000 > 10) dsp.SetColor(_ltgreen);
		else if (remaining / 1000 > 4) dsp.SetColor(_yellow);
		else dsp.SetColor(_ltred);
		loc = { 47, 18 };
		for (int i = 0; i < int((remaining / 1000) * 1.3); i++) {
			dsp.setLn(loc); cout << "00";
			loc.Y--;
		}
	}
	void set() {
		start = sample = end = remaining = 0;
		start = GetTickCount();
		isTicking = true;
	}
	void set(double d) {
		start = sample = end = remaining = 0;
		start = GetTickCount();
		end = start + (d * 1000);
		isTicking = true;
	}
	void tick() {
		if (isTicking) {
			sample = GetTickCount() - start;
			if (end != 0) remaining = (end - start) - sample;
		}
	}
	double stop() {
		tick();
		if (end == 0) {
			isTicking = false;
			return sample;
		}
		else if (sample > (end - start)) {
			isTicking = false;
			return 1;
		}
		else {
			return remaining;
		}
	}

};