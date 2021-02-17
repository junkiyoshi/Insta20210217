#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 100, true, true, true);

	this->box2d.init();
	this->box2d.setGravity(0, 50);
	this->box2d.createBounds();
	this->box2d.setFPS(60);
	this->box2d.registerGrabbing();
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = this->circle_list.size() - 1; i > -1; i--) {

		this->life_list[i] -= 1;

		if (this->life_list[i] < 0) {

			this->circle_list.erase(this->circle_list.begin() + i);
			this->radius_list.erase(this->radius_list.begin() + i);
			this->life_list.erase(this->life_list.begin() + i);
		}
	}

	for(int i = 0; i < 3; i++) {

		auto radius = ofRandom(1, 3);

		auto circle = make_shared<ofxBox2dCircle>();
		circle->setPhysics(0.5, 0.03, 0.1);
		circle->setup(this->box2d.getWorld(), ofRandom(ofGetWidth() * 0.5 - radius, ofGetWidth() * 0.5 + radius), 100 + radius, radius);
		circle->setRotation(ofRandom(360));
		this->circle_list.push_back(circle);
		this->radius_list.push_back(radius);
		this->life_list.push_back(400);
	}

	this->box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	string word = "PCD 2021";
	this->font.drawStringAsShapes(word, ofGetWidth() * 0.5 + this->font.stringWidth(word) * -0.5, ofGetHeight() * 0.5 + this->font.stringHeight(word) * 0.5);

	for (int i = 0; i < this->circle_list.size(); i++) {

		ofDrawCircle(glm::vec2(this->circle_list[i]->getPosition()), this->radius_list[i]);
	}
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}