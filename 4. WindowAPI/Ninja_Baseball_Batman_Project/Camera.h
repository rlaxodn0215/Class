#pragma once
#include"framework.h"
#include"Charactor.h"

class Camera
{
private:
	POINT m_CamOffset; //Sprite 
	RECT m_winRect;
public:
	Camera();
	Camera(shared_ptr<Player> player, RECT winRect);

	void CameraMove(POINT endpoint);
	void ShowCameraCenter();
};

