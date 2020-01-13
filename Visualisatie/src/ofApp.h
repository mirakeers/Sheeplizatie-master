#pragma once

#define PORT 9000

#include "ofMain.h"
#include "ParticleController.h"
#include "Style.h"
#include "ofxPostGlitch.h"
#include "ofxMidi.h"
#include "Particle.h"
#include "ofxOsc.h"

class Slider {
public:
	Slider(float *value, float min, float max) {
		this->min = min;
		this->max = max;
		this->value = value;
	}
	Slider() {}
	void set(float val) {
		val = MIN(MAX(val, 0), 1);
		*value = ofMap(val, 0, 1, min, max);
	}
private:
	float min;
	float max;
	float *value;
};

class ofApp : public ofBaseApp, public ofxMidiListener {
	//ParticleController* myParticleController;
	ParticleController myParticleController;
	ofFbo fbo;
	ofxPostGlitch	myGlitch;
	bool saveFrame = false;

	std::map<string, Slider> sliders;
	std::map<string, bool *> buttons;
	std::map<string, std::function<void()>> togglers;

	public:
		void setup();
		void update();
		void draw();
		void exit();
		void fadeToBlack();
		void setupMidi();
		void processMidiInfo();
		void updateEffects();
		Particle* getParticle(string id);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void newMidiMessage(ofxMidiMessage& eventArgs);
		stringstream text;

		ofxMidiIn midiIn;
		ofxMidiMessage midiMessage;
		ofxMidiMessage midiMessageOld;

		ofxOscReceiver receiver;

		bool eff_convergence;
		bool eff_shaker;
		bool eff_cutslider;
		bool eff_twist;
		bool eff_slitscan;
		bool eff_swell;

};
