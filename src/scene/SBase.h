#pragma once

#include "../constParameter.h"
#include "displayMgr.h"
#include "drawer.h"
#include "SType.h"
#include "midiCtrl.h"
#include "ctrlMap.h"
#include "postFilter.h"
#include "videoMgr.h"
#include "milightMgr.h"
class SBase
{
public:
	SBase(eSType type)
		:_type(type)
		,_isStart(false)
	{}

	void update(float delta){
		if (_isStart)
		{
			updateFunc(delta);
		}
	}
	void draw() {
		if (_isStart)
		{
			drawFunc();
		}
	};
	void start() 
	{
		_isStart = true;
		startFunc();
	};
	void stop() 
	{
		_isStart = false;
		stopFunc();
	};

	virtual void updateFunc(float delta) {};
	virtual void drawFunc() {};
	virtual void startFunc() {};
	virtual void stopFunc() {};

	virtual void drawMsg(ofVec2f pos) {};
	virtual void control(eCtrlType ctrl, int value = cMidiButtonPress) {};
	virtual string getSceneName() { return "SBase"; }

	inline eSType getType() { return _type; }
	inline bool getStart() { return _isStart; }


protected:
	bool _isStart;
	eSType _type;
};