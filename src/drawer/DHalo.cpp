#include "DHalo.h"

#pragma region HaloUnit
DHalo::haloUnit::haloUnit(ofColor c1, ofColor c2, ofVec2f p1, ofVec2f p2, float size, float t)
	:_duration(t)
	,_isPlay(true)
	, _fromP(p1)
	, _toP(p2)
	, _fromC(c1)
	, _toC(c2)
	, _size(size)
{
	_animAlpha.setDuration(t * 0.05);
	_animP.setDuration(t);

	_animAlpha.animateFromTo(0, 1.0);
	_animP.animateFromTo(0.0, 1.0);
}

void DHalo::haloUnit::update(float delta)
{
	if (!_isPlay)
	{
		return;
	}

	_animP.update(delta);
	_animAlpha.update(delta);
	
	_duration -= delta;

	if (_duration <= 0.0)
	{
		_isPlay = false;
	}

	if (_duration <= _animAlpha.getDuration() && !_animAlpha.isAnimating())
	{
		_animAlpha.animateTo(0);
	}
}

void DHalo::haloUnit::draw()
{
	if (!_isPlay)
	{
		return;
	}

	
	float p = _animP.getCurrentValue();
	ofVec2f nowP = _fromP.getInterpolated(_toP, p);
	ofColor nowC = _fromC.getLerped(_toC, p);

	nowC.a = nowC.a * _animAlpha.getCurrentValue();

	ofPushMatrix();
	ofTranslate(nowP);
	ofPushStyle();
	ofSetColor(nowC);
	ofFill();
	ofDrawCircle(0, 0, _size);
	ofPopStyle();
	ofPopMatrix();

}
#pragma endregion

#pragma region DHalo
void DHalo::update(float delta)
{
	CHECK_START();

	for (auto& iter : _haloMgr)
	{
		iter.update(delta);
	}
	removeHalo();

	_addTimer -= delta;
	if (_addTimer <= 0.0f)
	{
		_addTimer = ofRandom(0.2, 1.0) * cHaloCheckMaxDuration;
		checkHaloMgr();
	}
}

void DHalo::draw()
{
	CHECK_START();

	for (auto& iter : _haloMgr)
	{
		iter.draw();
	}
}

void DHalo::start()
{
	_isStart = true;
	_addTimer = 0.0f;

	_fromColor.set(34, 212, 0, 50);
	_toColor.set(34, 212, 200, 50);
}

void DHalo::stop()
{
	_isStart = false;
	_haloMgr.clear();
}

void DHalo::removeHalo()
{
	auto iter = _haloMgr.begin();
	while (iter != _haloMgr.end())
	{
		if (!iter->isPlay())
		{
			_haloMgr.erase(iter);
			break;
		}
		else
		{
			iter++;
		}
	}
}

void DHalo::checkHaloMgr()
{
	int limit = MIN(cHaloAddOnceTimeLimit, _haloLimit - _haloMgr.size());
	if (limit <= 0)
	{
		return;
	}
	
	int num = 1 + rand() % limit;
	for (int i = 0; i < num; i++)
	{
		addNewHaloUnit();
	}

}

void DHalo::addNewHaloUnit()
{
	float size = ofRandom(0.01, 0.1) * ofGetWindowWidth();
	float t = ofRandom(0.3, 1.0)* cHaloUnitMaxDuration;
	ofVec2f fromPos, toPos;
	fromPos.x = ofRandom(0, ofGetWindowWidth());
	fromPos.y = ofRandom(ofGetWindowHeight() * 0.5, ofGetWindowHeight());
	toPos = fromPos;
	if (fromPos.x >= ofGetWindowWidth() * 0.5)
	{
		toPos.x -= cHaloUnitMoveLimit * ofRandom(0.3, 1.0);
	}
	else
	{
		toPos.x += cHaloUnitMoveLimit * ofRandom(0.3, 1.0);
	}

	_haloMgr.push_back(haloUnit(_fromColor, _toColor, fromPos, toPos, size, t));


}
#pragma endregion


