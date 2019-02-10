#include "ofApp.h"
#include "ofxCTHD512.h"


//--------------------------------------------------------------
void ofApp::setup(){
	_milight.setup();
	ofBackground(0);

	initVideoMgr();


	_bg.load("starNight.jpg");

	//ofSetFrameRate(60);
	_mainTimer = ofGetElapsedTimef();
	
}

//--------------------------------------------------------------
void ofApp::update(){
	float delta = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta;

	_milight.update(delta);
	
	_dTest.update(delta);


	videoMgr::GetInstance()->update();

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	_bg.draw(0, 0);
	//_milight.draw(0, 0);

	_dTest.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case 'q':
	{
		_milight.nextCue();
		break;
	}
	case 'w':
	{
		_milight.prevCue();
		break;
	}
	case 'a':
	{
		_dTest.start();
		break;
	}
	}
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


