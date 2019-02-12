#include "displayMgr.h"
#include "ofxXmlSettings.h"

//------------------------------
void displayMgr::beginCtrl(bool needClear)
{
	if (_isCtrlBegin)
	{
		ofLog(OF_LOG_WARNING, "[displayMgr::beginCtrl]Need ctrl end");
		return;
	}

	_isCtrlBegin = true;
	_ctrlCanvas.begin();
	if (needClear)
	{
		ofClear(0);
	}
	
}

void displayMgr::endCtrl()
{
	if (!_isCtrlBegin)
	{
		ofLog(OF_LOG_WARNING, "[displayMgr::endCtrl]Need ctrl begin");
		return;
	}

	_ctrlCanvas.end();
	_isCtrlBegin = false;

}

void displayMgr::beginDisplay(eDisplayLayer layer, bool needClear)
{
	if (_drawLayer != eDisplayUnknow)
	{
		ofLog(OF_LOG_WARNING, "[displayMgr::beginDisplay]Need End");
		return;
	}

	_drawLayer = layer;
	_displayCanvas[_drawLayer].begin();
	if (needClear)
	{
		ofClear(0);
	}

}

void displayMgr::endDisplay()
{
	if (_drawLayer == eDisplayUnknow)
	{
		ofLog(OF_LOG_WARNING, "[displayMgr::endDisplay]Need Begin");
		return;
	}
	_displayCanvas[_drawLayer].end();
	_drawLayer = eDisplayUnknow;
}

void displayMgr::drawCtrl(int x, int y)
{
	ofPushStyle();
	ofSetColor(255);
	_ctrlCanvas.draw(x, y);
	ofPopStyle();
}

void displayMgr::drawDisplay(int x, int y)
{
	drawDisplay(x, y, cDisplayCanvasWidth, cDisplayCanvasHeight);
}

void displayMgr::drawDisplay(int x, int y, int w, int h)
{
	ofPushStyle();
	ofSetColor(255);
	if (_isSingleColor)
	{
		ofBackground(_displayBGColorFrom);
	}
	else
	{
		ofBackgroundGradient(_displayBGColorFrom, _displayBGColorTo, _gradientMode);
	}

	ofSetColor(255);
	for (auto& iter : _displayCanvas)
	{
		iter.draw(x, y, w, h);
	}

	ofSetColor(0, _displayCoverAlpha);
	ofFill();
	ofDrawRectangle(x, y, w, h);

	ofPopStyle();
}

void displayMgr::clearAllDisplay()
{
	for (auto& iter : _displayCanvas)
	{
		iter.begin();
		ofClear(0);
		iter.end();
	}
}

void displayMgr::setCoverAlpha(int alpha)
{
	_displayCoverAlpha = MAX(MIN(alpha, 255), 0);
}

void displayMgr::setBGMode(bool isSingleColor, ofGradientMode gMode)
{
	_isSingleColor = isSingleColor;
	if (!_isSingleColor)
	{
		_gradientMode = gMode;
	}
}

void displayMgr::setBGColor(ofColor c)
{
	_displayBGColorFrom.set(c);
}

void displayMgr::setBGColor(ofColor from, ofColor to)
{
	_displayBGColorFrom.set(from);
	_displayBGColorTo.set(to);
}


#pragma region Singleton
//--------------------------------------------------------------
displayMgr* displayMgr::pInstance = 0;
displayMgr* displayMgr::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new displayMgr();
	}
	return pInstance;
}

//--------------------------------------------------------------
void displayMgr::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}
#pragma endregion

