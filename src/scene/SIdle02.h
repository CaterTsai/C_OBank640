#pragma once

#include "SBase.h"

class SIdle02 : public SBase {

public:
	SIdle02()
		:SBase(eSIdle02)
	{}

	void update(float delta) override {}
	void draw() override {
	};
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << getSceneName();
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	void start() override 
	{
	};
	void stop() override 
	{
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SIdle02"; }

private:

};