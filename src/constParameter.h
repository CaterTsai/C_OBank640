#pragma once

#include "ofMain.h"

const int cWindowWidth = 1920;
const int cWindowHeight = 1080;

const int cViewWidth = 800;
const int cViewHeight = 800;

enum eDisplayLayer : int{
	eDisplayFront = 0,
	eDisplayBack,
	eDisplayLayerNum,
	eDisplayUnknow
};

//--------------
//Video Mgr
enum eVideoType : int
{
	//------------------
	eVideoTrainView01 = 0
	, eVideoTrainView02
	, eVideoTrainView03
	, eVideoTrainView04
	, eVideoTrainView05
	, eVideoTrainView06
	, eVideoTrainView07
	, eVideoTrainView08
	, eVideoTrainView09
	, eVideoTrainView10
	, eVideoTrainView11
	, eVideoTrainView12
	, eVideoTrainView13
	, eVideoTrainView14

	, eVideoDarkOcean
	, eVideoWaterWave
	, eVideoEndlessOcean
	, eVideoUnderWater
	, eVideoNapoli
	, eVideoTwilight
	, eVideoNum
};

const int cTrainVideoNum = 14;