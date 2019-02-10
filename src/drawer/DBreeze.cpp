#include "DBreeze.h"

#pragma region partical
//--------------------------------------
void DBreeze::partical::set(ePType type, ofVec2f p, ofVec2f v, ofVec2f a, float t)
{
	_type = type;
	_pos.set(p);
	_vec.set(v);
	_lifeLength = _life = t;
}

//--------------------------------------
void DBreeze::partical::update(float delta, ofVec2f desired)
{
	if (_life <= 0.0f)
	{
		//Dead
		return;
	}

	ofVec2f steer = desired - _vec;
	_vec += steer * delta;
	_pos += _vec * delta;

	//Rotate
	_degree += _rotateV * delta;
	if (_degree > 360)
	{
		_degree -= 360;
	}

	if (_degree < 0)
	{
		_degree += 360;
	}

	//Move
	if (_pos.x > cBreezRange.getMaxX())
	{
		_pos.x -= cBreezRange.getMaxX();
	}
	else if (_pos.x < cBreezRange.getMinX())
	{
		_pos.x += cBreezRange.getWidth();
	}

	if (_pos.y > cBreezRange.getMaxY())
	{
		_pos.y -= cBreezRange.getMaxY();
	}
	else if (_pos.y < cBreezRange.getMinY())
	{
		_pos.y += cBreezRange.getHeight();
	}
	_life -= delta;
}
#pragma endregion


//--------------------------------------
void DBreeze::update(float delta)
{
	CHECK_START();

	if (_autoEmitter)
	{
		_timer -= delta;
		if (_timer < 0.0f)
		{
			emitter(_emitterNum, _type);
			_timer = _emitterT;
		}
	}

	for (auto& iter : _pList)
	{
		iter.update(delta, getFlow(iter._pos));
	}

	checkPartical();
}

//--------------------------------------
void DBreeze::draw()
{
	CHECK_START();

	//Debug
	//displayFlow(0, 0, cWindowWidth, cWindowHeight);

	ofPushStyle();
	ofNoFill();

	for (auto& iter : _pList)
	{
		float life = iter._life / iter._lifeLength;
		life = (life <= 0.1f) ? ofMap(life, 0.0f, 0.1f, 0, 255) : 255;
		ofSetColor(_color, life);
		drawPartical(iter);
	}
	ofPopStyle();
}

//--------------------------------------
void DBreeze::start()
{
	generateFlowFields();
	_isStart = true;
	_color = cBreezBaseColor;
	_timer = _emitterT = cBreezEmitterSlow;
	_type = ePTypeRandom;
}

//--------------------------------------
void DBreeze::stop()
{
	_isStart = false;
}

//--------------------------------------
void DBreeze::toggleAutoEmitter()
{
	_autoEmitter = !_autoEmitter;

	if (_autoEmitter)
	{
		_timer = _emitterT;
	}
}

//--------------------------------------
void DBreeze::setEmitter(ePType type)
{
	_type = type;
}

//--------------------------------------
void DBreeze::setEmitterT(float v)
{
	_emitterT = v;
}

//--------------------------------------
void DBreeze::setEmitterNum(int num)
{
	_emitterNum = num;
}

void DBreeze::setColorR(int R)
{
	_color.r = R;
}

//--------------------------------------
void DBreeze::generateFlowFields()
{
	float offset = 0.05;
	for (int i = 0; i < cBreezeFieldRows; i++)
	{
		for (int j = 0; j < cBreezeFieldCols; j++)
		{
			//float theta = ofMap(ofNoise(i * offset, j * offset), 0, 1, 0, TWO_PI);
			float theta = ofRandom(-PI / 2.0f, PI / 2.0f);
			ofVec2f desired(cos(theta), sin(theta));
			_flowFields[i][j].set(desired.normalized() * ofRandom(cBreezParticalSpeedMin, cBreezParticalSpeedMax));
		}
	}
}

//--------------------------------------
void DBreeze::displayFlow(int x, int y, int w, int h)
{
	ofPushStyle();
	ofSetColor(255);
	ofFill();
	float unitW, unitH;
	unitW = w / cBreezeFieldCols;
	unitH = h / cBreezeFieldRows;

	for (int i = 0; i < cBreezeFieldRows; i++)
	{
		for (int j = 0; j < cBreezeFieldCols; j++)
		{
			ofVec2f center(j * unitW + unitW * 0.5, i * unitH + unitH * 0.5);
			ofVec2f desired = _flowFields[i][j];
			desired.normalize();
			ofVec2f end = center + (desired * 0.5 * unitW);

			ofDrawCircle(center, 0.2 * unitW);
			ofLine(center, end);
		}
	}
	ofPopStyle();
}

//--------------------------------------
ofVec2f DBreeze::getFlow(ofVec2f pos)
{
	int x = static_cast<int>(((pos.x - cBreezRange.x) / cBreezRange.width) * cBreezeFieldCols);
	int y = static_cast<int>(((pos.y - cBreezRange.y) / cBreezRange.height) * cBreezeFieldRows);

	x = (x == cBreezeFieldCols) ? x - 1 : x;
	y = (y == cBreezeFieldRows) ? y - 1 : y;
	return _flowFields[y][x];
}

//--------------------------------------
void DBreeze::checkPartical()
{
	_pList.remove_if([](const partical & p)
	{
		return p._life < 0.0f;
	});
}

//--------------------------------------
void DBreeze::drawPartical(partical& p)
{
	ofPushMatrix();
	ofTranslate(p._pos);
	ofRotate(p._degree, p._axis.x, p._axis.y, p._axis.z);
	switch (p._type)
	{
	case ePType::ePCircle:
	{
		ofDrawCircle(0, 0, p._size);
		break;
	}
	case ePType::ePTriangle:
	{
		ofVec2f p1, p2, p3;
		p1.set(p._size);
		p2 = p1.rotated(120);
		p3 = p3.rotated(120);
		ofDrawTriangle(p1, p2, p3);
		break;
	}
	case ePType::ePRect:
	{
		ofDrawRectangle(p._size * -0.5, p._size * -0.5, p._size, p._size);
		break;
	}
	case ePType::ePBox:
	{
		ofDrawBox(p._size);
		break;
	}
	case ePType::ePSphere:
	{
		ofDrawSphere(0, 0, p._size);
		break;
	}
	case ePType::ePCone:
	{
		ofDrawCone(0, 0, p._size, p._size);
		break;
	}
	case ePType::ePCylinder:
	{
		ofDrawCylinder(0, 0, p._size, p._size);
		break;
	}
	}

	ofPopMatrix();
}

//--------------------------------------
void DBreeze::emitter(int num, ePType type)
{
	for (int i = 0; i < num; i++)
	{
		partical newP;
		float theta = ofRandom(-PI / 4.0f, PI / 4.0f);
		ofVec2f pos(cBreezRange.getMinX(), ofRandom(cBreezRange.getMinY(), cBreezRange.getMaxY()));
		ofVec2f vec(cos(theta), sin(theta));
		ofVec2f acc(0);

		if (type == ePType::ePTypeRandom)
		{
			type = (ePType)(rand() % ePType::ePTypeNum);
		}
		else if (type == ePType::ePType2DRandom)
		{
			type = (ePType)(rand() % 3);
		}
		else if (type == ePType::ePType3DRandom)
		{
			type = (ePType)(3 + rand() % 4);
		}


		float lifeT = ofRandom(10, 20);
		vec *= ofRandom(cBreezParticalSpeedMin, cBreezParticalSpeedMax);
		newP.set(type, pos, vec, acc, lifeT);

		_pList.push_back(newP);
	}

}


