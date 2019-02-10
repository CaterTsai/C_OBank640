#pragma once

#include "SBase.h"

class SFrance02 : public SBase {

public:
	SFrance02()
		:SBase(eSFrance02)
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
	string getSceneName() { return "SFrance02"; }

private:

};