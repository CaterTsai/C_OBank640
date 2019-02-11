#pragma once


#include "ofxAnimatableFloat.h"

#include <random>
#include "DBase.h"

const float cHaloCheckMaxDuration = 5.0f;
const int cHaloAddOnceTimeLimit = 3;
const float cHaloUnitMaxDuration = 60;
const int cHaloUnitMoveLimit = 1000;
class DHalo : public DBase
{
private:
	class haloUnit
	{
	public:
		haloUnit(ofColor c1, ofColor c2, ofVec2f p1, ofVec2f p2, float size, float t);
		void update(float delta);
		void draw();
		inline bool isPlay() { return _isPlay; }
	private:
		bool _isPlay;
		float _duration;

		float _size;
		ofColor _fromC, _toC;
		ofVec2f _fromP, _toP;
		ofxAnimatableFloat _animP;
		ofxAnimatableFloat _animAlpha;
	};

public:
	DHalo()
		:DBase(eDHalo)
		, _addTimer(0.0f)
		, _haloLimit(30)
	{
	}

	void update(float delta) override;
	void draw() override;

	void start() override;
	void stop() override;

private:
	void removeHalo();
	void checkHaloMgr();
	void addNewHaloUnit();

private:
	int _haloLimit;
	float _addTimer;
	list<haloUnit> _haloMgr;

	ofColor _fromColor, _toColor;
};