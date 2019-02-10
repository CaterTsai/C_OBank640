#include "DTail.h"

#pragma region Tail
//--------------------------------------
DTail::tail::tail()
	:_width(10.0f)
	, _declineT(1.0f)
{
	_tailMesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_TRIANGLE_STRIP);

}

//--------------------------------------
DTail::tail::~tail()
{
	_tailMesh.clear();
	_tailUnitList.clear();
}

//--------------------------------------
void DTail::tail::set(float lifeT, float width, bool isDecline, float declineT)
{
	_tailLifeT = lifeT;
	_width = width;
	_isDecline = isDecline;
	_declineT = declineT;
}

//--------------------------------------
void DTail::tail::update(float delta)
{
	if (_tailMesh.getNumVertices() < 2)
	{
		return;
	}

	if (_isDecline)
	{
		int index = 0;
		for (auto& iter : _tailUnitList)
		{
			auto p1 = _tailMesh.getVertex(index * 2);
			auto p2 = _tailMesh.getVertex(index * 2 + 1);
			p1 += delta * iter.decline[0];
			p2 += delta * iter.decline[1];

			auto check = (p2 - p1) * iter.decline[0];

			if (p1.distance(p2) > cTailWidthLimit && check.x > 0 && check.y > 0)
			{
				_tailMesh.setVertex(index * 2, p1);
				_tailMesh.setVertex(index * 2 + 1, p2);
			}
			index++;
		}

	}

	for (auto& iter : _tailUnitList)
	{
		iter.lifeT -= delta;
	}

	if (_tailUnitList.begin()->lifeT < 0.0f)
	{
		_tailUnitList.pop_front();
		_tailMesh.removeVertex(0);
		_tailMesh.removeVertex(0);
	}

}

//--------------------------------------
void DTail::tail::draw()
{
	_tailMesh.draw();
}

//--------------------------------------
void DTail::tail::addPos(ofVec2f p)
{
	tailUnit newTailUnit;
	newTailUnit.pos = p;
	newTailUnit.lifeT = _tailLifeT;

	if (_tailUnitList.size() == 0)
	{
		_tailUnitList.push_back(newTailUnit);
	}
	else
	{
		auto last = _tailUnitList.rbegin();
		ofVec2f v = newTailUnit.pos - last->pos;
		v.normalize();
		ofVec2f up, down;
		up = down = v;

		up.rotate(90);
		down.rotate(-90);

		ofVec2f pUp = newTailUnit.pos + (up * _width);
		ofVec2f pDown = newTailUnit.pos + (down * _width);

		newTailUnit.decline[0] = (down  * _width) / _declineT;
		newTailUnit.decline[1] = (up  * _width) / _declineT;

		if (_tailUnitList.size() == 1)
		{
			ofVec2f pFirstUp = last->pos + (up * _width);
			ofVec2f pFirstDown = last->pos + (down * _width);
			last->decline[0] = (down  * _width) / _declineT;
			last->decline[1] = (up  * _width) / _declineT;
			_tailMesh.addVertex(pFirstUp);
			_tailMesh.addVertex(pFirstDown);
		}
		_tailMesh.addVertex(pUp);
		_tailMesh.addVertex(pDown);
		_tailUnitList.push_back(newTailUnit);
	}
}

#pragma endregion

#pragma region partical
//--------------------------------------
void DTail::partical::set(ofVec2f p, ofVec2f v, ofVec2f a, float t)
{
	_pos.set(p);
	_vec.set(v);
	_lifeLength = _life = t;

	_tail.set(t * 0.2, _size, true, t * 0.4);
}

//--------------------------------------
void DTail::partical::update(float delta, ofVec2f desired)
{
	if (_life <= 0.0f)
	{
		//Dead
		return;
	}

	ofVec2f steer = desired - _vec;
	_vec += steer * delta;
	_pos += _vec * delta;

	if (_haveTail && _growTail)
	{
		_tailTimer -= delta;
		if (_tailTimer < 0)
		{
			_tail.addPos(_pos);
			_tailTimer = 0.05f;
		}
	}

	_tail.update(delta);

	//Move
	if (_pos.x > cTailRange.getMaxX())
	{
		_growTail = false;
	}
	else if (_pos.x < cTailRange.getMinX())
	{
		_growTail = false;
	}

	if (_pos.y > cTailRange.getMaxY())
	{
		_growTail = false;
	}
	else if (_pos.y < cTailRange.getMinY())
	{
		_growTail = false;
	}
	_life -= delta;
}
#pragma endregion

