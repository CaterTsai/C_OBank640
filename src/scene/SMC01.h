#pragma once

#include "SBase.h"

class SMC01 : public SBase {

public:
	SMC01()
		:SBase(eSMC01)
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
	string getSceneName() { return "SMC01"; }

private:

};