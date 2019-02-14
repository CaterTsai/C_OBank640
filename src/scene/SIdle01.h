#pragma once

#include "SBase.h"
class SIdle01 : public SBase {

public:
	SIdle01()
		:SBase(eSIdle01)
	{}

	void updateFunc(float delta) override 
	{
		_dTrain.update(delta);
	}
	void drawFunc() override {

		displayMgr::GetInstance()->beginDisplay(eDisplayFront);
		ofSetColor(255);
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
		displayMgr::GetInstance()->setBGMode(false, OF_GRADIENT_CIRCULAR);
		displayMgr::GetInstance()->setBGColor(ofColor(50), ofColor(0));
		displayMgr::GetInstance()->clearAllDisplay();

		milightMgr::GetInstance()->toCue(0);
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
	string getSceneName() { return "SIdle01"; }

private:
	DTrain _dTrain;
};