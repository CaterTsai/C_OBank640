#pragma once

#include "SBase.h"

class SItaly04 : public SBase {

public:
	SItaly04()
		:SBase(eSItaly04)
	{}

	void updateFunc(float delta) override 
	{
		_dr.update(delta);
	}
	void drawFunc() override {
		displayMgr::GetInstance()->beginDisplay(eDisplayFront);
		ofSetColor(255);
		_dr.draw();
		displayMgr::GetInstance()->endDisplay();
	};
	void drawMsg(ofVec2f pos) override
	{
		ostringstream ss;
		ss << getSceneName() << endl;
		ss << "Slider 1 : Rain Level\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	void startFunc() override
	{
		displayMgr::GetInstance()->setBGMode(false, OF_GRADIENT_LINEAR);
		displayMgr::GetInstance()->setBGColor(ofColor(25, 25, 100), ofColor(10, 10, 50));
		displayMgr::GetInstance()->clearAllDisplay();
		milightMgr::GetInstance()->toCue(eSItaly04);
		_dr.start();
	};
	void stopFunc() override
	{
		_dr.stop();
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override 
	{
		if (ctrl == eCtrl_ViewSlider1)
		{
			_dr.setRainLevel(value / (float)cMidiValueMax);
		}
	};
	string getSceneName() { return "SItaly04"; }

private:
	DRain _dr;
};