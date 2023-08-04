#pragma once
#include"framework.h"
#include"Animation.h"
class UI
{
private:

	Animation m_UISprite;
	POINT m_ShowOffset;

public:
	UI();
	UI(Animation& sprite, POINT offset);
	~UI();

	void ShowUI();
};

