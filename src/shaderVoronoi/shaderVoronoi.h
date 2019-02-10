#pragma once

#include "ofMain.h"



class shaderVoronoi
{
#pragma region PingPongFbo
private:
	class PingPongFbo
	{
	public:
		void allocate(int w, int h);
		void clear(int x = 0, int y = 0, int z = 0);
		void swap();

		ofFbo* getSrc();
		ofFbo* getDst();

	private:
		ofFbo* _src;
		ofFbo* _dst;
		ofFbo _buffer[2];
	};
#pragma endregion



public:
	shaderVoronoi()
		:_isSetup(false)
		, _isUpdate(false)
		, _isAlwaysUpdate(true)
		, _isDisplaySeed(false)
	{}

	void setup(int w, int h);
	void update();
	void draw();

	void setSeed(vector<ofVec2f>& seedList);

	void begin();
	void end();

private:
	void initialPosArray();
	void resetSeedData();

private:
	void drawSeed();

public:
	vector<ofVec2f>	_seedList;

private:
	bool _isSetup, _isDisplaySeed;
	bool _isUpdate, _isAlwaysUpdate;
	ofFbo _result, _posArray;


	PingPongFbo _pingPong;
	ofShader _drawColor, _seedCheck;

	int _width, _height;

	ofFbo _color;
	float* _seedInitial;

};