#pragma once

#include "DType.h"
#include "drawParameter.h"

#define CHECK_START() if(!_isStart)return;

class DBase
{
public:
	DBase(eDType type)
		:_eType(type)
		, _isStart(false)
		, _timer(0.0f)
	{};

	virtual void update(float delta) {};
	virtual void draw() {};
	virtual void draw(int x, int y, int z = 0) {};
	virtual void draw(int x, int y, int w, int h) {};

	virtual void start() {};
	virtual void stop() {};

	virtual void reset() {};

	virtual void trigger(int key) {};

	inline bool getStart()
	{
		return _isStart;
	}

	inline eDType getType()
	{
		return _eType;
	};

protected:
	bool _isStart;
	const eDType	_eType;
	float _timer;

};