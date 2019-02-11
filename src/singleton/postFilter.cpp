#include "postFilter.h"

//-------------------------------------
void postFilter::init(int w, int h, bool arb)
{
	for(auto& iter : _postMgr)
	{
		iter.init(w, h, arb);

		iter.createPass<BloomPass>()->setEnabled(false);
		iter.createPass<BloomPass>()->setEnabled(false);
		iter.createPass<NoiseWarpPass>()->setEnabled(false);
		iter.createPass<ZoomBlurPass>()->setEnabled(false);
		iter.createPass<KaleidoscopePass>()->setEnabled(false);
		iter.createPass<EdgePass>()->setEnabled(false);
		iter.createPass<PixelatePass>()->setEnabled(false);
		iter.createPass<RGBShiftPass>()->setEnabled(false);
		iter.createPass<ToonPass>()->setEnabled(false);

		iter.setFlip(false);
	}
	

}

//-------------------------------------
void postFilter::filterEnable(ePostFilterType type, eDisplayLayer layer)
{
	auto isEnable = !_postMgr[layer][(int)type]->getEnabled();
	_postMgr[layer][(int)type]->setEnabled(isEnable);
	
}

//-------------------------------------
void postFilter::filterEnable(ePostFilterType type, eDisplayLayer layer, bool isEnable)
{
	_postMgr[layer][(int)type]->setEnabled(isEnable);
	
}

//-------------------------------------
void postFilter::disableAll()
{
	for (auto& iter : _postMgr)
	{
		for (int i = 0; i < iter.size(); i++)
		{
			iter[i]->disable();
		}
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




