#pragma once

#include "constParameter.h"
#include "milightMgr.h"
#include "videoMgr.h"
#include "drawer.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

private:
	float _mainTimer;

	milightMgr _milight;

#pragma region VideoMgr
public:
	void initVideoMgr();

#pragma endregion

	DShootingStar _dTest;

	ofImage _bg;
};
