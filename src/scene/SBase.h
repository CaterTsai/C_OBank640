#pragma once

#include "../constParameter.h"
#include "displayMgr.h"
#include "drawer.h"
#include "SType.h"
#include "midiCtrl.h"
#include "ctrlMap.h"
#include "postFilter.h"

class SBase
{
public:
	SBase(eSType type)
		:_type(type)
		,_isStart(false)
	{}

	virtual void update(float delta){}
	virtual void draw() {};
	virtual void drawMsg(ofVec2f pos) {};
	virtual void start() {};
	virtual void stop() {};
	virtual void control(eCtrlType ctrl, int value = cMidiButtonPress) {};
	virtual string getSceneName() { return "SBase"; }

	inline eSType getType() { return _type; }
	inline bool getStart() { return _isStart; }


protected:
	bool _isStart;
	eSType _type;
};