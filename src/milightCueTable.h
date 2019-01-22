#pragma once

#include "ofxXmlSettings.h"
#include "ofxGui.h"
#include "ofxPanelEx.h"
#include "milightParameter.h"
#include "milightCue.h"

typedef array<milightCue, cLightNum> milightCueList;

class milightCueTable {
public:
	milightCueTable();
	void init(string path);
	void drawCue(int x, int y);
	void drawGUI(int x, int y);

	inline int getCueNum() {
		return _cueTable.size();
	}

private:
	void loadCue();
	void saveCue();

public:
	void onGUIValueUpdate();
	void onBtnAddCue();
	void onBtnDelCue();
	void onBtnNextCue();
	void onBtnPrevCue();
	void onBtnNextLight();
	void onBtnPrevLight();

private:
	void initGUI();
	void setGUIVal();
	void clearGUIVal();
	void updateCue();
private:
	int _cueNo, _lightNo;
	string _cuePath;
	vector<milightCueList> _cueTable;

	 //GUI
	ofxPanelEx _lightGUI;
	ofParameter<string> _gLCueNo, _gLLightNo, _gLLightState;
	ofParameter<ofColor> _gCLightColor;
	ofParameter<ofColor> _gCLoopColor;
	ofParameter<int> _gSWarmWhite, _gSColdWhite;
	ofParameter<int> _gSLoopWarmWhite, _gSLoopColdWhite;
	ofParameter<float> _gSCueDuration, _gSLoopDuration;
	ofParameter<int> _gSState;
	ofxButton _gBAddCue, _gBDelCue, _gBNextCue, _gBPrevCue;
	ofxButton _gBNextLight, _gBPrevLight;
};