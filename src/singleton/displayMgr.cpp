#include "displayMgr.h"
#include "ofxXmlSettings.h"

#pragma region Basic
//------------------------------
displayMgr::displayMgr()
	:_isSetup(false)
	,_ctrlID(-1)
{
}

#pragma endregion

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




