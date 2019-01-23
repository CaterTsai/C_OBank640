#include "ofApp.h"
#include "ofxCTHD512.h"


//--------------------------------------------------------------
void ofApp::setup(){
	_milight.setup();
	ofBackground(0);

	_mainTimer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
	float delta = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta;

	_milight.update(delta);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	_milight.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case 'q':
	{
		_milight.playCue();
		break;
	}
	case 'w':
	{
		_milight.nextCue();
		break;
	}
	}
}
