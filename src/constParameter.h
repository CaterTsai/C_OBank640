#pragma once

#include "ofMain.h"

const int cWindowWidth = 1920;
const int cWindowHeight = 1080;

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


	, eVideoNum
};

const int cTrainVideoNum = 14;