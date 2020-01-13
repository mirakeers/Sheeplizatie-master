#pragma once
#include "ofMain.h"
#include "Particle.h"
#include "Style.h"
#include <limits>

class ParticleController {
public:
	ofVec2f sourcePosition;
	vector<ofImage> imgs;

	ofImage* currentImg;

	ofVec2f imgProjectionSize;
	ofVec2f targetCenter;

	vector<Particle> particles;
	vector< vector<ofxVec2f> > targets;
	float o;
	ParticleProperties pp;

	int currentGridX;
	int currentGridY;

	//ParticleController(int particleAmount, string imgPath, float projectionWidth, ofVec2f targetCenter, ofVec2f sourcePosition);
	void update();
	void draw();
    void changeTarget();
	ofImage* chooseImage();
	void updateImgOfParticles();
	void setup(vector<string> imgPaths, float projectionWidth, ofVec2f initTargetCenter, ofVec2f initSourcePosition);
	void changeReplay();

	ofVec2f calculateParticleSize(int particleAmount);
	void addParticle(string id, int currentQuestion, int currentPath);
	void updateParticles(ofVec2f pSize);
};