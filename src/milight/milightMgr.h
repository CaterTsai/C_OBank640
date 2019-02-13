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

	void playCue();
	void clearCue();

private:
	bool _isSetup;
	int _cueId;

#pragma region Light Ctrl
	//----------------------
	//Light
private:
	void initLight();
	void updateLight(float delta);
	void drawLight(int x, int y, int width, int height);
private:
	array<milightCtrl, cLightNum> _lightList;
#pragma endregion

#pragma region Cue Table
	//----------------------
	//Cue Table
private:
	void initCueTable();
	void drawCueTable(int x, int y);

private:
	milightCueTable _cueTable;
#pragma endregion

	//-------------------
	//Singleton
	//-------------------
private:
	milightMgr()
		:_isSetup(false)
	{};
	~milightMgr()
	{
		milightMgr::Destroy();
	}
	milightMgr(milightMgr const&);
	void operator=(milightMgr const&);

public:
	static milightMgr* GetInstance();
	static void Destroy();

private:
	static milightMgr *pInstance;




};
