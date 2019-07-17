#include "DShootingStar.h"

#pragma region Star Unit
DShootingStar::starUnit::starUnit(ofVec2f pos, float lifeT)
	:_isPlay(true)
	, _pos(pos)
{
	_animFlash.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH_ONCE);
	_animFlash.setDuration(lifeT);
	_animFlash.animateFromTo(0, 255);
}

void DShootingStar::starUnit::update(float delta)
{
	if (!_isPlay)
	{
		return;
	}

	_animFlash.update(delta);
	if (_animFlash.hasFinishedAnimating())
	{
		_isPlay = false;
	}
}

void DShootingStar::starUnit::draw()
{
	if (!_isPlay)
	{
		return;
	}

	ofPushStyle();
	ofFill();
	ofSetColor(255, _animFlash.getCurrentValue());
	ofDrawCircle(_pos, 2);
	ofPopStyle();
}
#pragma endregion

#pragma region Shooting Unit
DShootingStar::shootingUnit::shootingUnit(ofVec2f from, ofVec2f to, float duration)
	:_isPlay(true)
{
	float delay = duration * 0.1;
	_animStar.setDuration(duration - delay);
	_animStar.setRepeatType(AnimRepeat::PLAY_ONCE);
	_animTail.setDuration(duration - delay);
	_animTail.setRepeatType(AnimRepeat::PLAY_ONCE);

	_animStar.setPosition(from);
	_animTail.setPosition(from);

	_animTail.animateToAfterDelay(to, delay);
	_animStar.animateTo(to);

}

void DShootingStar::shootingUnit::update(float delta)
{
	if (!_isPlay)
	{
		return;
	}
	_animTail.update(delta);
	_animStar.update(delta);

	if (_animTail.hasFinishedAnimating() && _animTail.getPercentDone() == 1.0f)
	{
		_isPlay = false;
	}
}

void DShootingStar::shootingUnit::draw()
{
	if (!_isPlay)
	{
		return;
	}

	ofPushStyle();
	ofSetColor(255);
	ofLine(_animStar.getCurrentPosition(), _animTail.getCurrentPosition());

	ofPopStyle();
}
#pragma endregion

#pragma region DShootingStar
//--------------------------------------------
//Basic
void DShootingStar::update(float delta)
{
	CHECK_START();

	for (auto& iter : _starMgr)
	{
		iter.update(delta);
	}

	for (auto& iter : _shootingMgr)
	{
		iter.update(delta);
	}

	checkStar(delta);
	checkShooting(delta);

}

void DShootingStar::draw()
{
	CHECK_START();

	drawStar();
	drawShooting();
}

void DShootingStar::start()
{
	_isStart = true;

	_starLimit = 100;
	_starMaxT = cStarLifeMaxT;
	_starTimer = ofRandom(0.5, 1.0) * _starMaxT;

	_shootingMaxT = cShootingMaxT;
	_shootingTimer = ofRandom(0.5, 1.0) * _shootingMaxT;

}

void DShootingStar::stop()
{
	_isStart = false;

	_shootingMgr.clear();
	_starMgr.clear();
}

void DShootingStar::setStarAddMaxTimer(float t)
{
	_starMaxT = ofMap(t, 0, 1, cStarLifeMaxT, 1.0f);
}

void DShootingStar::setShootingAddMaxTimer(float t)
{
	_shootingMaxT = ofMap(t, 0, 1, cShootingMaxT, 0.2);
}

//--------------------------------------------
//Star
void DShootingStar::checkStar(float delta)
{
	_starTimer -= delta;
	if (_starTimer > 0.0f)
	{
		return;
	}
	_starTimer = ofRandom(0.5, 1.0) * _starMaxT;

	_starMgr.remove_if([](const starUnit & p)
	{
		return (!p._isPlay);
	});

	if (_starMgr.size() > _starLimit)
	{
		return;
	}
	else
	{
		int addStarNum = 1 + rand() % MIN(_starLimit - _starMgr.size(), cStarMaxAddNum);
		for (int i = 0; i < addStarNum; i++)
		{
			addStar();
		}

	}
}

void DShootingStar::drawStar()
{
	ofPushStyle();
	for (auto& iter : _starMgr)
	{
		iter.draw();
	}
	ofPopStyle();
}

void DShootingStar::addStar()
{
	ofVec2f pos(
		ofRandom(cShootingStarRange.getMinX(), cShootingStarRange.getMaxX()),
		ofRandom(cShootingStarRange.getMinY(), cShootingStarRange.getMaxY())
	);

	float lifeT = ofRandom(0.5, 0.1) * cStarLifeMaxT;

	_starMgr.push_back(starUnit(pos, lifeT));

}

//--------------------------------------------
//Shooting
void DShootingStar::checkShooting(float delta)
{
	_shootingTimer -= delta;
	if (_shootingTimer > 0.0f)
	{
		return;
	}
	_shootingTimer = ofRandom(0.5, 1.0) * _shootingMaxT;

	_shootingMgr.remove_if([](const shootingUnit & p)
	{
		return !p._isPlay;
	});

	addShooting();
}

void DShootingStar::drawShooting()
{
	for (auto& iter : _shootingMgr)
	{
		iter.draw();
	}
}

void DShootingStar::addShooting()
{
	float degree = ofRandom(40, 50);
	ofVec2f v(ofRandom(0.5, 1.0) * cShootingMaxDistance, 0.0);
	v.rotate(degree);

	ofVec2f from(
		ofRandom(cShootingStarRange.getMinX(), cShootingStarRange.getMaxX()),
		ofRandom(cShootingStarRange.getMinY(), cShootingStarRange.getMaxY() - v.y)
	);
	ofVec2f to(from);
	to += v;

	_shootingMgr.push_back(shootingUnit(from, to, ofRandom(0.5, 1.0) * cShootingMaxT));
}

#pragma endregion

