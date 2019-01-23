#include "milightCtrl.h"
#include "ofxCTHD512.h"

void milightCtrl::setup(int startAddr)
{
	_isSetup = true;
	_startAddr = startAddr;
}

void milightCtrl::update(float delta)
{
	_animColor.update(delta);
	_animColdWhite.update(delta);
	_animWarmWhite.update(delta);

	if (ofxCTHD512::GetInstance()->isConnection())
	{
		updateToDMX();
	}
}

void milightCtrl::setColor(ofColor color)
{
	_animColor.setColor(color);
}

void milightCtrl::clear()
{
	_animColor.pause();
	_animWarmWhite.pause();
	_animColdWhite.pause();

	_animColor.setColor(0);
	_animWarmWhite.reset(0);
	_animColdWhite.reset(0);
}

void milightCtrl::setCue(milightCue& cue)
{
	switch (cue._type)
	{
	case eCueOff:
	{
		_animColor.setDuration(cue._cueDuration);
		_animWarmWhite.setDuration(cue._cueDuration);
		_animColdWhite.setDuration(cue._cueDuration);
		_animColor.animateTo(ofColor(0));
		_animWarmWhite.animateTo(0);
		_animColdWhite.animateTo(0);
		break;
	}
	case eCueToColor:
	{
		_animColor.setDuration(cue._cueDuration);
		_animWarmWhite.setDuration(cue._cueDuration);
		_animColdWhite.setDuration(cue._cueDuration);
		_animColor.animateTo(cue._color1);
		_animWarmWhite.animateTo(cue._warmWhiteVal1);
		_animColdWhite.animateTo(cue._coldWhiteVal1);
		break;
	}
	}
}

ofColor milightCtrl::getColor()
{
	return _animColor.getCurrentColor();
}

float milightCtrl::getWarmWhite()
{
	return _animWarmWhite.getCurrentValue();
}

float milightCtrl::getColdWhite()
{
	return _animColdWhite.getCurrentValue();
}

void milightCtrl::updateToDMX()
{
	ofxCTHD512::GetInstance()->set(_startAddr, _animColor.getCurrentColor().r);
	ofxCTHD512::GetInstance()->set(_startAddr + 1, _animColor.getCurrentColor().g);
	ofxCTHD512::GetInstance()->set(_startAddr + 2, _animColor.getCurrentColor().b);
	ofxCTHD512::GetInstance()->set(_startAddr + 3, _animColdWhite.getCurrentValue());
	ofxCTHD512::GetInstance()->set(_startAddr + 4, _animWarmWhite.getCurrentValue());
}
