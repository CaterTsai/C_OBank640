#ifndef HD512DLL_H
#define HD512DLL_H

namespace HD512
{
#define Decl extern  "C"  __declspec(dllimport)

#pragma comment (lib, "HD512DLL.lib")   //Add LIB

	//===========================================================================

	//-------------------------------------------------------------
	// ShowAbout and Version
	//-------------------------------------------------------------
	Decl void ShowAbout();


	//-------------------------------------------------------------------------
	//  Check DMX Dongle
	//  True have Dongle
	//  HD512 box push to PC, will auto open ,so in your programm, don't call this function, only for check.  
	//-------------------------------------------------------------------------
	Decl bool isDMXOpen();


	//-----------------------------------------------------------------------------------------
	//  Close Dongle
	//-----------------------------------------------------------------------------------------
	Decl void DMXClose();


	//---------Send Single Channel Value to Dongle---------------------------
	//              Channel(1бл512)
	//              Value(0бл255)
	//----------------------------------------------------------------------
	Decl bool DMXSend(long Channel, unsigned char Value);


	//---------------------------Bulk send----------------------------------------------------
	//            ChannelCount(1~512)
	//            ChannelIndex(1~512) First Channel Value
	//            Value=buff datas
	//            DMXSends(512,1,buff); //Send All 512 channels data to HD512 (data in buff)
	//-------------------------------------------------------------------------------------------
	Decl bool DMXSends(long ChannelCount, long ChannelIndex, unsigned char* Value);


	//---------Other way Send Single Channel Value to Dongle---------------------------
	//              Channel(1бл512)
	//              Value(0бл255)
	//----------------------------------------------------------------------
	Decl bool DMXSendSingleChannel(long Channel, unsigned char Value);


	//---------------------------can send DMX data to 0~3 universe ID box------------------------------
	//            Value=buff[512] datas
	//            Box = 0~3  universe ID
	//            DMXSendBox(2,buff); //Send All 512 channels data to universe2[box3] HD512 box (data in buff)
	//        new for HD512 box, in your programm, only call this function then will ok
	//--------------------------------------------------------------------------------------------------
	Decl bool DMXSendBox(long Box, unsigned char* Value);



	//--------------------------------------Change Box Number----------------------------------------------------------
	//when want 1~4 box combinations work 1024~2048 channels, must changer box number, one box don't use this function,
	//            Box = 0~3  box number 
	//            ChangeBoxNumber(1); //have two box make 1024 channels.
	//-----------------------------------------------------------------------------------------------------------------
	Decl bool ChangeBoxNumber(long Box);



	//-----------------------Get Box Number-----------------------------------------------
	//                       Get box number
	//------------------------------------------------------------------------------------
	Decl int  GetBoxNumber();


	//-----------------------Get Box Universe ID------------------------------------------
	//                  only for one box, Get Box Universe ID
	//------------------------------------------------------------------------------------
	Decl char GetBoxUniverseID();


	//-----------------------Get Box Refresh Rate------------------------------------------
	//                       only for one box
	//-------------------------------------------------------------------------------------
	Decl int  GetBoxRefreshRate();


	//-----------------------Set Box Refresh Rate------------------------------------------
	//                         only for one box
	//                        DlyTime = 1000 / Rate , 22ms = 1000 / 44Hz
	//-------------------------------------------------------------------------------------
	Decl bool SetBoxRefreshRate(int DlyTime);

	//===========================================================================



	//================================== For examlpe =========================================
	/*

	//HD512 box push to PC, will auto open, so only call DMXSendBox() function then will ok ;

	//examlpe 1
	//For examlpe you need two box work 1024 channels:
	unsigned char U0_DMXData[512], U1_DMXData[512];  //save two box data, each is 512 channels
	ChangeBoxNumber(1);        // First to Change box number,0 is 1 box, 1 is two box, 2 is three box, 3 is four box,if only one box you needn't to call this function,default is one box.
	DMXSendBox(0,U0_DMXData); //Send 512 byte(channels) DMX data to box 1 (universe0)
	DMXSendBox(1,U1_DMXData); //Send 512 byte(channels) DMX data to box 2 (universe1)


	//examlpe 2
	//one box work 512 channels, only call DMXSendBox() function then will ok:
	unsigned char U0_DMXData[512];  //save one box data,U0_DMXData[512] is 512 channels data
	DMXSendBox(0,U0_DMXData);       //Send 512 byte(channels) DMX data to box 1

	*/
}


#endif


