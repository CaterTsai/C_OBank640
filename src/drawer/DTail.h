#pragma once

#include "DBase.h"

//DTail
const int cTailFieldRows = 20;
const int cTailFieldCols = 50;
const ofRectangle cTailRange = ofRectangle(0, 0, cWindowWidth, cWindowHeight);
const int cTailWidthLimit = 2;
const float cTailParticalSizeMin = 2.0f;
const float cTailParticalSizeMax = 4.0f;
const float cTailParticalSpeedMin = 50.0f;
const float cTailParticalSpeedMax = 150.0f;
const float cTailFlowFieldsMin = 50.0f;
const float cTailFlowFieldsMax = 150.0f;
const int cTailEmitterNumMin = 1;
const int cTailEmitterNumMax = 5;
const float cTailEmitterTSlow = 1.0;
const float cTailEmitterTFast = 0.2;
const ofColor cTailBaseColor(0, 45, 192);

class DTail : public DBase
{
#pragma region Tail
	struct tailUnit {
		ofVec2f pos;
		ofVec2f decline[2];
		float lifeT;
	};

	class tail {
	public:
		tail();
		~tail();
		void set(float lifeT, float width, bool isDecline, float declineT);
		void update(float delta);
		void draw();
		void addPos(ofVec2f p);

	private:
		bool _isDecline;
		list<tailUnit> _tailUnitList;
		ofVboMesh _tailMesh;
		float _tailLifeT;
		float _width, _declineT;
	};
#pragma endregion

#pragma region partical
private:
	class partical {
	public:
		partical()
			:_pos(0.0f)
			, _vec(0.0f)
			, _growTail(true)
			, _size(ofRandom(cTailParticalSizeMin, cTailParticalSizeMax))
			, _tailTimer(0.05)
		{
		}

		void set(ofVec2f p, ofVec2f v, ofVec2f a, float t);
		void update(float delta, ofVec2f desired);

	public:
		ofColor _color;
		ofVec2f _pos, _vec;
		float _life, _lifeLength;
		float _size;
		bool _haveTail, _growTail;
		tail _tail;
		float _tailTimer;
	};
#pragma endregion

public:
	DTail()
		:DBase(eDTail)
		, _emitterNum(cTailEmitterNumMin)
		, _emitterT(cTailEmitterTSlow)
		, _timer(0.0f)

	{
	}

	void update(float delta) override;
	void draw() override;

	void start() override;
	void stop() override;

	void trigger(int key) override;

	void setEmitterT(float t);
	void setEmitterNum(int num);
	void setColor(float r);

private:
	void generateFlowFields();
	void displayFlow(int x, int y, int w, int h);
	ofVec2f getFlow(ofVec2f pos);

	void checkPartical();
	void drawPartical(partical& p);
	void emitter(int num = 1);

private:
	int _emitterNum;
	float _timer, _emitterT;
	ofColor _color;
	list<partical> _pList;
	ofVec2f _flowFields[cTailFieldRows][cTailFieldCols];
};