#pragma once
#include"Sprite.h"
#include<vector>

using namespace std;

class Animation
{
private:
	vector<Sprite> m_Sprites;
	int m_FrameNum;

public:
	Animation();
	Animation(const TCHAR imageName[100], const TCHAR textFileName[100]);
	~Animation();
	void AniPlay(HWND hWnd, HDC hdc, POINT location, int spriteIndex);
};

