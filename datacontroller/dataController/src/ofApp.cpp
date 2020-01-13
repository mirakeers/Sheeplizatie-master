#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	sender.setup(HOST, SENDING_PORT);
	receiver.setup(RECEIVING_PORT);

	ofSetFrameRate(60);
	//questions = getQuestions();

	/*for (int i = 0; i < 75; i++) {
		ofxOscMessage m;
		User* newUser = processNewUserMessage(to_string(users.size()));
		m.setAddress("/getNewUser");
		m.addStringArg(newUser->id);
		m.addIntArg(newUser->lastAnsweredQuestionId);
		sender.sendMessage(m, false);
	}*/
}
//--------------------------------------------------------------
void ofApp::update(){
	while (receiver.hasWaitingMessages()) {
		cout << "trest";
		ofxOscMessage m;
		receiver.getNextMessage(m);
		if (m.getAddress() == "/newUser") {
			
			//Receive the message
			string userId = m.getArgAsString(0);

			//Process data
			User* newUser = processNewUserMessage(userId);

			//Send a message
			ofxOscMessage m;
			m.setAddress("/getNewUser");
			m.addStringArg(newUser->id);
			m.addIntArg(newUser->lastAnsweredQuestionId);
			sender.sendMessage(m, false);
			
		}
		if (m.getAddress() == "/questions") {
			//Receive the message
			string data = m.getArgAsString(0);
			ofxJSONElement json(data);

			//Process data
			if (true) {
				cout << "e json has been deparsed" << endl;
				for (int i = 0; i < json.size(); i++) {
					int questionId = 1 + json[i]["id"].asInt();
					int likeS = json[i]["lsheep"].asInt();
					int likeG = json[i]["lgoedgelovig"].asInt();
					int likeD = json[i]["ldenker"].asInt();
					int dislikeS = json[i]["dsheep"].asInt();
					int dislikeG = json[i]["dgoedgelovig"].asInt();
					int dislikeD = json[i]["ddenker"].asInt();
					questions.push_back(Question(questionId, Score(likeS, likeG, likeD), Score(dislikeS, dislikeG, dislikeD)));
				}
			}
		}
		if (m.getAddress() == "/questionAnswered") {
			//Receive the message
			string userId = m.getArgAsString(0);
			int questionId = 1 + (int) m.getArgAsFloat(1);
			int answer = (int) m.getArgAsFloat(2);
			cout << userId << questionId << answer << endl;
			
			//Process data
			User* affectedUser = processDataMessage(userId, questionId, answer);

			if (affectedUser) {
				int pathNumber = 1;
				if (affectedUser->currentS > affectedUser->currentG && affectedUser->currentS > affectedUser->currentD)
					pathNumber = 0;
				if (affectedUser->currentD > affectedUser->currentS && affectedUser->currentD > affectedUser->currentG)
					pathNumber = 2;

				//Send a message
				ofxOscMessage m;
				m.setAddress("/getUserData");
				m.addStringArg(affectedUser->id);
				m.addIntArg(affectedUser->lastAnsweredQuestionId);
				m.addIntArg(pathNumber);
				sender.sendMessage(m, false);
			}
			
		}
	}
	/*if (ofGetFrameNum() % 5  == 0) {

		//Random values for testing:
		string userId = to_string((int) ofRandom(0, users.size()));
		User* user = getUser(userId);
		int questionId = user->lastAnsweredQuestionId + 1;
		int answer = (int)ofRandom(0, 2);
		//til here

		if (questionId < questions.size()) {
			User* affectedUser = processDataMessage(userId, questionId, answer);

			int pathNumber = 1;
			if (affectedUser->currentS > affectedUser->currentG && affectedUser->currentS > affectedUser->currentD)
				pathNumber = 0;
			if (affectedUser->currentD > affectedUser->currentS && affectedUser->currentD > affectedUser->currentG)
				pathNumber = 2;

			ofxOscMessage m;
			m.setAddress("/getUserData");
			m.addStringArg(affectedUser->id);
			m.addIntArg(affectedUser->lastAnsweredQuestionId);
			m.addIntArg(pathNumber);
			sender.sendMessage(m, false);
		}
	}*/
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	for (int i = 0; i < users.size(); i++) {
		ofDrawBitmapString("User " + users[i].id + ":", 20, 20 + i*20);
		ofDrawBitmapString("Scores = (" + to_string(users[i].currentS) + ", " + to_string(users[i].currentG) + ", " + to_string(users[i].currentD) + ")", 90, 20 + i * 20);
	}
}
User* ofApp::processDataMessage(string userId, int questionId, int answer) {

	Question* question = getQuestion(questionId);
	if (question) {
		User* user = getUser(userId);
		if (user) {
			user->lastAnsweredQuestionId = question->id;
			if (answer == 1) {
				user->currentS += question->answerOnLike.sValue;
				user->currentG += question->answerOnLike.gValue;
				user->currentD += question->answerOnLike.dValue;
			}
			else {
				user->currentS += question->answerOnDislike.sValue;
				user->currentG += question->answerOnDislike.gValue;
				user->currentD += question->answerOnDislike.dValue;
			}
			
		}
		else {
			if (answer == 1) {
				User newUser = User(userId, question->answerOnLike.sValue, question->answerOnLike.gValue, question->answerOnLike.dValue, question->id);
				users.push_back(newUser);
			}
			else {
				User newUser = User(userId, question->answerOnDislike.sValue, question->answerOnDislike.gValue, question->answerOnDislike.dValue, question->id);
				users.push_back(newUser);
			}
		}
	}

	return getUser(userId);
}

User* ofApp::processNewUserMessage(string userId) {

	//string userId = "3";
	User* existingUser = getUser(userId);
	if (!existingUser) {
		User newUser = User(userId, 0, 0, 0, 0);
		users.push_back(newUser);
		return getUser(userId);
	}
	return existingUser;
}


User* ofApp::getUser(string id) {
	for (User& user : users) {
		if (id == user.id) {
			return &user;
		}
	}
	return nullptr;
}



Question* ofApp::getQuestion(int id) {
	for (Question& question : questions) {
		if (id == question.id) {
			return &question;
		}
	}
	return nullptr;
}

vector<Question> ofApp::getQuestions() {
	vector<Question> resultaat;
	resultaat.push_back(Question(1, Score(1, 2, 3), Score(3, 2, 1)));
	resultaat.push_back(Question(2, Score(2, 3, 1), Score(2, 1, 3)));
	resultaat.push_back(Question(3, Score(3, 2, 1), Score(1, 2, 3)));
	resultaat.push_back(Question(4, Score(1, 3, 2), Score(3, 1, 2)));
	resultaat.push_back(Question(5, Score(1, 2, 3), Score(3, 2, 1)));
	//resultaat.push_back(Question(6, Score(2, 3, 1), Score(2, 1, 3)));
	//resultaat.push_back(Question(7, Score(3, 2, 1), Score(1, 2, 3)));
	//resultaat.push_back(Question(8, Score(1, 3, 2), Score(3, 1, 2)));
	//resultaat.push_back(Question(9, Score(1, 2, 3), Score(3, 2, 1)));
	//resultaat.push_back(Question(10, Score(2, 3, 1), Score(2, 1, 3)));
	return resultaat;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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
