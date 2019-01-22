#include "milightCtrl.h"
#include "ofxCTHD512.h"

void milightCtrl::setup(int startAddr)
{
	_isSetup = true;
	_startAddr = startAddr;
	_color.set(0);
}

void milightCtrl::update(float delta)
{
	ofxCTHD512::GetInstance()->set(_startAddr, _color.r);
	ofxCTHD512::GetInstance()->set(_startAddr + 1, _color.g);
	ofxCTHD512::GetInstance()->set(_startAddr + 2, _color.b);
}

void milightCtrl::setColor(ofColor color)
{
	_color = color;
}

ofColor& milightCtrl::getColor()
{
	return _color;
}
