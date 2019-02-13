#pragma once

#include "SBase.h"

class SFrance06 : public SBase {

public:
	SFrance06()
		:SBase(eSFrance06)
	{}

	void updateFunc(float delta) override 
	{
		_dc.update(delta);
	}
	void drawFunc() override {
		displayMgr::GetInstance()->beginDisplay(eDisplayFront);
		ofSetColor(255);
		ofDrawCircle(cDisplayCanvasWidth * 0.5, cDisplayCanvasHeight * 0.25, cDisplayCanvasHeight * 0.1);
		displayMgr::GetInstance()->endDisplay();

		displayMgr::GetInstance()->beginDisplay(eDisplayBack);
		ofSetColor(255);
		_dc.draw();
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
		displayMgr::GetInstance()->setBGColor(ofColor(50, 50, 50), ofColor(0));
		displayMgr::GetInstance()->clearAllDisplay();
		_dc.start();
	};
	void stopFunc() override
	{
		_dc.stop();
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SFrance06"; }

private:
	DClouds _dc;
};