#pragma once

#include "ofxXmlSettings.h"
#include "ofxGui.h"
#include "milightCtrl.h"
#include "milightCue.h"

typedef vector<milightCue> milightCueTable;

class milightMgr
{
public:
	void setup();
	void update();

	void drawLight();
	void drawCtrl();

	void load();
	void save();

	//----------------------
	//Cue	
	void toCue(int cueNo);
	void nextCue();
	void prevCue();

	void addCue();
	void delCue();


private:
	void initGUI();

private:
	bool _isSetup;
	int _cueNo;
	vector<milightCtrl> _lightList;
	vector<milightCueTable> _cueTable;

	//GUI
	ofxGuiGroup _lightGUI;
	ofxColorSlider _gCLightColor;
	ofxFloatSlider _gSWarmWhite, _gSColdWhite;
	ofxFloatSlider _gSCueDuration, _gSLoopDuration;
	
	ofxButton _gBAddCue, _gBDelCue, _gBUpdate, _gBHasLoop;
	
};
