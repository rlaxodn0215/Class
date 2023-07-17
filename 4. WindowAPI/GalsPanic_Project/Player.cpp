#include "Player.h"

int Player::GetWay() const
{
	if (up)
	{
		return 12;
	}

	else if(down)
	{
		return 6;
	}

	else if (left)
	{
		return 9;
	}

	else
	{
		return 3;
	}
}

void Player::SetWay(int w)
{
	if (w==12)
	{
		up = true;
		down = false;
		left = false;
		right = false;
	}

	else if (w == 6)
	{
		up = false;
		down = true;
		left = false;
		right = false;
	}

	else if (w == 9)
	{
		up = false;
		down = false;
		left = true;;
		right = false;
	}

	else
	{
		up = false;
		down = false;
		left = false;
		right = true;
	}
}

Player::Player()
{
	curPos = { 0,0 };
	beforePos = { 0,0 };
	life = 3;
	up = false;
	down = false;
	left = false;
	right = false;
}


Player::~Player()
{
}

void Player::PlayerPosUpdate()
{
	beforePos = curPos;
}

void Player::PlayerCharactorUpdate(HDC hdc)
{
	int radius = 5;
	int x1 = curPos.x - radius;
	int y1 = curPos.y - radius;
	int x2 = curPos.x + radius;
	int y2 = curPos.y + radius;

	Ellipse(hdc,x1, y1, x2, y2);
}
