#include "ofxCTHD512.h"
#include "ofMain.h"

void ofxCTHD512::init(float rate)
{
	_hasConnection = isDMXOpen();

	if (!_hasConnection)
	{
		ofLog(OF_LOG_NOTICE, "[ofxCTHD512::init]Failed");
		return;
	}

	ofLog(OF_LOG_NOTICE, "[ofxCTHD512::init]Connection flash rate");
	_timer = _updateTime = 1.0f / rate;
	ZeroMemory(_sendBuffer, 512);
	ZeroMemory(_dataBuffer, 512);
	reset(0);
}

void ofxCTHD512::update(float delta)
{
	if (!_hasConnection)
	{
		return;
	}
	_timer -= delta;
	if (_timer <= 0.0f)
	{
		checkBuffer();
		_timer = _updateTime;
	}
}

void ofxCTHD512::set(int addr, unsigned char value)
{
	if (!_hasConnection)
	{
		return;
	}
	if (addr < 1 || addr > 512)
	{
		ofLog(OF_LOG_ERROR, "[ofxCTHD512::set]Wrong Address");
		return;
	}

	_sendBuffer[addr - 1] = value;
}

void ofxCTHD512::reset(unsigned char value)
{
	if (!_hasConnection)
	{
		return;
	}
	unsigned char data[512];
	memset(data, value, 512);
	DMXSendBox(0, data);
}

void ofxCTHD512::checkBuffer()
{
	for (int i = 0; i < 512; i++)
	{
		if (_dataBuffer[i] != _sendBuffer[i])
		{
			DMXSend(i + 1, _sendBuffer[i]);
		}
	}
	CopyMemory(_dataBuffer, _sendBuffer, 512);
}
//--------------------------------------------------------------
ofxCTHD512* ofxCTHD512::pInstance = 0;
ofxCTHD512* ofxCTHD512::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new ofxCTHD512();
	}
	return pInstance;
}

//--------------------------------------------------------------
void ofxCTHD512::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}