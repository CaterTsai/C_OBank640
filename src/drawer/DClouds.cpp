#include "DClouds.h"

#pragma region cloudUnit
//---------------------------------
void DClouds::cloudUnit::update(float delta)
{
	_anim += _animV * delta;
	if (_anim <= 1.0f)
	{
		if (_anim >= 0.0f && _anim <= 0.2f)
		{
			_alpha = ofMap(_anim, 0.0f, 0.2f, 0.0f, 1.0f);
		}
		else if (_anim >= 0.8f && _anim <= 1.0f)
		{
			_alpha = 1.0f - ofMap(_anim, 0.8f, 1.0f, 0.0f, 1.0f);
		}
		else
		{
			_alpha = 1.0f;
		}
	}
}

//---------------------------------
void DClouds::cloudUnit::set(int cloudIndex)
{
	_eType = eCloudImg;
	_cloudIdx = cloudIndex;

	_size = ofRandom(0.5, 1.0);
	init();
}

//---------------------------------
void DClouds::cloudUnit::set(ofColor c)
{
	_eType = eCloudPartical;
	_c = c;
	_c.set(c.r, c.g, c.b, ofRandom(180, 220));
	_size = ofRandom(5, 50);
	init();
}

//---------------------------------
ofVec2f DClouds::cloudUnit::getPos()
{
	return _source.getInterpolated(_target, _anim);
}

//---------------------------------
ofColor DClouds::cloudUnit::getColor()
{
	ofColor rC = _c;
	rC.a *= _alpha;
	return rC;
}

//---------------------------------
void DClouds::cloudUnit::init()
{
	int sx = 0;
	int tx = 0;

	if (rand() % 2 == 0)
	{
		if (_eType == eCloudImg)
		{
			sx = cWindowWidth + ofRandom(0, cCloudImageBaseWidth * _size);
			tx = -ofRandom(0, cCloudImageBaseWidth * 0.5 * _size);
		}
		else
		{
			sx = cWindowWidth + ofRandom(-200, 200);
			tx = ofRandom(-200, 200);
		}
	}
	else
	{
		if (_eType == eCloudImg)
		{
			sx = -ofRandom(0, cCloudImageBaseWidth * _size);
			tx = cWindowWidth + ofRandom(0, cCloudImageBaseWidth * 0.5 * _size);
		}
		else
		{
			sx = ofRandom(-200, 200);
			tx = cWindowWidth + ofRandom(-200, 200);
		}
	}
	int y = ofRandom(cWindowHeight * 0.65, cWindowHeight);
	_source.set(sx, y);
	_target.set(tx, y);

	_anim = 0.0f;
	_animV = 1.0f / ofRandom(30, 80);
}
#pragma endregion

//---------------------------------
void DClouds::update(float delta)
{
	CHECK_START();

	emitter(delta);

	for (auto& iter : _cloudPartical)
	{
		iter.update(delta);
	}

	for (auto& iter : _cloudList)
	{
		iter.update(delta);
	}

	checkCloudUnit();
}

//---------------------------------
void DClouds::draw()
{
	CHECK_START();

	ofPushStyle();
	for (auto& iter : _cloudPartical)
	{
		ofSetColor(iter.getColor());
		ofDrawCircle(iter.getPos(), iter._size);
	}
	ofPopStyle();

	ofPushStyle();
	for (auto& iter : _cloudList)
	{
		ofPushMatrix();
		ofTranslate(iter.getPos());
		if (iter._eType == eCloudType::eCloudPartical)
		{
			ofSetColor(255, iter._alpha * 255.0f);
		}
		else
		{
			ofSetColor(_color, iter._alpha * 255.0f);
		}

		int w = _cloudsImg[iter._cloudIdx].getWidth() * iter._size;
		int h = _cloudsImg[iter._cloudIdx].getHeight() * iter._size;
		_cloudsImg[iter._cloudIdx].draw(w * -0.5f, h * -0.5f, w, h);
		ofPopMatrix();
	}
	ofPopStyle();

}

//---------------------------------
void DClouds::start()
{
	_isStart = true;
	ofSetCircleResolution(60);
	_pEmmiterT = cCloudPEmitterSlow;
	_cEmmiterT = cCloudCEmitterSlow;
	_pTimer = _cTimer = 0;
	_color = cCloudBaseColor;
}

//---------------------------------
void DClouds::stop()
{
	_isStart = false;
}

//---------------------------------
void DClouds::trigger(int key)
{
	switch (key)
	{
	case 1:
	{
		addPartical();
		break;
	}
	case 2:
	{
		addCloudUnit();
		break;
	}
	}
}

//---------------------------------
void DClouds::setPEmmiterT(float t)
{
	_pEmmiterT = t;
}

void DClouds::setCEmmiterT(float t)
{
	_cEmmiterT = t;
}

void DClouds::setColorR(float r)
{
	_color.r = r;
}

//---------------------------------
void DClouds::loadClouds()
{
	for (int i = 0; i < cCloudImgNum; i++)
	{
		_cloudsImg[i].load("clouds/cloud_" + ofToString(i + 1) + ".png");
	}
}

//---------------------------------
void DClouds::addPartical()
{
	cloudUnit newCloudUnit;
	newCloudUnit.set(_color);
	_cloudPartical.push_back(newCloudUnit);

}

//---------------------------------
void DClouds::addCloudUnit()
{
	cloudUnit newCloudUnit;
	newCloudUnit.set(rand() % _cloudsImg.size());
	_cloudList.push_back(newCloudUnit);
}

//---------------------------------
void DClouds::checkCloudUnit()
{
	_cloudList.remove_if([](const cloudUnit & p)
	{
		return p._anim > 1.0f;
	});

	_cloudPartical.remove_if([](const cloudUnit & p)
	{
		return p._anim > 1.0f;
	});
}

//---------------------------------
void DClouds::emitter(float delta)
{
	_pTimer -= delta;
	_cTimer -= delta;

	if (_pTimer <= 0.0f) {
		if (_cloudPartical.size() < cCloudParticalMax)
		{
			addPartical();
		}
		
		_pTimer = _pEmmiterT * ofRandom(0.8, 1.2);
	}

	if (_cTimer <= 0.0f) {
		if (_cloudList.size() < cCloudUnitMax)
		{
			addCloudUnit();
		}
		_cTimer = _cEmmiterT * ofRandom(0.8, 1.2);
	}

}
