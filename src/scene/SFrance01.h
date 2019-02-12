#pragma once

#include "SBase.h"
#include "DClouds.h"

class SFrance01 : public SBase {

public:
	SFrance01()
		:SBase(eSFrance01)
	{}

	void updateFunc(float delta) override 
	{
		_dCloud.update(delta);
	}
	void drawFunc() override {
		displayMgr::GetInstance()->beginDisplay(eDisplayFront);
		ofSetColor(255);
		_dCloud.draw();
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
		displayMgr::GetInstance()->setBGColor(ofColor(24, 168, 235), ofColor(194, 234, 255));
		displayMgr::GetInstance()->clearAllDisplay();
		_dCloud.start();
	};
	void stopFunc() override 
	{
		_dCloud.stop();
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SFrance01"; }

private:
	DClouds _dCloud;
};