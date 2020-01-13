#pragma once
#include "ofMain.h"

class User {
public:
	string id;
	int currentS;
	int currentG;
	int currentD;

	int lastAnsweredQuestionId;

	User(string id, int s, int g, int d, int questionId) : id(id), currentS(s), currentG(g), currentD(d), lastAnsweredQuestionId(questionId) {};
};