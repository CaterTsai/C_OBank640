#include "milightCueTable.h"

milightCueTable::milightCueTable()
	:_cueNo(0)
	, _lightNo(0)
	, _cuePath("default.xml")
{
	initGUI();
	_cueTable.push_back(milightCueList());
}

void milightCueTable::init(string path) {
	_cuePath = path;
	loadCue();
}

void milightCueTable::drawCue(int x, int y)
{
	ofPushMatrix();
	ofTranslate(x, y);
	ofVec2f pos;
	pos.x = 0;
	pos.y = 0;
	for (auto& iter : _cueTable[_cueNo])
	{
		ofSetColor(iter._color1);
		ofCircle(pos, 20);

		pos.x += 40;
	}
	ofPopMatrix();
}

void milightCueTable::drawGUI(int x, int y)
{
	ofPushMatrix();
	ofTranslate(x, y);
	_lightGUI.draw();
	ofPopMatrix();
}

milightCueList& milightCueTable::getCue(int i)
{
	return _cueTable[i];
}

void milightCueTable::loadCue()
{
	ofxXmlSettings xml;
	if (!xml.load(_cuePath))
	{
		ofLog(OF_LOG_WARNING, "[milightCueTable::loadCue]Cant load cue file, use the defalut cue");
		return;
	}

	_cueTable.clear();
	int cueListNum = xml.getNumTags("cueList");
	for (int i = 0; i < cueListNum; i++)
	{
		xml.pushTag("cueList", i);
		int cueNum = xml.getNumTags("cue");
		milightCueList cueList;
		for (int j = 0; j < MIN(cueNum, cueList.size()) ; j++)
		{
			xml.pushTag("cue", j);
			cueList[j]._type = (eMilightCueType)xml.getValue("state", 0);
			cueList[j]._cueDuration = xml.getValue("cueDuration", 0.0f);
			cueList[j]._warmWhiteVal1 = xml.getValue("warmWhite1", 0);
			cueList[j]._coldWhiteVal1 = xml.getValue("coldWhite1", 0);
			cueList[j]._color1.r = xml.getValue("color1_r", 0);
			cueList[j]._color1.g = xml.getValue("color1_g", 0);
			cueList[j]._color1.b = xml.getValue("color1_b", 0);

			cueList[j]._loopDuration = xml.getValue("loopDuration", 0.0f);
			cueList[j]._warmWhiteVal2 = xml.getValue("warmWhite2", 0);
			cueList[j]._coldWhiteVal2 = xml.getValue("coldWhite2", 0);
			cueList[j]._color2.r = xml.getValue("color2_r", 0);
			cueList[j]._color2.g = xml.getValue("color2_g", 0);
			cueList[j]._color2.b = xml.getValue("color2_b", 0);
			xml.popTag();
		}
		xml.popTag();
		_cueTable.push_back(cueList);
	}

	setGUIVal();
}

void milightCueTable::saveCue()
{
	ofxXmlSettings xml;
	for (int i = 0; i < _cueTable.size(); i++)
	{
		xml.addTag("cueList");
		xml.pushTag("cueList", i);
		for (int j = 0; j < _cueTable[i].size(); j++)
		{
			xml.addTag("cue");
			xml.pushTag("cue", j);
			xml.addValue("state", _cueTable[i][j]._type);
			xml.addValue("cueDuration", _cueTable[i][j]._cueDuration);
			xml.addValue("warmWhite1", _cueTable[i][j]._warmWhiteVal1);
			xml.addValue("coldWhite1", _cueTable[i][j]._coldWhiteVal1);
			xml.addValue("color1_r", _cueTable[i][j]._color1.r);
			xml.addValue("color1_g", _cueTable[i][j]._color1.g);
			xml.addValue("color1_b", _cueTable[i][j]._color1.b);

			xml.addValue("loopDuration", _cueTable[i][j]._loopDuration);
			xml.addValue("warmWhite2", _cueTable[i][j]._warmWhiteVal2);
			xml.addValue("coldWhite2", _cueTable[i][j]._coldWhiteVal2);
			xml.addValue("color2_r", _cueTable[i][j]._color2.r);
			xml.addValue("color2_g", _cueTable[i][j]._color2.g);
			xml.addValue("color2_b", _cueTable[i][j]._color2.b);
			xml.popTag();
		}
		xml.popTag();
	}
	xml.save(_cuePath);
	ofLog(OF_LOG_NOTICE, "[milightCueTable::saveCue]Save cue table success");
}

#pragma region GUI
void milightCueTable::onGUIValueUpdate()
{
	updateCue();
}

void milightCueTable::onBtnAddCue()
{
	_cueNo += 1;
	_cueTable.insert(_cueTable.begin() + _cueNo, milightCueList());
	setGUIVal();
}

void milightCueTable::onBtnDelCue()
{
	if (_cueTable.size() == 1)
	{
		ofLog(OF_LOG_ERROR, "[milightCueTable::delCue]Have less 1 cue");
		return;
	}

	_cueTable.erase(_cueTable.begin() + _cueNo);
	setGUIVal();
}

void milightCueTable::onBtnNextCue()
{
	_cueNo = (_cueNo + 1) % _cueTable.size();
	setGUIVal();
}

void milightCueTable::onBtnPrevCue()
{
	_cueNo -= 1;
	if (_cueNo < 0)
	{
		_cueNo = _cueTable.size() - 1;
	}
	setGUIVal();
}

void milightCueTable::onBtnNextLight()
{
	_lightNo = (_lightNo + 1) % _cueTable[_cueNo].size();
	setGUIVal();
}

