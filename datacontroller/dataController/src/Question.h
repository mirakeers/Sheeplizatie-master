#pragma once
#include "ofMain.h"
#include "Score.h"

class Question {
public:
	int id;
	Score answerOnLike;
	Score answerOnDislike;

	Question(int id, Score answerOnLike, Score answerOnDislike) : id(id), answerOnLike(answerOnLike), answerOnDislike(answerOnDislike) {};
};