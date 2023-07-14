#pragma once
#include "framework.h"
#include"Player.h"

class GameManager : public Player
{
public:
	void StartGame(HDC hdc); //시작 사각형 및 플레이어 위치선정
	BOOL PlayerMoveable();
	void DrawLine(HDC hdc);
	void PaintArea(HDC hdc, vector<vector<POINT>>& ObjectPoints);
	//void AreaCollider();
	double AreaRatio();
};

