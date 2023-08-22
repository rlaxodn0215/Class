#pragma once
#include<Windows.h>
#include<mmsystem.h>
#include<Digitalv.h>

#pragma comment(lib,"winmm.lib")

class Sound
{
private:
	DWORD SoundData;

	MCI_OPEN_PARMS      mciOpenParms; //파일을 로드
	MCI_PLAY_PARMS       mciPlayParms; //파일을 재생
	MCI_STATUS_PARMS   mciStatus; //파일의 상태
	UINT wDeviceID = 0;

	int m_ChanelNumber;

public:
	Sound() {};
	Sound(HWND hWnd,const TCHAR lpszWave[100], int chanelNum);
	~Sound();
	DWORD LoadMP3(HWND hWnd,const TCHAR lpszWave[100]);
	void PlayAudio();
};

