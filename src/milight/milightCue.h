#pragma once

#include "ofMain.h"

enum eMilightCueType : int{
	eCueStay = 0,
	eCueOff,
	eCueToColor,
	eCueToLoop
};

const string cTypeName[] = { "Stay", "Off", "To", "Loop" };

class milightCue {
public:
	milightCue()
		: _type(eCueStay)
		,_warmWhiteVal1(0)
		,_coldWhiteVal1(0)
		, _warmWhiteVal2(0)
		, _coldWhiteVal2(0)
		, _cueDuration(0.0f)
		, _loopDuration(0.0f)
		, _color1(0)
		, _color2(0)
	{

	}

public:
	eMilightCueType _type;
	ofColor _color1, _color2;
	int _warmWhiteVal1, _coldWhiteVal1;
	int _warmWhiteVal2, _coldWhiteVal2;
	float _cueDuration, _loopDuration;

};