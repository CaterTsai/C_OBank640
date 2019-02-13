#pragma once


#include "DBase.h"

const int cRainMaxNum = 1000;
const int cRainMinNum = 50;
const float cRainLength = cWindowHeight * 0.8;

class DRain : public DBase
{
public:
	DRain()
		:DBase(eDRain)
		, _rainDegree(0)
	{
		_rainCanvas.allocate(cWindowWidth, cWindowHeight, GL_RGBA);
	}

	void update(float delta) override;
	void draw() override;

	void start() override;
	void stop() override;

	void setRainLevel(float level);
private:
	void drawRain();

private:
	float _timer;
	float _rainLevel;
	float _rainDegree;
	ofFbo _rainCanvas;
};