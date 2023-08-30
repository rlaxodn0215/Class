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

	MCI_OPEN_PARMS		 mciOpenParms;	//������ �ε�
	MCI_PLAY_PARMS       mciPlayParms;	//������ ���
	MCI_STATUS_PARMS	 mciStatus;		//������ ����
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

