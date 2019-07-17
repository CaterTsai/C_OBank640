#pragma once

#include "SBase.h"

class SFrance05 : public SBase {

public:
	SFrance05()
		:SBase(eSFrance05)
	{}

	void updateFunc(float delta) override {
		_dTail.update(delta);
	}
	void drawFunc() override {
		displayMgr::GetInstance()->beginDisplay(eDisplayFront);
		_dTail.draw();
		displayMgr::GetInstance()->endDisplay();
	};
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << getSceneName() << endl;
		ss << "Knob 1 : tail r\n";
		ss << "Slider 1 : emitter Num\n";
		ss << "Slider 2 : emitter V\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	void startFunc() override
	{
		displayMgr::GetInstance()->setBGMode(false, OF_GRADIENT_LINEAR);
		displayMgr::GetInstance()->setBGColor(ofColor(50, 50, 50), ofColor(120, 0, 200));
		displayMgr::GetInstance()->clearAllDisplay();
		milightMgr::GetInstance()->toCue(eSFrance05);
		_dTail.start();

	};
	void stopFunc() override
	{
		_dTail.stop();
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override 
	{
		switch (ctrl)
		{
		case eCtrlType::eCtrl_ViewSlider1:
		{
			_dTail.setEmitterNum(value / (float)cMidiValueMax);
			break;
		}
		case eCtrlType::eCtrl_ViewSlider2:
		{
			_dTail.setEmitterT(value / (float)cMidiValueMax);
			break;
		}
		case eCtrlType::eCtrl_ViewKnob1:
		{
			_dTail.setColor(value / (float)cMidiValueMax);
			break;
		}
		}
	};
	string getSceneName() { return "SFrance05"; }

private:
	DTail _dTail;
};