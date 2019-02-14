#pragma once

#include "SBase.h"

class SFrance07 : public SBase {

public:
	SFrance07()
		:SBase(eSFrance07)
	{}

	void updateFunc(float delta) override {}
	void drawFunc() override {
		displayMgr::GetInstance()->beginDisplay(eDisplayFront);
		ofSetColor(255);

		ofPushMatrix();
		ofTranslate(cDisplayCanvasWidth * 0.5, cDisplayCanvasHeight * 0.5);
		videoMgr::GetInstance()->draw(eVideoWaterWave);
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
		milightMgr::GetInstance()->toCue(eSFrance07);
		videoMgr::GetInstance()->play(eVideoWaterWave);
	};
	void stopFunc() override 
	{
		videoMgr::GetInstance()->stop(eVideoWaterWave);
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SFrance07"; }

private:

};