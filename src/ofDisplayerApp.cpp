#include "ofDisplayerApp.h"

//--------------------------------------------------------------
void ofDisplayerApp::setup()
{
	ofBackground(0);
	_coverAlpha = 255;

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
	displayMgr::GetInstance()->drawToProjection();

	ofPushStyle();
	ofSetColor(0, 255 - _coverAlpha);
	ofFill();
	ofDrawRectangle(0, 0, cProjectionWindowWidth, cProjectionWindowHeight);
	ofPopStyle();
}


//--------------------------------------------------------------
void ofDisplayerApp::keyPressed(int key)
{
	switch (key)
	{
	case '1':
	case '2':
	case '3':
	{
		int id = key - '1';
		displayMgr::GetInstance()->enableDisplayControl(id);
		break;
	}
	case '0':
	{
		displayMgr::GetInstance()->disableDisplayControl();
		break;
	}
	case 'z':
	{
		displayMgr::GetInstance()->saveConfig("config/_displayConfig.xml");
		break;
	}
	}
}

//--------------------------------------------------------------
void ofDisplayerApp::mousePressed(int x, int y, int button)
{
	displayMgr::GetInstance()->mousePressedFromProjector(x, y);
}

//--------------------------------------------------------------
void ofDisplayerApp::mouseDragged(int x, int y, int button)
{
	displayMgr::GetInstance()->mouseDraggedFromProjector(x, y);
}

//--------------------------------------------------------------
void ofDisplayerApp::mouseReleased(int x, int y, int button)
{
	displayMgr::GetInstance()->mouseReleasedFromProject(x, y);
}

//--------------------------------------------------------------
void ofDisplayerApp::newMidiMessage(ofxMidiMessage & msg)
{
	auto type = ctrlMap::GetInstance()->midi2Ctrl[msg.control];
	if (type == eCtrl_ChangeProjectAlpha)
	{
		_coverAlpha = ofMap(msg.value, 0, 127, 0, 255);
	}

}

