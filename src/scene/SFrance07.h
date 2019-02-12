#pragma once

#include "SBase.h"

class SFrance07 : public SBase {

public:
	SFrance07()
		:SBase(eSFrance07)
	{}

	void updateFunc(float delta) override {}
	void drawFunc() override {
	};
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << getSceneName();
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	void startFunc() override 
	{
	};
	void stopFunc() override 
	{
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SFrance07"; }

private:

};