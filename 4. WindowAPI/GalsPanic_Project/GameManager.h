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
	BOOL AreaCollider(vector<vector<POINT>>& ObjectPoints); // divided into rectangle and integrel + == 는 안한다. (고려해서 코드 수정)
	BOOL RectangleCollider();
	double AreaRatio();
};

