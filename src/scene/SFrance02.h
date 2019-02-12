#pragma once

#include "SBase.h"

class SFrance02 : public SBase {

public:
	SFrance02()
		:SBase(eSFrance02)
	{}

	void updateFunc(float delta) override 
	{
		_dBreeze.update(delta);
	}
	void drawFunc() override {
		
		displayMgr::GetInstance()->beginDisplay(eDisplayFront);
		ofSetColor(255);
		_dBreeze.draw();
		displayMgr::GetInstance()->endDisplay();
	};
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << getSceneName();
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	void startFunc() override 
	{
		displayMgr::GetInstance()->setBGMode(false, OF_GRADIENT_LINEAR);
		displayMgr::GetInstance()->setBGColor(ofColor(12, 255, 161), ofColor(19, 150, 56));
		displayMgr::GetInstance()->clearAllDisplay();
		_dBreeze.start();
	};
	void stopFunc() override 
	{
		_dBreeze.stop();;
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SFrance02"; }

private:
	DBreeze _dBreeze;
};