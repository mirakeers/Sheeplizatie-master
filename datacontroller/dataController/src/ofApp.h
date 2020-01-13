#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "User.h"
#include "Question.h"
#include "Score.h"
#include "ofxJSON.h"

#define HOST "10.3.32.197"
#define SENDING_PORT 9000
#define RECEIVING_PORT 2344

class ofApp : public ofBaseApp{

	vector<User> users;
	vector<Question> questions;

	ofxOscSender sender;
	ofxOscReceiver receiver;

	public:
		void setup();
		void update();
		void draw();

		User* getUser(string id);
		Question* getQuestion(int id);
		vector<Question> getQuestions();
		User* processDataMessage(string userId, int questionId, int answer);
		User* processNewUserMessage(string id);

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
		
};
