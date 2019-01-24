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

	checkLoop();

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
	_needSetLoop = false;
	_animColor.setRepeatType(AnimRepeat::PLAY_ONCE);
	_animWarmWhite.setRepeatType(AnimRepeat::PLAY_ONCE);
	_animColdWhite.setRepeatType(AnimRepeat::PLAY_ONCE);
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
	case eCueToLoop:
	{
		_animColor.animateTo(cue._color1);
		_animWarmWhite.animateTo(cue._warmWhiteVal1);
		_animColdWhite.animateTo(cue._coldWhiteVal1);

		_loopColor = cue._color2;
		_loopDuration = cue._loopDuration;
		_loopColdWhite = cue._coldWhiteVal2;
		_loopWarmWhite = cue._warmWhiteVal2;

		_needSetLoop = true;
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

void milightCtrl::checkLoop()
{
	if (_needSetLoop)
	{
		if (_animColor.hasFinishedAnimating() && _animColor.getPercentDone() == 1.0)
		{
			_animColor.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH);
			_animColor.setDuration(_loopDuration);
			_animColor.animateTo(_loopColor);
			
			_animColdWhite.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH);
			_animColdWhite.setDuration(_loopDuration);
			_animColdWhite.animateTo(_loopColdWhite);

			_animWarmWhite.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH);
			_animWarmWhite.setDuration(_loopDuration);
			_animWarmWhite.animateTo(_loopWarmWhite);

			_needSetLoop = false;
		}
	}
}

void milightCtrl::updateToDMX()
{
	ofxCTHD512::GetInstance()->set(_startAddr, _animColor.getCurrentColor().r);
	ofxCTHD512::GetInstance()->set(_startAddr + 1, _animColor.getCurrentColor().g);
	ofxCTHD512::GetInstance()->set(_startAddr + 2, _animColor.getCurrentColor().b);
	ofxCTHD512::GetInstance()->set(_startAddr + 3, _animColdWhite.getCurrentValue());
	ofxCTHD512::GetInstance()->set(_startAddr + 4, _animWarmWhite.getCurrentValue());
}
