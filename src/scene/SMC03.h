#pragma once

#include "SBase.h"

class SMC03 : public SBase {

public:
	SMC03()
		:SBase(eSMC03)
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
	string getSceneName() { return "SMC03"; }

private:

};