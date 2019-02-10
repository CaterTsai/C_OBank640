#include "DTrain.h"

#pragma region TrainUnit
DTrain::trainUnit::trainUnit(eVideoType index, float duration, ofVec3f center, int w, int h):
	_isPlay(true)
	, _videoType(index)
	, _duration(duration)
	, _center(center)
	, _width(w)
	, _height(h)
{
	float animD = duration * 0.05;
	_animAlpha.setDuration(animD);
	_animAlpha.animateFromTo(0, 255);
	_animZ.setDuration(duration);
	_animZ.animateFromTo(_center.z, _center.z - ofRandom(300, 800));
	videoMgr::GetInstance()->play(index);
	
}

void DTrain::trainUnit::update(float delta)
{
	if (!_isPlay)
	{
		return;
	}
	_animAlpha.update(delta);
	_animZ.update(delta);

	_center.z = _animZ.getCurrentValue();

	_duration -= delta;

	if (_duration <= 0.0f)
	{
		videoMgr::GetInstance()->stop(_videoType);
		_isPlay = false;
	}

	if (_duration <= _animAlpha.getDuration() && !_animAlpha.isAnimating())
	{
		_animAlpha.animateTo(0);
	}
}

void DTrain::trainUnit::draw()
{
	if (!_isPlay)
	{
		return;
	}

	ofPushStyle();
	ofSetColor(255, _animAlpha.getCurrentValue());
	ofPushMatrix();
	ofTranslate(_center);
	videoMgr::GetInstance()->draw(_videoType, _width, _height);
	ofPopMatrix();
	ofPopStyle();

}
#pragma endregion

#pragma region DTrain
void DTrain::update(float delta)
{
	CHECK_START();

	for (auto& iter : _trainMgr)
	{
		iter.update(delta);
	}
	removeTrainUnit();

	_addTimer -= delta;
	if (_addTimer <= 0.0f)
	{
		_addTimer = ofRandom(0.2, 1.0) * cTrainCheckMaxDuration;
		checkTrainMgr();
	}

}

void DTrain::draw()
{
	CHECK_START();

	ofSetDepthTest(true);
	for (auto& iter : _trainMgr)
	{
		iter.draw();
	}
	ofSetDepthTest(false);
}

void DTrain::start()
{
	_isStart = true;
	_addTimer = 0.0f;
	_videoIndex = 0;
	shuffle(_trainVideoList.begin(), _trainVideoList.end(), default_random_engine(ofGetElapsedTimeMillis()));
	_degree = ofRandom(0, 360);
}

void DTrain::stop()
{
	_isStart = false;
	videoMgr::GetInstance()->stopAll();
}

void DTrain::removeTrainUnit()
{
	auto iter = _trainMgr.begin();
	while (iter != _trainMgr.end())
	{
		if (!iter->isPlay())
		{
			_trainMgr.erase(iter);
			break;
		}
		else
		{
			iter++;
		}
	}
}

void DTrain::checkTrainMgr()
{
	if (_trainMgr.size() <= cTrainUnitNum)
	{
		addNewTrainUnit();
	}
}

void DTrain::addNewTrainUnit()
{
	int width = static_cast<int>(cTrainUnitMaxWidth * ofRandom(0.2, 1.0) + 0.5f);
	int height = width * 9.0f / 16.0f;

	_degree += ofRandom(45, 180);
	_degree %= 360;

	ofVec2f v(ofRandom(width, ( (ofGetWindowWidth() - width) * 0.5)), 0);
	v.rotate(_degree);
	v.x += ofGetWindowWidth() * 0.5;
	v.y += ofGetWindowHeight() * 0.5;
	int z = ofRandom(0, -500);

	_trainMgr.push_back(trainUnit(_trainVideoList[_videoIndex], cTrainUnitMaxDuration * ofRandom(0.5, 1.0), ofVec3f(v.x, v.y, z), width, height));
	
	if ((_videoIndex + 1) >= _trainVideoList.size())
	{
		_videoIndex = 0;
		shuffle(_trainVideoList.begin(), _trainVideoList.end(), default_random_engine(ofGetElapsedTimeMillis()));
	}
	else
	{
		_videoIndex++;
	}
}
#pragma endregion


