#include "shaderVoronoi.h"

#pragma region PingPongFbo
//--------------------------------------------------------------
void shaderVoronoi::PingPongFbo::allocate(int w, int h)
{
	for(int idx_ = 0; idx_ < 2; idx_++)
	{
		_buffer[idx_].allocate(w, h, GL_RGB32F);
	}

	clear();
	_src = &_buffer[0];
	_dst = &_buffer[1];
}

//--------------------------------------------------------------
void shaderVoronoi::PingPongFbo::clear(int x, int y, int z)
{
	for(int idx_ = 0; idx_ < 2; idx_++)
	{
		_buffer[idx_].begin();
		ofClear(x, y, z, 255);
		_buffer[idx_].end();
	}
}

//--------------------------------------------------------------
void shaderVoronoi::PingPongFbo::swap()
{
	std::swap(_src, _dst);
}
	
//--------------------------------------------------------------
ofFbo* shaderVoronoi::PingPongFbo::getSrc()
{
	return _src;
}

//--------------------------------------------------------------
ofFbo* shaderVoronoi::PingPongFbo::getDst()
{
	return _dst;
}
#pragma endregion

#pragma region shaderVoronoi
void shaderVoronoi::setup(int w, int h)
{
	if(_isSetup)
	{
		return;
	}
	_width = w;
	_height = h;
	bool bResult_ = true;
	bResult_ &= _drawColor.load("", "shader/drawColor.frag");
	bResult_ &= _seedCheck.load("", "shader/seedCheck.frag");

	_seedInitial = new float[_width * _height *  3];	

	if(!bResult_)
	{
		ofLog(OF_LOG_ERROR, "[shaderVoronoi]setup failed");
	}

	initialPosArray();
	_result.allocate(_width, _height, GL_RGB32F);
	_pingPong.allocate(_width, _height);

	_color.allocate(_width, _height, GL_RGB);
	_color.begin();
	ofClear(0, 255);
	_color.end();

	_isSetup = bResult_;
}

//--------------------------------------------------------------
void shaderVoronoi::update()
{	
	if(!_isSetup)
	{
		return;
	}

	if(_isAlwaysUpdate || _isUpdate)
	{
		resetSeedData();

		//processing the address
		float offset_ = static_cast<int>(_width / 2.0);
		while(offset_ >= 1.0)
		{
			_pingPong.getDst()->begin();
			_seedCheck.begin();
			_seedCheck.setUniformTexture("back", _pingPong.getSrc()->getTextureReference(), 0);
			_seedCheck.setUniformTexture("posData", _posArray.getTextureReference(), 1);
			_seedCheck.setUniform1i("offset", static_cast<int>(offset_));
			{
				_pingPong.getSrc()->draw(0, 0);
			}
			_seedCheck.end();
			_pingPong.getDst()->end();

			_pingPong.swap();
			offset_ /= 2.0;
		}
		_isUpdate = false;
	}

	//Draw to result
	_result.begin();
	ofClear(0, 255);
	_drawColor.begin();
	_drawColor.setUniformTexture("seedPos", _pingPong.getSrc()->getTextureReference(), 1);
	{
		_color.draw(0, 0);
	}
	_drawColor.end();
	_result.end();
}

//--------------------------------------------------------------
void shaderVoronoi::draw()
{
	if(!_isSetup)
	{
		return;
	}

	ofPushStyle();
	{
		ofSetColor(255);
		_result.draw(0, 0);
	}
	ofPopStyle();

	drawSeed();
}

//--------------------------------------------------------------
void shaderVoronoi::setSeed(vector<ofVec2f>& seedList)
{
	_seedList.clear();
	_seedList = seedList;
	_isUpdate = true;
}

//--------------------------------------------------------------
void shaderVoronoi::begin()
{
	_color.begin();
	ofClear(0, 255);

}

//--------------------------------------------------------------
void shaderVoronoi::end()
{
	_color.end();
}
//--------------------------------------------------------------
void shaderVoronoi::initialPosArray()
{
	float* posArray_ = new float[_width * _height * 3];

	for(int y = 0; y < _height; y++)
	{
		for(int x = 0; x < _width; x++)
		{
			int index_ = (x + y * _width) * 3;
			posArray_[index_] = x;
			posArray_[index_ + 1] = y;
			posArray_[index_ + 2] = 0.0;
		}
	}

	_posArray.allocate(_width, _height, GL_RGB32F);
	_posArray.getTextureReference().loadData(posArray_, _width, _height, GL_RGB);
	delete [] posArray_;
}

//--------------------------------------------------------------
void shaderVoronoi::resetSeedData()
{
	//clear the fbo
	_pingPong.clear();

	ZeroMemory(_seedInitial, sizeof(float ) * _width * _height *  3);
	for(auto& Iter_ : _seedList)
	{
		int index_ = ((int)Iter_.x + (int)Iter_.y * _width) * 3;
		_seedInitial[index_] = Iter_.x;
		_seedInitial[index_ + 1] = Iter_.y;
		_seedInitial[index_ + 2] = 1;
	}

	_pingPong.getSrc()->getTextureReference().loadData(_seedInitial, _width, _height, GL_RGB);
}

//--------------------------------------------------------------
void shaderVoronoi::drawSeed()
{
	if(!_isDisplaySeed)
	{
		return;
	}
	ofPushStyle();
	{
		ofFill();
		for(auto& Iter_ : _seedList)
		{
			ofCircle(Iter_, 1);
		}
	}
	ofPopStyle();
}
#pragma endregion
