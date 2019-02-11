#pragma once

#include "constParameter.h"
#include "displayMgr.h"
#include "ctrlMap.h"
#include "midiCtrl.h"

class ofDisplayerApp : public ofBaseApp, public ofxMidiListener
{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void mouseDragged(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

	void newMidiMessage(ofxMidiMessage& msg) override;

private:
	int _coverAlpha;
};