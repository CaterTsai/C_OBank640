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

#pragma region VideoMgr
public:
	void initVideoMgr();

#pragma endregion
};
