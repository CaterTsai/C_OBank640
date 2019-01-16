#pragma once

#include "ofMain.h"

class milightCtrl
{
public:
	milightCtrl()
		:_isSetup(false)
	{}

	void setup(int startAddr);
	void update();
	void setColor(ofColor color);
	ofColor& getColor();
private:
	bool _isSetup;
	int _startAddr;
	ofColor _color;
};