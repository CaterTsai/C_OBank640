#pragma once

#include "SBase.h"

class SItaly05 : public SBase {

public:
	SItaly05()
		:SBase(eSItaly05)
	{
		_bg.load("starNight.jpg");
	}

	void updateFunc(float delta) override {
		_dShooting.update(delta);
	}
	void drawFunc() override {
		displayMgr::GetInstance()->beginDisplay(eDisplayFront);
		_dShooting.draw();
		displayMgr::GetInstance()->endDisplay();

		displayMgr::GetInstance()->beginDisplay(eDisplayBack);
		ofSetColor(255, _bgAlpha);
		_bg.draw(0, 0, cDisplayCanvasWidth, cDisplayCanvasHeight);
		displayMgr::GetInstance()->endDisplay();
	};
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << getSceneName() << endl;
		ss << "Knob 1 : bg alpha\n";
		ss << "Slider 1 : star max emitter V\n";
		ss << "Slider 2 : shooting max emitter V\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	void startFunc() override
	{
		displayMgr::GetInstance()->setBGMode(false, OF_GRADIENT_LINEAR);
		displayMgr::GetInstance()->setBGColor(ofColor(25, 25, 100), ofColor(10, 10, 50));
		displayMgr::GetInstance()->clearAllDisplay();
		milightMgr::GetInstance()->toCue(eSItaly05);
		_bgAlpha = 0;
		_dShooting.start();
	};
	void stopFunc() override
	{
		_dShooting.stop();
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override 
	{
		switch (ctrl)
		{
		case eCtrlType::eCtrl_ViewSlider1:
		{
			_dShooting.setStarAddMaxTimer(value / (float)cMidiValueMax);
			break;
		}
		case eCtrlType::eCtrl_ViewSlider2:
		{
			_dShooting.setShootingAddMaxTimer(value / (float)cMidiValueMax);
			break;
		}
		case eCtrlType::eCtrl_ViewKnob1:
		{
			_bgAlpha = ofMap(value, 0, cMidiValueMax, 0, 255);
			break;
		}
		}
	};
	string getSceneName() { return "SItaly05"; }

private:
	DShootingStar _dShooting;
	ofImage _bg;
	int _bgAlpha;
};