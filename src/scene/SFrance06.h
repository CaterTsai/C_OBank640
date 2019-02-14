#pragma once

#include "SBase.h"

class SFrance06 : public SBase {

public:
	SFrance06()
		:SBase(eSFrance06)
	{
		_moon.load("moonLight.png");
	}

	void updateFunc(float delta) override 
	{
		_dc.update(delta);
	}
	void drawFunc() override {
		displayMgr::GetInstance()->beginDisplay(eDisplayFront);
		ofSetColor(255);
		float width = cDisplayCanvasWidth * 0.5;
		float height = width * _moon.getHeight() / _moon.getWidth();
		_moon.draw((cDisplayCanvasWidth - width) * 0.5, height * -0.2, width, height);
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
		milightMgr::GetInstance()->toCue(eSFrance06);
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
	ofImage _moon;
};