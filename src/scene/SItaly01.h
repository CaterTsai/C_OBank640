#pragma once

#include "SBase.h"

class SItaly01 : public SBase {

public:
	SItaly01()
		:SBase(eSItaly01)
	{}

	void updateFunc(float delta) override {

	}
	void drawFunc() override {
		displayMgr::GetInstance()->beginDisplay(eDisplayFront);
		ofSetColor(255);

		ofPushMatrix();
		ofTranslate(cDisplayCanvasWidth * 0.5, cDisplayCanvasHeight * 0.5);
		videoMgr::GetInstance()->draw(eVideoEndlessOcean);
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
		displayMgr::GetInstance()->setBGMode(false, OF_GRADIENT_LINEAR);
		displayMgr::GetInstance()->setBGColor(ofColor(135, 206, 235), ofColor(240, 248, 255));
		displayMgr::GetInstance()->clearAllDisplay();
		videoMgr::GetInstance()->play(eVideoEndlessOcean);
	};
	void stopFunc() override
	{
		videoMgr::GetInstance()->stop(eVideoEndlessOcean);
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SItaly01"; }

private:

};