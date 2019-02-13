#include "ofApp.h"
#include "ofxCTHD512.h"


//--------------------------------------------------------------
void ofApp::setup(){
	
	ofBackground(0);

	initVideoMgr();

	//ofSetFrameRate(60);
	_mainTimer = ofGetElapsedTimef();
	
}

//--------------------------------------------------------------
void ofApp::update(){
	float delta = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta;

	
	

	videoMgr::GetInstance()->update();

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

#pragma region Video Mgr
void ofApp::initVideoMgr()
{
	for (int i = 0; i < cTrainVideoNum; i++)
	{
		videoMgr::GetInstance()->add((eVideoType)i, "videos/train/" + ofToString(i+1, 2, '0') + ".avi");
	}


}
#pragma endregion


