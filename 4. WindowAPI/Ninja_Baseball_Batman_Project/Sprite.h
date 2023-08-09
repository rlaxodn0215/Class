#pragma once

#include"framework.h"
#include<string>
#include<memory>

using namespace std;

class Sprite
{
private:
	HBITMAP m_SpriteImage;
	BITMAP m_SpriteBit;
	COLORREF m_TransparentColor;

public:
	HBITMAP GetSpriteImage() { return m_SpriteImage; }
	BITMAP GetSpriteBit() { return m_SpriteBit; }
	COLORREF GetTransparentColor() { return m_TransparentColor; }
	void SetTransparentColor(COLORREF num) { m_TransparentColor=num; }

	Sprite();
	Sprite(const TCHAR imageName[100]);
	~Sprite() {};
};

