#pragma once
#include"framework.h"

class Camera
{
private:
	RECT m_SceneArea; //sprite ±‚¡ÿ
	POINT m_CamCenter;
	int m_CamMoveOffset;

public:
	Camera();
	Camera(RECT sceneArea, int camOffset);
	~Camera();

	void CameraMove(POINT endpoint);
};

