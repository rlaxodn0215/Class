#pragma once

#include"framework.h"
#include"Vector3.h"
#include<string>
#include<memory>

using namespace std;

class Sprite
{
private:
	HBITMAP m_SpriteImage;
	BITMAP m_SpriteBit;
	Vector3 m_TransparentRGB = {-1, -1, -1};

public:
	HBITMAP GetSpriteImage() { return m_SpriteImage; }
	BITMAP GetSpriteBit() { return m_SpriteBit; }
	Vector3 GetTransparentColor() { return m_TransparentRGB; }
	void SetTransparentColor(Vector3 num) { m_TransparentRGB =num; }

	Sprite();
	Sprite(const TCHAR imageName[100]);
	~Sprite() {};
};

