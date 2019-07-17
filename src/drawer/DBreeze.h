#pragma once

#include "DBase.h"

const int cBreezeFieldRows = 20;
const int cBreezeFieldCols = 50;
const ofRectangle cBreezRange = ofRectangle(0, 0, cWindowWidth, cWindowHeight);
const float cBreezParticalSpeedMin = 100.0f;
const float cBreezParticalSpeedMax = 500.0f;
const float cBreezParticalSizeMin = 5.0f;
const float cBreezParticalSizeMax = 20.0f;
const float cBreezEmitterSlow = 1.0f;
const float cBreezEmitterFast = 0.2f;
const int cBreezEmitterNumMin = 1;
const int cBreezEmitterNumMax = 10;
const ofColor cBreezBaseColor(200, 200, 200);

class DBreeze : public DBase
{

#pragma region partical
public:
	enum ePType :int {
		ePCircle = 0 //2D
		, ePRect
		, ePTriangle
		, ePBox		//3D
		, ePSphere
		, ePCone
		, ePCylinder
		, ePTypeNum



		, ePType2DRandom
		, ePType3DRandom
		, ePTypeRandom
		, ePTypeUnknow
	};
private:
	class partical {
	public:
		partical()
			:_pos(0.0f)
			, _vec(0.0f)
			, _type(ePTypeUnknow)
			, _degree(0.0f)
			, _rotateV(ofRandom(-180, 180))
			, _size(ofRandom(cBreezParticalSizeMin, cBreezParticalSizeMax))
		{
			_axis.set(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
			_axis.normalize();
		}

		void set(ePType type, ofVec2f p, ofVec2f v, ofVec2f a, float t);
		void update(float delta, ofVec2f desired);

	public:
		ePType _type;
		ofVec2f _pos, _vec;
		float _life, _lifeLength;

		float _size;
		ofVec3f _axis;
		float _degree, _rotateV;
	};
#pragma endregion


public:
	DBreeze()
		:DBase(eDBreeze)
		, _autoEmitter(true)
		, _emitterNum(1)
		, _type(ePType2DRandom)
	{
		_color = cBreezBaseColor;
	}

	void update(float delta) override;
	void draw() override;

	void start() override;
	void stop() override;

	void toggleAutoEmitter();
	void setEmitter(ePType type);
	void setEmitterT(float v);
	void setEmitterNum(int num);
	void setColorR(int R);

private:
	void generateFlowFields();
	void displayFlow(int x, int y, int w, int h);
	ofVec2f getFlow(ofVec2f pos);

	void checkPartical();
	void drawPartical(partical& p);
	void emitter(int num = 1, ePType type = ePTypeRandom);


private:
	bool _autoEmitter;
	int _emitterNum;
	float _timer, _emitterT;
	ePType _type;
	ofColor _color;
	list<partical> _pList;
	ofVec2f _flowFields[cBreezeFieldRows][cBreezeFieldCols];
};