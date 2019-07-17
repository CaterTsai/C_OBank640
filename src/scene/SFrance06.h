#pragma once

#include "SBase.h"

class SFrance06 : public SBase {

public:
	SFrance06()
		:SBase(eSFrance06)
	{
		_moon.load("moonLight.png");
	}

	void updateFunc(float delta) override 
	{
		_dc.update(delta);
	}
	void drawFunc() override {
		displayMgr::GetInstance()->beginDisplay(eDisplayFront);
		ofSetColor(255);
		float width = cDisplayCanvasWidth * 0.5;
		float height = width * _moon.getHeight() / _moon.getWidth();
		_moon.draw((cDisplayCanvasWidth - width) * 0.5, height * -0.2, width, height);
		displayMgr::GetInstance()->endDisplay();

		displayMgr::GetInstance()->beginDisplay(eDisplayBack);
		ofSetColor(255, _moonAlpah);
		_dc.draw();
		displayMgr::GetInstance()->endDisplay();
	};
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << getSceneName() << endl;
		ss << "Knob(1-3) : cloud r, g, b\n";
		ss << "Slider 1 : cloud emitter V\n";
		ss << "Slider 2 : particle emitter V\n";
		ss << "Slider 3 : Moon Alpha\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	void startFunc() override
	{
		displayMgr::GetInstance()->setBGMode(false, OF_GRADIENT_LINEAR);
		displayMgr::GetInstance()->setBGColor(ofColor(50, 50, 50), ofColor(0));
		displayMgr::GetInstance()->clearAllDisplay();
		milightMgr::GetInstance()->toCue(eSFrance06);
		_moonAlpah = 0;
		_dc.start();
		_dc.setColorR(0);
		_dc.setColorG(100);
		_dc.setColorB(150);
	};
	void stopFunc() override
	{
		_dc.stop();
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override 
	{
		switch (ctrl)
		{
		case eCtrlType::eCtrl_ViewSlider1:
		{
			_dc.setCEmmiterT(value / (float)cMidiValueMax);
			break;
		}
		case eCtrlType::eCtrl_ViewSlider2:
		{
			_dc.setPEmmiterT(value / (float)cMidiValueMax);
			break;
		}
		case eCtrlType::eCtrl_ViewSlider3:
		{
			_moonAlpah = ofMap(value, 0, cMidiValueMax, 0, 255);
			break;
		}
		case eCtrlType::eCtrl_ViewKnob1:
		{
			_dc.setColorR(value / (float)cMidiValueMax);
			break;
		}
		case eCtrlType::eCtrl_ViewKnob2:
		{
			_dc.setColorG(value / (float)cMidiValueMax);
			break;
		}
		case eCtrlType::eCtrl_ViewKnob3:
		{
			_dc.setColorB(value / (float)cMidiValueMax);
			break;
		}
		}
	};
	string getSceneName() { return "SFrance06"; }

private:
	DClouds _dc;
	ofImage _moon;
	int _moonAlpah;
};