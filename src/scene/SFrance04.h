#pragma once

#include "SBase.h"

class SFrance04 : public SBase {

public:
	SFrance04()
		:SBase(eSFrance04)
	{}

	void updateFunc(float delta) override {}
	void drawFunc() override {
		displayMgr::GetInstance()->beginDisplay(eDisplayFront);
		ofSetColor(255);

		ofPushMatrix();
		ofTranslate(cDisplayCanvasWidth * 0.5, cDisplayCanvasHeight * 0.5);
		videoMgr::GetInstance()->draw(eVideoDarkOcean);
		ofPopMatrix();
		displayMgr::GetInstance()->endDisplay();
	};
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << getSceneName();
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	void startFunc() override
	{
		displayMgr::GetInstance()->clearAllDisplay();
		videoMgr::GetInstance()->play(eVideoDarkOcean);
	};
	void stopFunc() override
	{
		videoMgr::GetInstance()->stop(eVideoDarkOcean);
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SFrance04"; }

private:

};