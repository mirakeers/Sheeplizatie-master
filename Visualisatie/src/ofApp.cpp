#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	/*
	-------PADS-------		----SLIDERS----
	 __   __   __   __		(1) (2) (3) (4)
	|48| |49| |50| |51|		 O	 O	 O	 O
	 __   __   __   __		(5) (6) (7) (8)
	|44| |45| |46| |47|		 O   O   O   O

	---------------------------PIANO---------------------------
	  49  51      54  56  58      61  63      66  68  70  
	48  50  52  53  55  57  59  60  62  64  65  67  69  71  72

	*/

	sliders["/slider1"] = Slider(&myParticleController.pp.size, 1, 10);
	sliders["/slider2"] = Slider(&myParticleController.pp.hue, 0, 255);
	sliders["/slider3"] = Slider(&myParticleController.pp.overlayOpacity, 50, 2);
	sliders["/slider4"] = Slider(&myParticleController.pp.gravityTarget, 0.005, 0.0005);
	buttons["/button64"] = &eff_convergence;
	buttons["/button65"] = &eff_shaker;
	buttons["/button67"] = &eff_cutslider;
	buttons["/button69"] = &eff_twist;
	buttons["/button71"] = &eff_slitscan;
	buttons["/button72"] = &eff_swell;
	togglers["/button48"] = [&](){
		myParticleController.pp.currentMode = (ParticleProperties::Mode)(((int)myParticleController.pp.currentMode + 1) % myParticleController.pp.modesAmount);
		if (myParticleController.pp.currentMode == ParticleProperties::simpleParticles) {
			myParticleController.currentImg = myParticleController.chooseImage();
			myParticleController.updateImgOfParticles();
		}
	};

	ofSetFrameRate(160);
	//ofSetFullscreen(true);
	ofSetWindowShape(1920, 1080);
	ofSetWindowPosition(0, 0);

	setupMidi();
	receiver.setup(PORT);

	fbo.allocate(ofGetScreenWidth(), ofGetScreenHeight(), GL_RGBA);
	fbo.begin();
	ofClear(0);
	fbo.end();
	fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight());
	myGlitch.setup(&fbo);

	vector<string> imgPaths;
	imgPaths.push_back("beeld-01.png");
	imgPaths.push_back("beeld-02.png");
	imgPaths.push_back("beeld-03.png");
	imgPaths.push_back("beeld-04.png");
	imgPaths.push_back("beeld-05.png");

	myParticleController.setup(imgPaths, ofGetScreenWidth()*0.6, ofVec2f(ofGetScreenWidth() / 2, ofGetScreenHeight() / 2), ofVec2f(0, ofGetScreenHeight() / 2));
}

//--------------------------------------------------------------
void ofApp::update(){
	ofxOscMessage ontvangenData;
	receiver.getNextMessage(ontvangenData);


	if (ontvangenData.getAddress() == "/getUserData") {
		string ontvangenUserId = ontvangenData.getArgAsString(0);
		int ontvangenVraagId = ontvangenData.getArgAsInt(1);
		int ontvangenPad = ontvangenData.getArgAsInt(2);

		Particle* particle = getParticle(ontvangenUserId);
		if (particle) {
			particle->historyTargets.push_back(myParticleController.targets[ontvangenVraagId][ontvangenPad]);
		}
	}

	if (ontvangenData.getAddress() == "/getNewUser") {
		string ontvangeUserId = ontvangenData.getArgAsString(0);
		int ontvangenVraagId = ontvangenData.getArgAsInt(1);

		myParticleController.addParticle(ontvangeUserId, 0, 1);
	}

	myParticleController.update();
	processMidiInfo();
	updateEffects();
	fbo.begin();
		switch(myParticleController.pp.currentMode) {
			case(ParticleProperties::imageParts) :
				ofBackground(0);
				break;
			case (ParticleProperties::simpleParticles) :
				fadeToBlack();
				break;
		}
		myParticleController.draw();
	fbo.end();

	
	if (ofGetFrameNum() % 80 == 0) {

		myParticleController.changeReplay();
		myParticleController.changeReplay();
		myParticleController.changeReplay();
		myParticleController.changeReplay();
	}
	

}

