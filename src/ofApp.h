#pragma once

#include "ofMain.h"
#include "milightCtrl.h"
#include "milightCueTable.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

private:
	milightCueTable table;
};
