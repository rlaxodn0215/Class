#pragma once
#include"framework.h"
#include<Windows.h>
#include<mmsystem.h>
#include<Digitalv.h>
#include<iostream>

#pragma comment(lib,"winmm.lib")

class Sound
{
private:
	DWORD SoundData;

	MCI_OPEN_PARMS		 mciOpenParms;	//파일을 로드
	MCI_PLAY_PARMS       mciPlayParms;	//파일을 재생
	MCI_STATUS_PARMS	 mciStatus;		//파일의 상태
	UINT wDeviceID = 0;

	int m_ChanelNumber;

	int m_Timer = 0;

public:
	Sound() {};
	Sound(HWND hWnd,const TCHAR lpszWave[100], int channel);
	~Sound();
	DWORD LoadWAV(HWND hWnd,const TCHAR lpszWave[100]);

	MCI_PLAY_PARMS GetMciPlayParms() { return mciPlayParms; }
	MCI_STATUS_PARMS GetMciStatus() { return mciStatus; }

	void PlayAudio();
	void ResetAudio();
	void LoopAudio(int timer);
};

