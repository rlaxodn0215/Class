#pragma once
#include "framework.h"
#include"Player.h"

class GameManager : public Player
{
public:
	void StartGame(POINT recCenter, int width, int height, Player* player, vector<POINT> & AreaPoints); //시작 사각형 및 플레이어 위치선정
	BOOL PlayerMoveable();
	void DrawLine(HDC hdc);
	void PaintArea(HDC hdc, vector<POINT>& ObjectPoints);
	BOOL AreaCollider(vector<vector<POINT>>& ObjectPoints, vector<RECT> Colliders);
	double AreaRatio(); 
};

