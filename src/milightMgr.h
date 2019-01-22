#pragma once


#include "milightCtrl.h"
#include "milightParameter.h"
#include "milightCueTable.h"



class milightMgr
{
public:
	void setup();
	void update(float delta);
	void draw(int x, int y);

	void toCue(int cueNo);
	void nextCue();
	void prevCue();

private:
	bool _isSetup;

#pragma region Light Ctrl
	//----------------------
	//Light
public:
	void initLight();
	void updateLight(float delta);
	void drawLight(int x, int y);
private:
	array<milightCtrl, cLightNum> _lightList;
#pragma endregion

#pragma region Cue Table
	//----------------------
	//Cue Table
public:
	void initCueTable();
	void drawCueTable(int x, int y);

private:
	milightCueTable _cueTable;
#pragma endregion

	




};
