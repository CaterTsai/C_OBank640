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
		: _type(eCueStay)
		,_warmWhiteVal(0)
		,_coldWhiteVal(0)
		, _cueDuration(0.0f)
		, _loopDuration(0.0f)
	{}

public:
	eMilightCueType _type;
	ofColor _color1, _color2;
	int _warmWhiteVal, _coldWhiteVal;
	float _cueDuration, _loopDuration;

};