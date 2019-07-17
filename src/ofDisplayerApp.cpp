#include "ofDisplayerApp.h"

//--------------------------------------------------------------
void ofDisplayerApp::setup()
{
	ofBackground(0);

	midiCtrl::GetInstance()->init();
	midiCtrl::GetInstance()->addListener(this);
}

//--------------------------------------------------------------
void ofDisplayerApp::update()
{

}

//--------------------------------------------------------------
void ofDisplayerApp::draw()
{
	displayMgr::GetInstance()->drawDisplay(0, 0);
}


//--------------------------------------------------------------
void ofDisplayerApp::keyPressed(int key)
{

}


//--------------------------------------------------------------
void ofDisplayerApp::newMidiMessage(ofxMidiMessage & msg)
{
	auto type = ctrlMap::GetInstance()->midi2Ctrl[msg.control];
	if (type == eCtrl_ChangeProjectAlpha)
	{
		displayMgr::GetInstance()->setCoverAlpha(ofMap(msg.value, 0, 127, 255, 0));
	}

}

