#pragma once

#include "SBase.h"

class SItaly09 : public SBase {

public:
	SItaly09()
		:SBase(eSItaly09)
	{}

	void update(float delta) override {}
	void draw() override {
		//displayMgr::GetInstance()->updateOnUnitBegin(eBack, true);
		//postFilter::GetInstance()->_postMgr[eBack].begin();
		//ofFill();
		//ofSetColor(255);
		//	//ofDrawRectangle(0, 0, 1920, 1080);
		//postFilter::GetInstance()->_postMgr[eBack].end();
		//displayMgr::GetInstance()->updateOnUnitEnd(eBack);
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
	string getSceneName() { return "SItaly09"; }

private:

};