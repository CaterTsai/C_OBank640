#pragma once

#include "ofMain.h"
#include "milightCue.h"
#include "ofxAnimatableOfColor.h"
#include "ofxAnimatableFloat.h"

class milightCtrl
{
public:
	milightCtrl()
		:_isSetup(false)
		, _needSetLoop(false)
	{
		_animColor.setColor(ofColor(0));
		_animWarmWhite.reset(0);
		_animColdWhite.reset(0);
	}

	void setup(int startAddr);
	void update(float delta);
	void setColor(ofColor color);
	void clear();

	void setCue(milightCue& cue);

	ofColor getColor();
	float getWarmWhite();
	float getColdWhite();
private:
	void checkLoop();
	void updateToDMX();

private:
	bool _isSetup;
	int _startAddr;
	ofxAnimatableOfColor _animColor;
	ofxAnimatableFloat _animWarmWhite, _animColdWhite;

	bool _needSetLoop;
	float _loopDuration;
	ofColor _loopColor;
	float _loopWarmWhite, _loopColdWhite;
};