#pragma once

#include "DBase.h"
#include "ofxAnimatableFloat.h"

const int cCloudImgNum = 4;
const int cCloudColorHueMin = 180;
const int cCloudColorHueMax = 220;
const int cCloudImageBaseWidth = 1000;
const int cCloudParticalMax = 100;
const int cCloudUnitMax = 30;
const float cCloudPEmitterSlow = 3.0f;
const float cCloudPEmitterFast = 0.5f;
const float cCloudCEmitterSlow = 4.0f;
const float cCloudCEmitterFast = 2.0f;
const ofColor cCloudBaseColor(255, 255, 255);

class DClouds : public DBase
{
private:
	enum eCloudType {
		eCloudImg = 0
		,eCloudPartical
	};

	class cloudUnit {
	public:
		cloudUnit():
			_anim(0.0f)
			, _animV(0.0f)
			, _cloudIdx(0)
			, _alpha(0.0f)
		{}

		void update(float delta);
		void set(int cloudIndex);
		void set(ofColor c);
		ofVec2f getPos();
		ofColor getColor();

	private:
		void init();
	public:

		eCloudType _eType;
		int _cloudIdx;
		ofColor _c;
		float _alpha;		
		ofVec2f _source, _target;
		float _anim, _animV;
		float _size;
	};
public:
	DClouds()
		:DBase(eDCloud)
	{
		loadClouds();
	}

	void update(float delta) override;
	void draw() override;

	void start() override;
	void stop() override;

	void trigger(int key) override;

	void setPEmmiterT(float t);
	void setCEmmiterT(float t);
	void setColorR(float r);
	void setColorG(float g);
	void setColorB(float b);

private:
	void loadClouds();

	void addPartical();
	void addCloudUnit();
	void checkCloudUnit();

	void emitter(float delta);

private:
	ofColor _color;
	float _pTimer, _pEmmiterT;
	float _cTimer, _cEmmiterT;

	list<cloudUnit> _cloudPartical;
	list<cloudUnit> _cloudList;
	array<ofImage, cCloudImgNum> _cloudsImg;
};