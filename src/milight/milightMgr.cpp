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
	drawLight(x + 300, y, 90, 300);
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
	for (int i = 0; i < cLightNum; i++)
	{
		_lightList[i].clear();
	}
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
	float unitW = (float)width / 3.0f;
	float unitH = (float)height / cLightNum;

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
		ofDrawRectangle(pos.x + unitW, pos.y, unitW, unitH);

		ofColor c = cLightWarmWhite; ;
		c.setBrightness(iter.getWarmWhite());
		ofSetColor(c);
		ofDrawRectangle(pos.x + unitW * 2, pos.y, unitW, unitH);
		
		ofNoFill();
		ofSetColor(255);
		ofDrawRectangle(pos, unitW * 3, unitH);
		ofPopStyle();
		pos.y += unitH;
	}
	ofPopMatrix();
}


#pragma endregion

#pragma region GUI
void milightMgr::initGUI()
{
	_lightIdx = 0;
	_lightGUI.setup();
	ofAddListener(_lightGUI.isUpdateE, this, &milightMgr::onGUIValueUpdate);
}

void milightMgr::updateGUI()
{
	auto light = _lightList[_lightIdx];
	_gLLightNo = ofToString(_lightIdx);
	_gCLightColor.set(light.getColor());
	_gSWarmWhite.set(light.getWarmWhite());
	_gSColdWhite.set(light.getColdWhite());
}

void milightMgr::drawGUI(int x, int y)
{
}

void milightMgr::setLightIdx(int idx)
{
	_lightIdx = idx;
	updateGUI();
}

void milightMgr::onGUIValueUpdate()
{
}

#pragma endregion


#pragma region Cue Table
void milightMgr::initCueTable()
{
	_cueTable.init("_cue.xml");
}

void milightMgr::drawCueTable(int x, int y)
{
	_cueTable.drawGUI(x, y);
}
#pragma endregion


#pragma region Singleton
//--------------------------------------------------------------
milightMgr* milightMgr::pInstance = 0;
milightMgr* milightMgr::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new milightMgr();
	}
	return pInstance;
}

//--------------------------------------------------------------
void milightMgr::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}
#pragma endregion
