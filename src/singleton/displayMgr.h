#pragma once


class displayMgr
{
public:
	displayMgr();

private:
	bool _isSetup;
	int _ctrlID;

//-------------------
//Singleton
//-------------------
public:
	static displayMgr* GetInstance();
	static void Destroy();

private:
	static displayMgr *pInstance;
};