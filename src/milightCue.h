#pragma once

#include "ofMain.h"

enum eMilightCueType {
	eCueStay = 0,
	eCueOff,
	eCueToColor,
	eCueToWarmWhite,
	eCueToColdWhite,
	eCueToLoop
};

class milightCue {
public:
	milightCue()
	{}

public:
	eMilightCueType _type;
	ofColor _color;
	int _warmWhiteVal, _coldWhiteVal;

};