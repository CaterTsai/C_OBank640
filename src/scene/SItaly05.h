#pragma once

#include "SBase.h"

class SItaly05 : public SBase {

public:
	SItaly05()
		:SBase(eSItaly05)
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
	string getSceneName() { return "SItaly05"; }

private:

};