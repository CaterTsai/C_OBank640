#pragma once

#include "SBase.h"
class SIdle01 : public SBase {

public:
	SIdle01()
		:SBase(eSIdle01)
	{}

	void update(float delta) override 
	{
		_dTrain.update(delta);
	}
	void draw() override {
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
	void start() override 
	{
		displayMgr::GetInstance()->setBGMode(true);
		displayMgr::GetInstance()->setBGColor(ofColor(0));
		displayMgr::GetInstance()->clearAllDisplay();
		_dTrain.start();
		
	};
	void stop() override 
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