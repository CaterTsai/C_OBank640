#pragma once

#include "SBase.h"

class SItaly01 : public SBase {

public:
	SItaly01()
		:SBase(eSItaly01)
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
	string getSceneName() { return "SItaly01"; }

private:

};