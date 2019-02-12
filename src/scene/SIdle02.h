#pragma once

#include "SBase.h"

class SIdle02 : public SBase {

public:
	SIdle02()
		:SBase(eSIdle02)
	{}

	void updateFunc(float delta) override
	{
		_dTrain.update(delta);
	}
	void drawFunc() override {
		displayMgr::GetInstance()->beginDisplay(eDisplayFront);
		_dTrain.draw();
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
		displayMgr::GetInstance()->setBGMode(true);
		displayMgr::GetInstance()->setBGColor(ofColor(0));
		displayMgr::GetInstance()->clearAllDisplay();
		_dTrain.start();

	};
	void stopFunc() override
	{
		_dTrain.stop();
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override
	{
		_dTrain.trigger(ctrl);
	};

	string getSceneName() { return "SIdle02"; }

private:
	DTrain _dTrain;
};