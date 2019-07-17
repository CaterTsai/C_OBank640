#pragma once

#include "SBase.h"

class SFrance02 : public SBase {

public:
	SFrance02()
		:SBase(eSFrance02)
	{}

	void updateFunc(float delta) override 
	{
		_dBreeze.update(delta);
		_dHalo.update(delta);
	}
	void drawFunc() override {
		
		displayMgr::GetInstance()->beginDisplay(eDisplayFront);
		ofSetColor(255);
		
		_dBreeze.draw();
		_dHalo.draw();
		displayMgr::GetInstance()->endDisplay();

	};
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << getSceneName() << endl;
		ss << "Slider 1 : Breeze emitter Num\n";
		ss << "Slider 2 : Breeze emitter V\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	void startFunc() override 
	{
		displayMgr::GetInstance()->setBGMode(true);
		displayMgr::GetInstance()->setBGColor(ofColor(0, 0, 0));
		displayMgr::GetInstance()->clearAllDisplay();
		milightMgr::GetInstance()->toCue(eSFrance02);
		_dBreeze.start();
		_dHalo.start();
	};
	void stopFunc() override 
	{
		_dBreeze.stop();
		_dHalo.stop();
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override 
	{
		switch (ctrl)
		{
		case eCtrlType::eCtrl_ViewSlider1:
		{
			_dBreeze.setEmitterNum(value / (float)cMidiValueMax);
			break;
		}
		case eCtrlType::eCtrl_ViewSlider2:
		{
			_dBreeze.setEmitterT(value / (float)cMidiValueMax);
			break;
		}
		}
	};
	string getSceneName() { return "SFrance02"; }

private:
	DBreeze _dBreeze;
	DHalo _dHalo;
};