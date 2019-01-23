#include "milightMgr.h"
#include "ofxCTHD512.h"

#pragma region Basic
void milightMgr::setup()
{
	initLight();
	initCueTable();
	_cueId = 0;
}

void milightMgr::update(float delta)
{
	updateLight(delta);
}

void milightMgr::draw(int x, int y)
{
	drawCueTable(x, y);
	drawLight(x + 300, y, 300, 100);
}

void milightMgr::toCue(int cueNo)
{
	if (cueNo < 0 || cueNo >= _cueTable.getCueNum())
	{
		return;
	}
	_cueId = cueNo;
	playCue();
}

void milightMgr::nextCue()
{
	_cueId = (_cueId + 1) % _cueTable.getCueNum();
	playCue();
}

void milightMgr::prevCue()
{
	int cueNo = _cueTable.getCueNo();

	cueNo -= 1;
	if (cueNo < 0)
	{
		cueNo = _cueTable.getCueNo() - 1;
	}
	playCue();
}

void milightMgr::playCue()
{
	auto& cueList = _cueTable.getCue(_cueId);
	for (int i = 0; i < cLightNum; i++)
	{
		_lightList[i].setCue(cueList[i]);
	}
}
void milightMgr::clearCue()
{
}
#pragma endregion

#pragma region light
void milightMgr::initLight()
{
	ofxCTHD512::GetInstance()->init();

	int dmxAddr = cLightStartAddr;
	for (int i = 0; i < cLightNum; i++)
	{
		_lightList[i].setup(dmxAddr);
		dmxAddr += cLightDMXChannel;
	}
}

void milightMgr::updateLight(float delta)
{
	for (auto& iter : _lightList)
	{
		iter.update(delta);
	}
}

void milightMgr::drawLight(int x, int y, int width, int height)
{
	float unitW = (float)width / cLightNum;
	float unitH = (float)height / 3.0f;

	ofPushMatrix();
	ofTranslate(x, y);
	ofVec2f pos(0, 0);
	for (auto& iter : _lightList)
	{
		ofPushStyle();
		ofFill();
		ofSetColor(iter.getColor());
		ofDrawRectangle(pos.x, pos.y, unitW, unitH);

		ofSetColor(iter.getColdWhite());
		ofDrawRectangle(pos.x, pos.y + unitH, unitW, unitH);

		ofColor c = cLightWarmWhite; ;
		c.setBrightness(iter.getWarmWhite());
		ofSetColor(c);
		ofDrawRectangle(pos.x, pos.y + unitH * 2, unitW, unitH);
		
		ofNoFill();
		ofSetColor(255);
		ofDrawRectangle(pos, unitW, unitH * 3);
		ofPopStyle();

		
		pos.x += unitW;
	}
	ofPopMatrix();
}
#pragma endregion

#pragma region Cue Table
void milightMgr::initCueTable()
{
	_cueTable.init("cue.xml");
}

void milightMgr::drawCueTable(int x, int y)
{
	_cueTable.drawGUI(x, y);
}
#pragma endregion
