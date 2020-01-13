#pragma once
#include "ofMain.h"

class Score {
public:
	int sValue;
	int gValue;
	int dValue;
	Score(int s, int g, int d) : sValue(s), gValue(g), dValue(d) {};
};