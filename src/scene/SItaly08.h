#pragma once

#include "SBase.h"

class SItaly08 : public SBase {

public:
	SItaly08()
		:SBase(eSItaly08)
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
	string getSceneName() { return "SItaly08"; }

private:

};