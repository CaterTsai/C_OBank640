#pragma once

#include "ofxAnimatableFloat.h"
#include <random>
#include "DBase.h"
#include "videoMgr.h"

const int cTrainUnitNum = 8;
const float cTrainUnitMaxDuration = 60.0f;
const float cTrainCheckMaxDuration = 10.0f;
const int cTrainUnitMaxWidth = 480;

class DTrain : public DBase
{
private:
	class trainUnit
	{
	public:
		trainUnit(eVideoType index, float duration, ofVec3f center, int w, int h);
		void update(float delta);
		void draw();
		inline bool isPlay() { return _isPlay; }
	private:
		bool _isPlay;
		eVideoType _videoType;
		float _duration;
		ofVec3f _center;
		int _width, _height;
		ofxAnimatableFloat _animAlpha;
		ofxAnimatableFloat _animZ;
	};

public:
	DTrain()
		:DBase(eDTrain)
		, _addTimer(0.0f)
		, _videoIndex(0)
		, _degree(0)
	{
		for (int i = 0; i < cTrainVideoNum; i++)
		{
			_trainVideoList[i] = (eVideoType)i;
		}
	}

	void update(float delta) override;
	void draw() override;

	void start() override;
	void stop() override;

private:
	void removeTrainUnit();
	void checkTrainMgr();
	void addNewTrainUnit();

private:
	float _addTimer;
	list<trainUnit> _trainMgr;

	int _degree;

	int _videoIndex;
	array<eVideoType, cTrainVideoNum> _trainVideoList;
};