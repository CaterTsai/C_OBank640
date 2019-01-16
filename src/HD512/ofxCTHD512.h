#pragma once


#include "HD512DLL.h"
using namespace HD512;

class ofxCTHD512 {
public:
	void init(float rate = 44.0f);
	void update(float delta);
	void set(int addr, unsigned char value);
	void reset(unsigned char value);

private:
	void checkBuffer();

private:
	bool _hasConnection;
	float _timer, _updateTime;
	unsigned char _sendBuffer[512], _dataBuffer[512];
	//-------------------
	//Singleton
	//-------------------
private:
	ofxCTHD512()
		:_hasConnection(false)
	{};
	~ofxCTHD512()
	{
		ofxCTHD512::Destroy();
	}
	ofxCTHD512(ofxCTHD512 const&);
	void operator=(ofxCTHD512 const&);

public:
	static ofxCTHD512* GetInstance();
	static void Destroy();

private:
	static ofxCTHD512 *pInstance;

};