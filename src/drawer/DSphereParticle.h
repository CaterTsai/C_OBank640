#pragma once

#include "DBase.h"

const int cDPNumber = 300;
const float cDPSpeedMin = 2 * DEG_TO_RAD;
const float cDPSpeedMax = 8 * DEG_TO_RAD;
const float cDPThetaMin = 30 * DEG_TO_RAD;
const float cDPThetaMax = 150 * DEG_TO_RAD;
const float cDPThetaMoveMin = 30 * DEG_TO_RAD;
const float cDPThetaMoveMax = 90 * DEG_TO_RAD;
const float cDPThetaLimit = 10 * DEG_TO_RAD;
const float cDPNearLimit = 0.2;
const float cDPCheckTriT = 0.1f;

class DSphereParticle : public DBase
{

#pragma region particle
	class particle
	{
	public:
		particle()
			:_t(0.0)
			,_p(0.0)
			,_vt(0.0)
			,_vp(0.0)
			, _minT(0.0)
			, _maxT(0.0)
		{};

		particle(float t, float p, float vt, float vp, float maxT, float minT)
			:_t(t)
			,_p(p)
			,_vt(vt)
			,_vp(vp)
			,_maxT(maxT)
			,_minT(minT)
		{}

		void set(float t, float p, float vt, float vp, float maxT, float minT);
		void update(float delta, float baseSize);
				
	public:
		float _t, _p;
		float _vt, _vp;
		float _maxT, _minT;
		ofVec3f _pos;
	};
#pragma endregion


public:
	DSphereParticle()
		:DBase(eDSphereParticle)
		, _baseSize(1.0)
		, _pColor(255)
	{
		_tri.setMode(ofPrimitiveMode::OF_PRIMITIVE_TRIANGLES);
		
	}

	void update(float delta) override;
	void draw(int x, int y, int z = 0) override;

	void start() override;
	void stop() override;
	void setBaseSize(float size);
	void setParticleColor(ofColor c);
private:
	void generateParticle();

	void computeTri();
private:
	float _baseSize;
	bool _triCheck[cDPNumber];
	array<DSphereParticle::particle, cDPNumber> _particleList;
	ofMesh _tri;

	ofColor _pColor;
};