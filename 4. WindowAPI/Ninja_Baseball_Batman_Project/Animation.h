#pragma once
#include"Sprite.h"
#include<vector>

using namespace std;

class Animation
{
private:
	vector<Sprite> m_Sprites;
	int m_FrameCurCount;
	int m_FrameTotalCount;

public:
	int GetFrameCurCount() { return m_FrameCurCount; }
	void SetFrameCurCount(int num) { m_FrameCurCount = num; }
	int GetFrameTotalCount() { return m_FrameTotalCount; }
	
	Animation();
	Animation(const TCHAR imageName[100], const TCHAR textFileName[100]);
	~Animation();
	void AniPlay(HWND hWnd, HDC hdc, POINT location, int spriteIndex, float imageRatio, int timerDefine, int delayTime, TIMERPROC func);
};

