#include "Sound.h"

Sound::Sound(HWND hWnd,const TCHAR lpszWave[100], int chanelNum)
{
    SoundData = LoadMP3(hWnd, lpszWave);
    m_ChanelNumber = chanelNum;
}

Sound::~Sound()
{
    if (wDeviceID > 0)
    {
        mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
    }
}

DWORD Sound::LoadMP3(HWND hWnd,const TCHAR lpszWave[100])
{
    DWORD Result;
    //WaveAudio 대신 MPEGVideo를 사용하면 mp3 형식을 재생합니다.
    mciOpenParms.lpstrDeviceType = L"WaveAudio"; //MPEGVideo
    mciOpenParms.lpstrElementName = lpszWave;
    Result = mciSendCommand(wDeviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpenParms);
    if (Result)
        return Result;
    wDeviceID = mciOpenParms.wDeviceID;
    mciPlayParms.dwCallback = (DWORD)hWnd;
    if (Result)
        return Result;
    return 0;
}

void Sound::PlayAudio()
{
    SoundData = mciSendCommand(m_ChanelNumber, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayParms);
}

void Sound::ResetAudio()
{
    SoundData = mciSendCommand(m_ChanelNumber, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
}
