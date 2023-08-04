#pragma once

#include"framework.h"

class Animation
{
private:
	TCHAR m_FileName[100];
	TCHAR m_AniName[50];
	POINT m_Offset;
	POINT m_Pivot;
	int m_Width;
	int m_Height;
	int m_FrameCount;
	int m_FrameSpeed;

public:
	Animation();
	Animation(TCHAR filename[], TCHAR m_AniName[], POINT offset,
		POINT pivot, int width, int height, int frameCount, int frameSpeed);
	~Animation() {};

	void SetFrameSpeed(int frameSpeed) { m_FrameSpeed = frameSpeed; }
	
	void ShowSprite();

	void StartAni();
	void StopAni();
	void ChangeAni(TCHAR beforeAniName[], TCHAR afterAniName[]);
	void GotoFrame(int frameNum);

};

