#pragma once
#include"framework.h"

class Camera
{
private:
	POINT m_SpriteOffset;
	int m_Width;
	int m_Height;
	POINT m_CamCenter;
	int m_CamMoveOffset;

public:
	Camera();
	Camera(POINT spriteOffset, int width, int height, POINT camCenter, int camOffset);
	~Camera();

	void CameraMove();
};