void milightCueTable::onBtnPrevLight()
{
	_lightNo -= 1;
	if (_lightNo < 0)
	{
		_lightNo = _cueTable[_cueNo].size() - 1;
	}
	setGUIVal();
}

void milightCueTable::initGUI()
{
	_lightGUI.setup();
	ofAddListener(_lightGUI.isUpdateE, this, &milightCueTable::onGUIValueUpdate);
	ofAddListener(_lightGUI.savePressedE, this, &milightCueTable::saveCue);
	_gBAddCue.addListener(this, &milightCueTable::onBtnAddCue);
	_gBDelCue.addListener(this, &milightCueTable::onBtnDelCue);
	_gBNextCue.addListener(this, &milightCueTable::onBtnNextCue);
	_gBPrevCue.addListener(this, &milightCueTable::onBtnPrevCue);
	_gBNextLight.addListener(this, &milightCueTable::onBtnNextLight);
	_gBPrevLight.addListener(this, &milightCueTable::onBtnPrevLight);

	_lightGUI.add(_gLCueNo.set("Cue No", ofToString(_cueNo)));
	_lightGUI.add(_gBNextCue.setup("Next Cue"));
	_lightGUI.add(_gBPrevCue.setup("Prev Cue"));
	_lightGUI.add(_gBAddCue.setup("Add Cue"));
	_lightGUI.add(_gBDelCue.setup("Del Cue"));
	_lightGUI.add(_gLLightNo.set("Light No", ofToString(_lightNo)));
	_lightGUI.add(_gBNextLight.setup("Next Light"));
	_lightGUI.add(_gBPrevLight.setup("Prev Light"));

	_lightGUI.add(_gSState.set("Light State", 0, 0, 3));
	_lightGUI.add(_gLLightState.set("State Name", cTypeName[0]));
	_lightGUI.add(_gSCueDuration.set("Cue In¡@Duration", 0, 0, 20));

	_lightGUI.add(_gCLightColor.set("RGB Color", ofColor(0, 0, 0)));
	_lightGUI.add(_gSWarmWhite.set("Warm White", 0, 0, 255));
	_lightGUI.add(_gSColdWhite.set("Cold White", 0, 0, 255));

	_lightGUI.add(_gSLoopDuration.set("Loop Duration", 0, 0, 20));
	_lightGUI.add(_gCLoopColor.set("Loop RGB Color", ofColor(0, 0, 0)));
	_lightGUI.add(_gSLoopWarmWhite.set("Loop Warm White", 0, 0, 255));
	_lightGUI.add(_gSLoopColdWhite.set("Loop Cold White", 0, 0, 255));
}

void milightCueTable::setGUIVal()
{
	auto cue = _cueTable[_cueNo][_lightNo];
	_gLCueNo = ofToString(_cueNo);
	_gLLightNo = ofToString(_lightNo);

	clearGUIVal();
	switch (cue._type)
	{
	case eCueOff:
	{
		_gSState = 1;
		_gSCueDuration = cue._cueDuration;
		break;
	}
	case eCueToColor:
	{
		_gSState = 2;
		_gCLightColor = cue._color1;
		_gSWarmWhite = cue._warmWhiteVal1;
		_gSColdWhite = cue._coldWhiteVal1;
		_gSCueDuration = cue._cueDuration;
		break;
	}
	case eCueToLoop:
	{
		_gSState = 3;
		_gCLightColor = cue._color1;
		_gSWarmWhite = cue._warmWhiteVal1;
		_gSColdWhite = cue._coldWhiteVal1;
		_gCLoopColor = cue._color2;
		_gSLoopWarmWhite = cue._warmWhiteVal2;
		_gSLoopColdWhite = cue._coldWhiteVal2;
		_gSCueDuration = cue._cueDuration;
		_gSLoopDuration = cue._loopDuration;
		break;
	}
	}
	_gLLightState = cTypeName[_gSState];
}

void milightCueTable::clearGUIVal()
{
	_gCLightColor.set(0);
	_gCLoopColor.set(0);
	_gSState = 0;
	_gLLightState = cTypeName[_gSState];
	_gSWarmWhite = _gSColdWhite = _gSLoopWarmWhite = _gSLoopColdWhite = _gSCueDuration = _gSLoopDuration = 0.0f;
}

void milightCueTable::updateCue()
{
	if (_cueTable.size() <= 0)
	{
		return;
	}
	auto cue = _cueTable[_cueNo][_lightNo];
	switch (_gSState)
	{
	case 0:
	{
		cue._type = eCueStay;
		break;
	}
	case 1:
	{
		cue._type = eCueOff;
		cue._cueDuration = _gSCueDuration;
		break;
	}
	case 2:
	{
		cue._type = eCueToColor;
		cue._cueDuration = _gSCueDuration;
		cue._color1 = _gCLightColor;
		cue._coldWhiteVal1 = _gSColdWhite;
		cue._warmWhiteVal1 = _gSWarmWhite;
		break;
	}
	case 3:
	{
		cue._type = eCueToLoop;
		cue._cueDuration = _gSCueDuration;
		cue._loopDuration = _gSLoopDuration;
		cue._color1 = _gCLightColor;
		cue._coldWhiteVal1 = _gSColdWhite;
		cue._warmWhiteVal1 = _gSWarmWhite;
		cue._color2 = _gCLightColor;
		cue._coldWhiteVal2 = _gSLoopColdWhite;
		cue._warmWhiteVal2 = _gSLoopWarmWhite;
		break;
	}
	}

	_cueTable[_cueNo][_lightNo] = cue;
}
#pragma endregion


