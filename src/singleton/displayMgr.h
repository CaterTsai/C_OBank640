#pragma once

#include "../constParameter.h"

const int cCtrlCanvasWidth = 1000;
const int cCtrlCanvasHeight = 1000;

const int cDisplayCanvasWidth = cWindowWidth;
const int cDisplayCanvasHeight = cWindowHeight;

class displayMgr
{
public:
	void beginCtrl(bool needClear = true);
	void endCtrl();

	void beginDisplay(eDisplayLayer layer, bool needClear = true);
	void endDisplay();

	void drawCtrl(int x, int y);
	void drawDisplay(int x, int y);
	void clearAllDisplay();

	void setCoverAlpha(int alpha);
	void setBGMode(bool isSingleColor, ofGradientMode gMode = OF_GRADIENT_LINEAR);
	void setBGColor(ofColor c);
	void setBGColor(ofColor from, ofColor to);

private:
	bool _isCtrlBegin;
	int _displayCoverAlpha;

	bool _isSingleColor;
	ofGradientMode _gradientMode;
	ofColor _displayBGColorFrom, _displayBGColorTo;

	ofFbo _ctrlCanvas;
	eDisplayLayer _drawLayer;
	array<ofFbo, eDisplayLayerNum> _displayCanvas;

//-------------------
//Singleton
//-------------------
private:
	displayMgr():
		_isCtrlBegin(false)
		, _drawLayer(eDisplayUnknow)
		, _displayCoverAlpha(0)
		, _isSingleColor(true)
		, _gradientMode(OF_GRADIENT_LINEAR)
		, _displayBGColorFrom(0)
		, _displayBGColorTo(0)
	{
		_ctrlCanvas.allocate(cCtrlCanvasWidth, cCtrlCanvasHeight);
		for (auto& iter : _displayCanvas)
		{
			iter.allocate(cDisplayCanvasWidth, cDisplayCanvasHeight);
		}
	}
		
	~displayMgr(){
		_ctrlCanvas.clear();
		_ctrlCanvas.destroy();
		for (auto& iter : _displayCanvas)
		{
			iter.clear();
			iter.destroy();
		}
	}
	displayMgr(displayMgr const&);
	void operator=(displayMgr const&);
public:
	static displayMgr* GetInstance();
	static void Destroy();

private:
	static displayMgr *pInstance;
};