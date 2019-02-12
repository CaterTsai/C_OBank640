#pragma once

#include "SBase.h"

class SFrance03 : public SBase {

public:
	SFrance03()
		:SBase(eSFrance03)
	{
		_sphere.setResolution(4);
		_sphere.setPosition(cDisplayCanvasWidth * 0.5, cDisplayCanvasHeight * 0.5, 0);
		_sphere.setRadius(cDisplayCanvasHeight * 0.1);
		
	}

	void updateFunc(float delta) override 
	{
		_dSP.update(delta);
		
	}
	void drawFunc() override {
		displayMgr::GetInstance()->beginDisplay(eDisplayFront);
		ofSetColor(255);
		ofSetDepthTest(true);
		_dSP.draw(cDisplayCanvasWidth * 0.5, cDisplayCanvasHeight * 0.5);
		_sphere.drawWireframe();
		ofSetDepthTest(false);

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
		displayMgr::GetInstance()->setBGColor(ofColor(0), ofColor(20, 0, 50));
		displayMgr::GetInstance()->clearAllDisplay();
		_dSP.setBaseSize(cDisplayCanvasHeight * 0.3);
		_dSP.setParticleColor(ofColor(204, 51, 101));
		_dSP.start();
	};
	void stopFunc() override 
	{
		_dSP.stop();
	};
	void control(eCtrlType ctrl, int value = cMidiButtonPress) override {};
	string getSceneName() { return "SFrance03"; }

private:
	DSphereParticle _dSP;
	ofSpherePrimitive _sphere;
};