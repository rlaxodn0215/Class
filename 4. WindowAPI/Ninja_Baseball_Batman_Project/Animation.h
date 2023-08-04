#pragma once

#include"framework.h"

using namespace std;

class Animation
{
private:
	string m_FileName[100];
	POINT m_Offset;
	POINT m_Pivot;
	int m_Width;
	int m_Height;
	int m_FrameCount;
	int m_FrameSpeed;

public:
	Animation();
	Animation(string filename, POINT offset, POINT pivot, 
		int width, int height, int frameCount, int frameSpeed);
	~Animation() {};

	void SetFrameSpeed(int frameSpeed) { m_FrameSpeed = frameSpeed; }
	
	void ShowSprite();

	void StartAni();
	void StopAni();
	void GotoFrame(int frameNum);

};

