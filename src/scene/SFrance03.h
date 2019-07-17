#pragma once

#include "SBase.h"

class SFrance03 : public SBase {

public:
	SFrance03()
		:SBase(eSFrance03)
	{
		_sphere.setResolution(4);
		_sphere.setPosition(0, 0, 0);
		_sphere.setRadius(cDisplayCanvasHeight * 0.1);
		
	}

	void updateFunc(float delta) override 
	{
		_dSP.update(delta);
		_r += _rV * delta;
		if (_r > 360)
		{
			_r -= 360;
		}

	}
	void drawFunc() override {
		displayMgr::GetInstance()->beginDisplay(eDisplayFront);
		ofSetColor(255);
		ofSetDepthTest(true);

		_dSP.draw(cDisplayCanvasWidth * 0.5, cDisplayCanvasHeight * 0.5);
		ofPushMatrix();
		ofTranslate(cDisplayCanvasWidth * 0.5, cDisplayCanvasHeight * 0.5);
		ofRotateX(sin(_r * DEG_TO_RAD) * 360.0);
		ofRotateY(cos(_r * DEG_TO_RAD) * 360.0);
		_sphere.drawWireframe();
		ofPopMatrix();
		ofSetDepthTest(false);

		displayMgr::GetInstance()->endDisplay();
	};
	void drawMsg(ofVec2f pos) override 
	{
		ostringstream ss;
		ss << getSceneName() << endl;
		ss << "Knob 1 : particle size\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	};
	void startFunc() override 
	{
		_r = 0;
		_rV = 20;
		displayMgr::GetInstance()->setBGMode(false, OF_GRADIENT_LINEAR);
		displayMgr::GetInstance()->setBGColor(ofColor(0), ofColor(20, 0, 50));
		displayMgr::GetInstance()->clearAllDisplay();
		milightMgr::GetInstance()->toCue(eSFrance03);
		_dSP.setBaseSize(cDisplayCanvasHeight * 0.3);
		_dSP.setParticleColor(ofColor(204, 51, 101));
		_dSP.start();
	};
	void stopFunc() override 
	{
		_dSP.stop();
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override 
	{
		if (ctrl == eCtrlType::eCtrl_ViewKnob1)
		{
			_dSP.setParticleSize(value / (float)cMidiValueMax);
		}
	};
	string getSceneName() { return "SFrance03"; }

private:
	DSphereParticle _dSP;
	ofSpherePrimitive _sphere;
	float _r, _rV;
};