#pragma once

#include "ofxAnimatableFloat.h"
#include "ofxAnimatableOfPoint.h"
#include "DBase.h"

const ofRectangle cShootingStarRange(0, 0, cWindowWidth, cWindowHeight);
const float cStarLifeMaxT = 5.0f;
const int cStarMaxAddNum = 10;
const float cShootingMaxDistance = cShootingStarRange.height * 0.8;
const float cShootingMaxT = 1.0f;

class DShootingStar : public DBase
{
private:
	class starUnit
	{
	public:
		starUnit(ofVec2f pos, float lifeT);
		void update(float delta);
		void draw();
		bool _isPlay;
	private:		
		float _duration;
		ofVec2f _pos;

		ofxAnimatableFloat _animFlash;
	};

	class shootingUnit
	{
	public:
		shootingUnit(ofVec2f from, ofVec2f to, float duration);
		void update(float delta);
		void draw();
		bool _isPlay;
	private:		
		float _duration;
		ofxAnimatableOfPoint _animStar, _animTail;
	};

public:
	DShootingStar()
		:DBase(eDShootingStar)
		, _starLimit(50)
		, _starTimer(0)
		, _shootingTimer(0)
	{
	}

	void update(float delta) override;
	void draw() override;

	void start() override;
	void stop() override;

private:
	void checkStar(float delta);
	void drawStar();
	void addStar();

private:
	int _starLimit;
	float _starTimer, _starMaxT;
	list<starUnit> _starMgr;

private:
	void checkShooting(float delta);
	void drawShooting();
	void addShooting();

private:
	float _shootingTimer, _shootingMaxT;
	list<shootingUnit> _shootingMgr;

};