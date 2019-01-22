#include "milightMgr.h"
#include "ofxCTHD512.h"

#pragma region Basic
void milightMgr::setup()
{
}

void milightMgr::update(float delta)
{
}

void milightMgr::draw(int x, int y)
{
}

void milightMgr::toCue(int cueNo)
{
}

void milightMgr::nextCue()
{
}

void milightMgr::prevCue()
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

void milightMgr::drawLight(int x, int y)
{

}
#pragma endregion

#pragma region Cue Table
void milightMgr::initCueTable()
{
	_cueTable.init("_cueTable.xml");
}

void milightMgr::drawCueTable(int x, int y)
{
	_cueTable.drawGUI(x, y);
}
#pragma endregion
