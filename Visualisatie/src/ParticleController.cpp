#include "ParticleController.h"

void ParticleController::setup(vector<string> imgPaths, float projectionWidth, ofVec2f initTargetCenter, ofVec2f initSourcePosition) {
	targetCenter = initTargetCenter;
	sourcePosition = initSourcePosition;

	

	for (string& imgPath : imgPaths) {
		ofImage img;
		img.load(imgPath);
		imgs.push_back(img);
	}

	currentImg = chooseImage();

	imgProjectionSize = ofVec2f(projectionWidth, projectionWidth * imgs[0].getHeight() / imgs[0].getWidth());
	

	ofVec2f p = ofVec2f(ofGetScreenWidth() / 2, ofGetScreenHeight() / 2);

	float radius3 = (ofGetScreenHeight() / 2) -50;
	float radius2 = radius3  - 150;
	float radius1 = radius2  - 150;

	/*
	vector<ofVec2f> row;
	row.push_back(p + ofVec2f(cos(0) * radius1, sin(0) * radius1));
	row.push_back(p + ofVec2f(cos(0) * radius2, sin(0) * radius2));
	row.push_back(p + ofVec2f(cos(0) * radius3, sin(0) * radius3));
	targets.push_back(row);

	row.clear();
	row.push_back(p + ofVec2f(cos(TWO_PI * 1 / 6) * radius1, sin(TWO_PI * 1 / 6) * radius1));
	row.push_back(p + ofVec2f(cos(TWO_PI * 1 / 6) * radius2, sin(TWO_PI * 1 / 6) * radius2));
	row.push_back(p + ofVec2f(cos(TWO_PI * 1 / 6) * radius3, sin(TWO_PI * 1 / 6) * radius3));
	targets.push_back(row);

	row.clear();
	row.push_back(p + ofVec2f(cos(TWO_PI * 2 / 6) * radius1, sin(TWO_PI * 2 / 6) * radius1));
	row.push_back(p + ofVec2f(cos(TWO_PI * 2 / 6) * radius2, sin(TWO_PI * 2 / 6) * radius2));
	row.push_back(p + ofVec2f(cos(TWO_PI * 2 / 6) * radius3, sin(TWO_PI * 2 / 6) * radius3));
	targets.push_back(row);

	row.clear();
	row.push_back(p + ofVec2f(cos(TWO_PI * 3 / 6) * radius1, sin(TWO_PI * 3 / 6) * radius1));
	row.push_back(p + ofVec2f(cos(TWO_PI * 3 / 6) * radius2, sin(TWO_PI * 3 / 6) * radius2));
	row.push_back(p + ofVec2f(cos(TWO_PI * 3 / 6) * radius3, sin(TWO_PI * 3 / 6) * radius3));
	targets.push_back(row);

	row.clear();
	row.push_back(p + ofVec2f(cos(TWO_PI * 4 / 6) * radius1, sin(TWO_PI * 4 / 6) * radius1));
	row.push_back(p + ofVec2f(cos(TWO_PI * 4 / 6) * radius2, sin(TWO_PI * 4 / 6) * radius2));
	row.push_back(p + ofVec2f(cos(TWO_PI * 4 / 6) * radius3, sin(TWO_PI * 4 / 6) * radius3));
	targets.push_back(row);

	row.clear();
	row.push_back(p + ofVec2f(cos(TWO_PI * 5 / 6) * radius1, sin(TWO_PI * 5 / 6) * radius1));
	row.push_back(p + ofVec2f(cos(TWO_PI * 5 / 6) * radius2, sin(TWO_PI * 5 / 6) * radius2));
	row.push_back(p + ofVec2f(cos(TWO_PI * 5 / 6) * radius3, sin(TWO_PI * 5 / 6) * radius3));
	targets.push_back(row);
	*/
	vector<ofxVec2f> row;
	row.push_back(ofxVec2f(100, ofGetWindowHeight() / 4));
	row.push_back(ofxVec2f(100, (ofGetWindowHeight() / 4) * 2));
	row.push_back(ofxVec2f(100, (ofGetWindowHeight() / 4) * 3));
	targets.push_back(row);

	row.clear();
	row.push_back(ofxVec2f(((ofGetWindowWidth() - 100) / 6) * 1 + 100, (ofGetWindowHeight() / 10) * 2));
	row.push_back(ofxVec2f(((ofGetWindowWidth() - 100) / 6) * 1 + 100, (ofGetWindowHeight() / 10) * 5));
	row.push_back(ofxVec2f(((ofGetWindowWidth() - 100) / 6) * 1 + 100, (ofGetWindowHeight() / 10) * 8));
	targets.push_back(row);

	row.clear();
	row.push_back(ofxVec2f(((ofGetWindowWidth() - 100) / 6) * 2 + 100, (ofGetWindowHeight() / 10) * 2));
	row.push_back(ofxVec2f(((ofGetWindowWidth() - 100) / 6) * 2 + 100, (ofGetWindowHeight() / 10) * 5));
	row.push_back(ofxVec2f(((ofGetWindowWidth() - 100) / 6) * 2 + 100, (ofGetWindowHeight() / 10) * 8));
	targets.push_back(row);

	row.clear();
	row.push_back(ofxVec2f(((ofGetWindowWidth() - 100) / 6) * 3 + 100, (ofGetWindowHeight() / 10) * 2));
	row.push_back(ofxVec2f(((ofGetWindowWidth() - 100) / 6) * 3 + 100, (ofGetWindowHeight() / 10) * 5));
	row.push_back(ofxVec2f(((ofGetWindowWidth() - 100) / 6) * 3 + 100, (ofGetWindowHeight() / 10) * 8));
	targets.push_back(row);

	row.clear();
	row.push_back(ofxVec2f(((ofGetWindowWidth() - 100) / 6) * 4 + 100, (ofGetWindowHeight() / 10) * 2));
	row.push_back(ofxVec2f(((ofGetWindowWidth() - 100) / 6) * 4 + 100, (ofGetWindowHeight() / 10) * 5));
	row.push_back(ofxVec2f(((ofGetWindowWidth() - 100) / 6) * 4 + 100, (ofGetWindowHeight() / 10) * 8));
	targets.push_back(row);

	row.clear();
	row.push_back(ofxVec2f(((ofGetWindowWidth() - 100) / 6) * 5 + 100, (ofGetWindowHeight() / 10) * 2));
	row.push_back(ofxVec2f(((ofGetWindowWidth() - 100) / 6) * 5 + 100, (ofGetWindowHeight() / 10) * 5));
	row.push_back(ofxVec2f(((ofGetWindowWidth() - 100) / 6) * 5 + 100, (ofGetWindowHeight() / 10) * 8));
	targets.push_back(row);
}

