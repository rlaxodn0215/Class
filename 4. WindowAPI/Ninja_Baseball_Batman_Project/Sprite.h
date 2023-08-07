#pragma once

#include"framework.h"
#include<memory>
#include<string>

using namespace std;

class Sprite
{
private:
	HBITMAP m_AniImage;
	BITMAP m_AniBit;
	POINT m_Offset;
	POINT m_Pivot;
	int m_Width;
	int m_Height;
	COLORREF m_TransparentColor;

public:
	HBITMAP GetAniImage() { return m_AniImage; }
	BITMAP GetAniBit() { return m_AniBit; }
	POINT GetOffset() { return m_Offset; }
	POINT GetPivot() { return m_Pivot; }
	int GetWidth() { return m_Width; }
	int GetHeight() { return m_Height; }
	COLORREF GetTransparentColor() { return m_TransparentColor; }

	Sprite();
	Sprite(const TCHAR filename[100],const TCHAR dataname[100], int & readIndexNum);
	~Sprite() {};
	
	void ShowSprite(HDC hdc, POINT location);

};