//--------------------------------------
void DTail::update(float delta)
{
	CHECK_START();

	_timer -= delta;
	if (_timer < 0.0f)
	{
		emitter(_emitterNum);
		_timer = _emitterT;
	}

	for (auto& iter : _pList)
	{
		iter.update(delta, getFlow(iter._pos));
	}
	checkPartical();
}

//--------------------------------------
void DTail::draw()
{
	CHECK_START();

	ofPushStyle();
	for (auto& iter : _pList)
	{
		ofSetColor(iter._color);
		drawPartical(iter);
	}
	ofPopStyle();
}

//--------------------------------------
void DTail::start()
{
	generateFlowFields();
	_emitterNum = cTailEmitterNumMin;
	_timer = _emitterT = cTailEmitterTSlow;
	_isStart = true;
	_color = cTailBaseColor;
}

//--------------------------------------
void DTail::stop()
{
	_isStart = false;
}

//--------------------------------------
void DTail::trigger(int key)
{
	if (key == ' ')
	{
		emitter();
	}

}

//--------------------------------------
void DTail::setEmitterT(float t)
{
	_emitterT = t;
}

//--------------------------------------
void DTail::setEmitterNum(int num)
{
	_emitterNum = num;
}

//--------------------------------------
void DTail::setColor(float r)
{
	_color.r = r;
}

//--------------------------------------
void DTail::generateFlowFields()
{
	float offset = 0.05;
	for (int i = 0; i < cTailFieldRows; i++)
	{
		for (int j = 0; j < cTailFieldCols; j++)
		{
			//float theta = ofMap(ofNoise(i * offset, j * offset), 0, 1, 0, TWO_PI);
			float theta = ofRandom(PI * 0.45, PI * 0.55f);
			ofVec2f desired(cos(theta), sin(theta));
			_flowFields[i][j].set(desired.normalized() * ofRandom(cTailFlowFieldsMin, cTailFlowFieldsMax));
		}
	}
}

//--------------------------------------
void DTail::displayFlow(int x, int y, int w, int h)
{
	ofPushStyle();
	ofSetColor(255);
	ofFill();
	float unitW, unitH;
	unitW = w / cTailFieldCols;
	unitH = h / cTailFieldRows;

	for (int i = 0; i < cTailFieldRows; i++)
	{
		for (int j = 0; j < cTailFieldCols; j++)
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
ofVec2f DTail::getFlow(ofVec2f pos)
{
	int x = static_cast<int>(((pos.x - cTailRange.x) / cTailRange.width) * cTailFieldCols);
	int y = static_cast<int>(((pos.y - cTailRange.y) / cTailRange.height) * cTailFieldRows);


	x = (x == cTailFieldCols) ? x - 1 : x;
	y = (y == cTailFieldRows) ? y - 1 : y;

	if (x >= 0 && x < cTailFieldCols && y > 0 && y < cTailFieldRows)
	{
		return _flowFields[y][x];
	}
	else
	{
		return ofVec2f(0);
	}
}

//--------------------------------------
void DTail::checkPartical()
{
	_pList.remove_if([](const partical & p)
	{
		return p._life < 0.0f;
	});
}

//--------------------------------------
void DTail::drawPartical(partical& p)
{
	if (p._haveTail)
	{
		p._tail.draw();
	}
	else
	{
		ofDrawCircle(p._pos, p._size);
	}
}

//--------------------------------------
void DTail::emitter(int num)
{
	for (int i = 0; i < num; i++)
	{
		ofColor c = _color;
		c.a = ofRandom(100, 200);
		partical newP;
		float theta = ofRandom(PI * 0.45, PI * 0.55f);
		ofVec2f pos;
		pos.set(ofRandom(cTailRange.getMinX(), cTailRange.getMaxX()), cTailRange.getMinY());
		ofVec2f vec(cos(theta), sin(theta));
		ofVec2f acc(0);


		float lifeT = cTailRange.getHeight() / cTailParticalSpeedMin * 2.0f;
		vec *= ofRandom(cTailParticalSpeedMin, cTailParticalSpeedMax);
		newP.set(pos, vec, acc, lifeT);
		newP._color = c;

		newP._haveTail = (rand() % 3 != 0);
		_pList.push_back(newP);
	}

}
