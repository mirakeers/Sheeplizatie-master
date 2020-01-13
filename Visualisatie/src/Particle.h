                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        #pragma once

#include "ofMain.h"
#include "ofxVec2f.h"


class ParticleProperties {
public:
	const int modesAmount = 2;
	enum Mode { simpleParticles, imageParts };
	Mode currentMode = simpleParticles;
	float size = 3;
	float hue = 0;
	float overlayOpacity = 10;
	float gravityTarget = 0.002;
};


class Particle {
public:
	//vector met alle targets die particle geweest is 
	vector<ofxVec2f> historyTargets;

	string id;

	ofxVec2f location;
	ofVec3f rotation;
	float scale;
	float o = 1;
	int currentPath;
	int currentVraag;

	ofxVec2f velocity;
	ofxVec2f acceleration;

	ofxVec2f target;
	float maxspeed;
	float maxforce;
	float gravitytarget;
	float frictiontarget;

	bool replay;
	ofColor c;
	ofImage* img;
	float imgScale;
	ofVec2f tileSize;
	ofVec2f relTargetPos; //The position, relative to the center of the image, where the particle will be targeted to

	int indexX;
	int indexY;

	const ParticleProperties* pp;

	Particle(string id, const int indexX, const int indexY, ParticleProperties* pp,
		ofxVec2f location, ofxVec2f target, ofVec3f rotation, float scale,
		float maxspeed, float maxforce, float gravitytarget, float frictiontarget,
		ofImage* img, float imgScale, ofVec2f tileSize) :
		id(id), indexX(indexX), indexY(indexY), pp(pp), location(location), target(target), rotation(rotation), scale(scale), maxspeed(maxspeed), maxforce(maxforce), gravitytarget(gravitytarget), frictiontarget(frictiontarget), img(img), imgScale(imgScale), tileSize(tileSize)
	{};

	void setup();
	void update(); 
	void draw();
	void updateRelTargetPos();
	void seek(ofxVec2f target);
	bool lerpRotationAndScaleTo(ofVec3f targetRotation, float targetScale, int framesAmount);
	void applyforce(ofxVec2f force);
	void setTarget(ofVec2f targett);
	void changeReplay();
};                                       