#include "postFilter.h"

//-------------------------------------
void postFilter::init(int w, int h, bool arb)
{
	_postMgr.init(w, h, arb);

	_postMgr.createPass<BloomPass>()->setEnabled(false);
	_postMgr.createPass<BloomPass>()->setEnabled(false);
	_postMgr.createPass<NoiseWarpPass>()->setEnabled(false);
	_postMgr.createPass<ZoomBlurPass>()->setEnabled(false);
	_postMgr.createPass<KaleidoscopePass>()->setEnabled(false);
	_postMgr.createPass<EdgePass>()->setEnabled(false);
	_postMgr.createPass<PixelatePass>()->setEnabled(false);
	_postMgr.createPass<RGBShiftPass>()->setEnabled(false);
	_postMgr.createPass<ToonPass>()->setEnabled(false);

	_postMgr.setFlip(false);

}

//-------------------------------------
void postFilter::filterEnable(ePostFilterType type)
{
	auto isEnable = !_postMgr[(int)type]->getEnabled();
	_postMgr[(int)type]->setEnabled(isEnable);
	
}

//-------------------------------------
void postFilter::filterEnable(ePostFilterType type, bool isEnable)
{
	_postMgr[(int)type]->setEnabled(isEnable);
	
}

//-------------------------------------
void postFilter::disableAll()
{
	for (int i = 0; i < _postMgr.size(); i++)
	{
		
		_postMgr[i]->disable();
	}
}


#pragma region Singleton
//--------------------------------------------------------------
postFilter* postFilter::pInstance = 0;
postFilter* postFilter::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new postFilter();
	}
	return pInstance;
}

//--------------------------------------------------------------
void postFilter::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}
#pragma endregion




