#pragma once


#include "milightCtrl.h"
#include "milightCue.h"



class milightMgr
{
public:
	void setup();
	void update();

	void drawLight();
	

	//----------------------
	//Light

	//----------------------
	//Cue
public:
	void drawCue();

	void toCue(int cueNo);
	void nextCue();
	void prevCue();

	void load();
	void save();

private:
	bool _isSetup;

	vector<milightCtrl> _lightList;




};
