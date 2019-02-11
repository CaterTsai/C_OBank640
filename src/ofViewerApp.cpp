#include "ofViewerApp.h"


#pragma region Basic
void ofViewerApp::setup()
{

	//Singleton
	displayMgr::GetInstance();
	postFilter::GetInstance()->init(cWindowWidth, cWindowHeight, true);

	midiCtrl::GetInstance()->init();
	midiCtrl::GetInstance()->addListener(this);

	initVideo();
	initScene();

	ofSetFrameRate(60);


	_mainTimer = ofGetElapsedTimef();
}

//----------------------------------
void ofViewerApp::update()
{
	float delta = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta;

	updateMidi();
	videoMgr::GetInstance()->update();
	_scenceMgr[_nowScence]->update(delta);


	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//----------------------------------
void ofViewerApp::draw()
{
	ofSetBackgroundColor(0);
	_scenceMgr[_nowScence]->draw();


	if (_showMsg)
	{
		ofSetColor(255);
		string state =  + _isStart ? "Play" : "Stop";
		ofDrawBitmapStringHighlight("State :" + state, ofVec2f(0, 95));
		_scenceMgr[_nowScence]->drawMsg(ofVec2f(0, 110));
	}

}

//----------------------------------
void ofViewerApp::keyPressed(int key)
{
	eCtrlType type = ctrlMap::GetInstance()->key2Ctrl[key];
	if (type >= 0 && type < eCtrl_GlobalNum)
	{
		control(type);
	}
	else
	{
		_scenceMgr[_nowScence]->control(type);
	}

	if (key == OF_KEY_BACKSPACE)
	{
		_showMsg ^= true;
	}
}

//----------------------------------
void ofViewerApp::control(eCtrlType ctrl, int value)
{
	switch (ctrl)
	{
	case eCtrl_Start:
	{
		if (value == cMidiButtonPress)
		{
			_scenceMgr[_nowScence]->start();
			_isStart = true;
		}
		break;
	}
	case eCtrl_Stop:
	{
		if (value == cMidiButtonPress)
		{
			_scenceMgr[_nowScence]->stop();
			_isStart = false;
			displayMgr::GetInstance()->clearAllDisplay();
		}
		break;
	}
	case eCtrl_NextScence:
	{
		if (value == cMidiButtonPress)
		{
			postFilter::GetInstance()->disableAll();
			auto nextScence = (eSType)((_nowScence + 1) % eSTypeNum);
			if (_isStart)
			{
				_scenceMgr[_nowScence]->stop();
				_scenceMgr[nextScence]->start();
			}
			_nowScence = nextScence;

			displayMgr::GetInstance()->clearAllDisplay();
		}

		break;
	}
	case eCtrl_PrevScence:
	{
		if (value == cMidiButtonPress)
		{
			postFilter::GetInstance()->disableAll();
			auto nextScence = (eSType)((_nowScence - 1) % eSTypeNum);
			if (nextScence < 0)
			{
				nextScence = (eSType)(eSTypeNum - 1);
			}
			if (_isStart)
			{
				_scenceMgr[_nowScence]->stop();
				_scenceMgr[nextScence]->start();
			}
			_nowScence = nextScence;
			displayMgr::GetInstance()->clearAllDisplay();

		}
		break;
	}
#pragma region Filter
	case eCtrl_DisableAllFilter:
	{
		if (value == cMidiButtonPress)
		{
			postFilter::GetInstance()->disableAll();
		}
		break;
	}
	case eCtrl_Filter1:
	{
		if (value == cMidiButtonPress)
		{
			postFilter::GetInstance()->filterEnable(ePostFilterType::ePostBloom);
		}
		break;
	}
	case eCtrl_Filter2:
	{
		if (value == cMidiButtonPress)
		{
			postFilter::GetInstance()->filterEnable(ePostFilterType::ePostBloomTwo);
		}
		break;
	}
	}
#pragma endregion
}

#pragma endregion
//----------------------------------
void ofViewerApp::initScene()
{
	_scenceMgr.push_back(ofPtr<SIdle01>(new SIdle01()));
	_scenceMgr.push_back(ofPtr<SFrance01>(new SFrance01()));
	_scenceMgr.push_back(ofPtr<SFrance02>(new SFrance02()));
	_scenceMgr.push_back(ofPtr<SFrance03>(new SFrance03()));
	_scenceMgr.push_back(ofPtr<SFrance04>(new SFrance04()));
	_scenceMgr.push_back(ofPtr<SFrance05>(new SFrance05()));
	_scenceMgr.push_back(ofPtr<SFrance06>(new SFrance06()));
	_scenceMgr.push_back(ofPtr<SFrance07>(new SFrance07()));
	_scenceMgr.push_back(ofPtr<SIdle02>(new SIdle02()));
	_scenceMgr.push_back(ofPtr<SItaly01>(new SItaly01()));
	_scenceMgr.push_back(ofPtr<SItaly02>(new SItaly02()));
	_scenceMgr.push_back(ofPtr<SItaly03>(new SItaly03()));
	_scenceMgr.push_back(ofPtr<SItaly04>(new SItaly04()));
	_scenceMgr.push_back(ofPtr<SItaly05>(new SItaly05()));
	_scenceMgr.push_back(ofPtr<SItaly06>(new SItaly06()));

	_nowScence = eSIdle01;
}

//----------------------------------
void ofViewerApp::initVideo()
{
	for (int i = 0; i < cTrainVideoNum; i++)
	{
		videoMgr::GetInstance()->add((eVideoType)i, "videos/train/" + ofToString(i + 1, 2, '0') + ".avi");
	}
}

//----------------------------------
void ofViewerApp::updateMidi()
{
	for (int i = 0; i < _midiQueue.size(); i++)
	{
		auto ctrl = _midiQueue.begin();
		if (ctrl->type >= 0 && ctrl->type < eCtrl_GlobalNum)
		{
			control(ctrl->type, ctrl->value);
		}
		else
		{
			_scenceMgr[_nowScence]->control(ctrl->type, ctrl->value);
		}
		_midiQueue.pop_front();
	}
}

//----------------------------------
void ofViewerApp::newMidiMessage(ofxMidiMessage & msg)
{
	midiCtrlData newCtrl;
	newCtrl.type = ctrlMap::GetInstance()->midi2Ctrl[msg.control];
	newCtrl.value = msg.value;
	_midiQueue.push_back(newCtrl);
}

