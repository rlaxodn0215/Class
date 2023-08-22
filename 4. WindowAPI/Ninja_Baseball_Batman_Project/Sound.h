#pragma once
#include<Windows.h>
#include<mmsystem.h>
#include<Digitalv.h>

#pragma comment(lib,"winmm.lib")

class Sound
{
private:
	DWORD SoundData;

	MCI_OPEN_PARMS      mciOpenParms; //������ �ε�
	MCI_PLAY_PARMS       mciPlayParms; //������ ���
	MCI_STATUS_PARMS   mciStatus; //������ ����
	UINT wDeviceID = 0;

	int m_ChanelNumber;

public:
	Sound() {};
	Sound(HWND hWnd,const TCHAR lpszWave[100], int chanelNum);
	~Sound();
	DWORD LoadMP3(HWND hWnd,const TCHAR lpszWave[100]);
	void PlayAudio();
};

