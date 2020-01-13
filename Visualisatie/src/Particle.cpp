#include "Particle.h"

void Particle::setup() {
	velocity.set(0, 0);
	acceleration.set(0, 0);
	updateRelTargetPos();
	replay = false;



	historyTargets.push_back(target);
	o = historyTargets.size() - 1;
	replay = false;
}

void Particle::updateRelTargetPos() {
	relTargetPos = ofVec2f(-img->getWidth()*imgScale / 2 + indexX * tileSize.x, -img->getHeight()*imgScale / 2 + indexY * tileSize.y);
}

void Particle::update() {



	if (replay == false) {
		o = historyTargets.size() - 1;
		cout << o;
		cout << "if";
	}
	else {
		cout << "else";
		ofPoint delta = historyTargets[o] - location;
		float distBetween = sqrt(delta.x * delta.x + delta.y * delta.y);
		if (distBetween < 30) {

			if (o < historyTargets.size() - 1) {
				o++;
			}
		}
	}










	acceleration.x += ofRandom(-0.005, 0.005);
	acceleration.y += ofRandom(-0.005, 0.005);
	
	if (pp->currentMode == ParticleProperties::imageParts) {
		if (location.distance(ofxVec2f(ofGetScreenWidth() / 2, ofGetScreenHeight() / 2) + relTargetPos) > 2) {
			seek(ofxVec2f(ofGetScreenWidth() / 2, ofGetScreenHeight() / 2) + relTargetPos);
			ofxVec2f desired = ofxVec2f(ofGetScreenWidth() / 2, ofGetScreenHeight() / 2) + relTargetPos - location;
			float estimatedFramesAmount = desired.length() / maxspeed;
			lerpRotationAndScaleTo(ofVec3f(0, 0, 0), 1, estimatedFramesAmount);
		}
		else {
			acceleration.x = acceleration.y = velocity.x = velocity.y = 0;
		}

	} else if (pp->currentMode == ParticleProperties::simpleParticles) {
		seek(historyTargets[o]);
	}

	velocity += acceleration;
	velocity.limit(maxspeed);
	location += velocity;

	c = ofColor::fromHsb(ofMap(location.y, 0, ofGetScreenHeight(), 70, 270), (100 + location.x / 7.0), 255);
}	

void Particle::draw() {

	if (pp->currentMode == ParticleProperties::imageParts) {
		ofPushMatrix();

		ofTranslate(location);
		ofScale(ofVec2f(scale, scale));
		ofRotateX(rotation.x),
		ofRotateY(rotation.y);
		ofRotateZ(rotation.z);

		ofVec2f relPPos = ofVec2f(indexX * tileSize.x, indexY * tileSize.y);

		float x = 0;
		float y = 0;
		float w = tileSize.x;
		float h = tileSize.y;
		float sx = relPPos.x / imgScale;
		float sy = relPPos.y / imgScale;
		float sw = tileSize.x / imgScale;
		float sh = tileSize.y / imgScale;
		ofSetColor(255);
		img->drawSubsection(x, y, w, h, sx, sy, sw, sh);

		ofPopMatrix();
	}
	if (pp->currentMode == ParticleProperties::simpleParticles) {

		ofColor color;
		color.setHsb(pp->hue, 120, 255);
		ofSetColor(c);
		ofDrawEllipse(location.x, location.y, pp->size, pp->size);
	}
}

void Particle::seek(ofxVec2f target) {
	ofxVec2f desired;
	desired = target - location;
	desired = desired * frictiontarget;
	desired *= maxspeed;
	desired.normalize();
	desired *= 2;
	ofxVec2f steer;
	steer = desired - velocity;
	steer.getLimited(maxforce);
	switch (pp->currentMode) {
		case(ParticleProperties::imageParts):
			applyforce(steer);
			break;
		case (ParticleProperties::simpleParticles):
			applyforce(steer * gravitytarget);
			break;
	}
	
}

bool Particle::lerpRotationAndScaleTo(ofVec3f targetRotation, float targetScale, int framesAmount) {
	bool goalAchieved = false;

	ofVec3f amountToRotate = targetRotation - rotation;
	float amountToScale = targetScale - scale;

	if (framesAmount > 4) {
		rotation += (amountToRotate / framesAmount);
		scale += (amountToScale / framesAmount);
	}
	else {
		rotation = targetRotation;
		scale = targetScale;
		goalAchieved = true;
	}
	return goalAchieved;
}

void Particle::applyforce(ofxVec2f force) {
	acceleration += force;
}

void Particle::setTarget(ofVec2f targett) {
	target.x = targett.x;
	target.y = targett.y;

	historyTargets.push_back(ofxVec2f(targett.x, targett.y));
}

void Particle::changeReplay() {
	o = 0;
	replay = true;
	cout << "changeReplay uitgevoerd";
	
	location.x = 0;
	location.y = ofGetWindowHeight() / 2;
}