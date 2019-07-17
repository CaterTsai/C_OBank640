#pragma once

#include "SBase.h"
#include "DClouds.h"

class SFrance01 : public SBase {

public:
	SFrance01()
		:SBase(eSFrance01)
	{}

	void updateFunc(float delta) override 
	{
		_dCloud.update(delta);
	}
	void drawFunc() override {
		displayMgr::GetInstance()->beginDisplay(eDisplayFront);
		ofSetColor(255);
		_dCloud.draw();
		displayMgr::GetInstance()->endDisplay();
	};
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << getSceneName() << endl;
		ss << "Knob(1-3) : cloud r, g, b\n";
		ss << "Slider 1 : cloud emitter V\n";
		ss << "Slider 2 : particle emitter V\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	void startFunc() override 
	{
		displayMgr::GetInstance()->setBGMode(false, OF_GRADIENT_LINEAR);
		displayMgr::GetInstance()->setBGColor(ofColor(24, 168, 235), ofColor(194, 234, 255));
		displayMgr::GetInstance()->clearAllDisplay();

		milightMgr::GetInstance()->toCue(eSFrance01);
		_dCloud.start();
		_dCloud.setColorR(200);
		_dCloud.setColorG(200);
		_dCloud.setColorB(200);
	};
	void stopFunc() override 
	{
		_dCloud.stop();
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override 
	{
		switch (ctrl)
		{
		case eCtrlType::eCtrl_ViewSlider1:
		{
			_dCloud.setCEmmiterT(value / (float)cMidiValueMax);
			break;
		}
		case eCtrlType::eCtrl_ViewSlider2:
		{
			_dCloud.setPEmmiterT(value / (float)cMidiValueMax);
			break;
		}
		case eCtrlType::eCtrl_ViewKnob1:
		{
			_dCloud.setColorR(value / (float)cMidiValueMax);
			break;
		}
		case eCtrlType::eCtrl_ViewKnob2:
		{
			_dCloud.setColorG(value / (float)cMidiValueMax);
			break;
		}
		case eCtrlType::eCtrl_ViewKnob3:
		{
			_dCloud.setColorB(value / (float)cMidiValueMax);
			break;
		}
		}
	};
	string getSceneName() { return "SFrance01"; }

private:
	DClouds _dCloud;
};