void ParticleController::update() {
	for (Particle& p : particles) {
		p.gravitytarget = pp.gravityTarget;
		p.update();
	}
}

void ParticleController::draw() {
	for (Particle& p : particles) {
		p.draw();
	}
}


void ParticleController::addParticle(string id, int currentQuestion, int currentPath) {
	float imgScale = imgProjectionSize.x / imgs[0].getWidth();
	ofVec2f newPSize = ofVec2f(1, 1);
	if (!particles.empty()) {
		newPSize = calculateParticleSize(particles.size() + 1);
	}
	updateParticles(newPSize);

	ofxVec2f target = targets[currentQuestion][currentPath];

	ofVec3f rotation = ofVec3f(ofRandom(-30, 30), ofRandom(-30, 30), ofRandom(-30, 30));
	float pScale = ofRandom(0.5, 2);
	float maxSpeed = Style::getAverageMaxSpeed() * ofRandom(0.9, 1.1);

	int ix = 0;
	int iy = 0;

	/*Particle lastParticle = particles.back();
	if (lastParticle.indexX < currentGridX - 1) {
	ix = lastParticle.indexX + 1;
	iy = lastParticle.indexY;
	}
	else {
	ix = 0;
	iy = lastParticle.indexY + 1;
	}*/



	Particle p = Particle(id, ix, iy, &pp,
		ofxVec2f(sourcePosition), target, rotation, pScale,
		maxSpeed, Style::getAverageMaxForce(), pp.gravityTarget, Style::getFrictiontarget(),
		currentImg, imgScale, newPSize);
	p.setup();
	particles.push_back(p);
}

ofImage* ParticleController::chooseImage() {
	return &imgs[(int)ofRandom(0, imgs.size())];
}

void ParticleController::updateImgOfParticles() {
	for (Particle& particle : particles) {
		particle.img = currentImg;
	}
}

void ParticleController::updateParticles(ofVec2f pSize) {
	int i(0);
	for (int iy(0); iy < currentGridY; iy++) {
		for (int ix(0); ix < currentGridX; ix++) {
			if (i >= particles.size() - 1) {
				ix = iy = 100000;
			}
			else {
				i++;
				particles[i].tileSize = pSize;
				particles[i].indexX = ix;
				particles[i].indexY = iy;
				particles[i].updateRelTargetPos();
			}
		}
	}
}

ofVec2f ParticleController::calculateParticleSize(int particleAmount) {
	float imageArea = imgProjectionSize.x * imgProjectionSize.y;
	float particleArea = imageArea / particleAmount;

	float imageRatio = imgProjectionSize.x / imgProjectionSize.y;

	ofVec2f particleSize = ofVec2f(sqrt(particleArea / imageRatio)* imageRatio, sqrt(particleArea / imageRatio));

	currentGridX = ceil(imgProjectionSize.x / particleSize.x);
	currentGridY = ceil(imgProjectionSize.y / particleSize.y);

	return particleSize;
}

void ParticleController::changeTarget() {

	/*for (int i = 0; i < particles.size(); ++i) {
		particles[i].setTarget(targets[o + 1]);
	}
	o++;*/
}



void ParticleController::changeReplay() {
	if (particles.size() > 0) {//1500 voorbij

		float r = ofRandom(0, particles.size());
		float o = particles[r].o + 1;
		
		float x = particles[r].location.x;

		if (o == 5) {
			if (x > ofGetScreenWidth() * 0.85) { particles[r].changeReplay(); };
		}

		cout << "functie 1";
	}
}