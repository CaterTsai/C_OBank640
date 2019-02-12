#pragma once

#include "SBase.h"

class SFrance04 : public SBase {

public:
	SFrance04()
		:SBase(eSFrance04)
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
	string getSceneName() { return "SFrance04"; }

private:

};