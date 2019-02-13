#include "DRain.h"

void DRain::update(float delta)
{
	CHECK_START();
	_timer -= delta;

	if (_timer < 0.0f)
	{
		_timer = _interval;
		_rainCanvas.begin();
		ofClear(0);
		drawRain();
		_rainCanvas.end();
	}
}

void DRain::draw()
{
	CHECK_START();
	_rainCanvas.draw(0, 0);
}

void DRain::start()
{
	_isStart = true;
	_rainDegree = 90;
	setRainLevel(0.5f);
	_timer = _interval;
	
}

void DRain::stop()
{
	_isStart = false;
}

void DRain::setRainLevel(float level)
{
	_rainLevel = level;
	_interval = ofMap(_rainLevel, 0.0f, 1.0f, cRainSlowest, cRainFastest);
}

void DRain::drawRain()
{
	int num = ofMap(_rainLevel, 0.0f, 1.0f, cRainMinNum, cRainMaxNum) * ofRandom(0.9, 1.1);
	float baseLength = ofMap(_rainLevel, 0.0f, 1.0f, 0.2, 1.0) * cRainLength;
	ofPushStyle();
	for (int i = 0; i < num; i++)
	{
		float length = baseLength * ofRandom(0.1, 0.5);
		int alpha = ofRandom(100, 255);
		ofVec2f shift(length, 0);
		shift.rotate(_rainDegree * ofRandom(0.95, 1.05));
		ofVec2f from, to;
		from.x = ofRandom(0, cWindowWidth);
		from.y = ofRandom(0, cWindowHeight - length);
		to = from + shift;
		
		ofSetColor(255, alpha);
		ofDrawLine(from, to);
		
	}
	ofPopStyle();
}
