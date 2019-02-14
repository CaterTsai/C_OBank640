#pragma once

#include "SBase.h"

class SFrance05 : public SBase {

public:
	SFrance05()
		:SBase(eSFrance05)
	{}

	void updateFunc(float delta) override {
		_dTail.update(delta);
	}
	void drawFunc() override {
		displayMgr::GetInstance()->beginDisplay(eDisplayFront);
		_dTail.draw();
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
		displayMgr::GetInstance()->setBGColor(ofColor(0), ofColor(20, 0, 50));
		displayMgr::GetInstance()->clearAllDisplay();
		milightMgr::GetInstance()->toCue(eSFrance05);
		_dTail.start();

	};
	void stopFunc() override
	{
		_dTail.stop();
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SFrance05"; }

private:
	DTail _dTail;
};