void ofApp::fadeToBlack() {
	ofSetColor(0, 3);
	ofDrawRectangle(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
	ofSetColor(255);
}


//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	ofSetColor(255);
	myGlitch.generateFx();
	fbo.draw(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
	if (saveFrame) {
		//ofImage img = fbo.readToPixels();
		ofSaveScreen(ofToString(ofGetFrameNum()) + ".png");
		saveFrame = false;
	}
	/*
	ofDrawCircle(1000, 100, 50, 50);
	ofDrawCircle(1200, 100, 50, 50);
	ofDrawCircle(1400, 100, 50, 50);
	ofDrawCircle(1600, 100, 50, 50);
	ofDrawCircle(1800, 100, 50, 50);*/
}

void ofApp::exit() {
	//delete myParticleController;
	midiIn.closePort();
	midiIn.removeListener(this);
}

Particle* ofApp::getParticle(string id) {
	for (Particle& particle : myParticleController.particles) {
		if (id == particle.id) {
			return &particle;
		}
	}
	return nullptr;
}

void ofApp::newMidiMessage(ofxMidiMessage& msg) {
	// make a copy of the latest message
	midiMessage = msg;
}

void ofApp::setupMidi() {
	ofSetLogLevel(OF_LOG_VERBOSE);

	midiIn.listPorts();
	midiIn.openPort(0);
	midiIn.ignoreTypes(false, false, false);
	midiIn.addListener(this);
	midiIn.setVerbose(false);
}

void ofApp::updateEffects() {
	myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE, eff_convergence);
	myGlitch.setFx(OFXPOSTGLITCH_SHAKER, eff_shaker);
	myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER, eff_cutslider);
	myGlitch.setFx(OFXPOSTGLITCH_TWIST, eff_twist);
	myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN, eff_slitscan);
	myGlitch.setFx(OFXPOSTGLITCH_SWELL, eff_swell);
}

void ofApp::processMidiInfo() {

	auto comp = [](const ofxMidiMessage & m1, const ofxMidiMessage & m2) {
		return m1.pitch == m2.pitch && m1.control == m2.control && m1.status == m2.status && m1.value == m2.value;
	};

	auto link = [&](bool button, string addr, float value, bool changed) {
		string b = (button ? "button" : "slider");
		addr = "/" + b + ofToString(addr);
		if (changed) {
			if (button) {
				if (buttons.count(addr) > 0) {
					*(buttons[addr]) = value;
				}
				else if (togglers.count(addr) > 0 && !value) {
					togglers[addr]();
				}
			}
			else {
				if (sliders.count(addr) > 0) {
					sliders[addr].set(value);
				}
			}
		}
		
	};
	if (midiMessage.pitch || midiMessage.control) {
		bool on = ofxMidiMessage::getStatusString(midiMessage.status) == "Note On";
		bool button = midiMessage.pitch;
		link(button, ofToString(button ? midiMessage.pitch : midiMessage.control), button ? (float)on : midiMessage.value/127.0, !comp(midiMessageOld, midiMessage));
		midiMessageOld = midiMessage;
	}
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_BACKSPACE) {
		saveFrame = true;
	}
	else {
		//myParticleController.addParticle();
	}



	//herhaal pad knop
	if (key == 'a') {
		cout << "knop detected";
		myParticleController.changeReplay();

	};

	
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == '1') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE, false);
	if (key == '2') myGlitch.setFx(OFXPOSTGLITCH_SHAKER, false);
	if (key == '3') myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER, false);
	if (key == '4') myGlitch.setFx(OFXPOSTGLITCH_TWIST, false);
	if (key == '5') myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN, false);
	if (key == '6') myGlitch.setFx(OFXPOSTGLITCH_SWELL, false);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	myParticleController.changeTarget();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
