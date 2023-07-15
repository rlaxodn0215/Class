#pragma once
#include "framework.h"
#include"Player.h"

class GameManager : public Player
{
public:
	void StartGame(HDC hdc); //���� �簢�� �� �÷��̾� ��ġ����
	BOOL PlayerMoveable();
	void DrawLine(HDC hdc);
	void PaintArea(HDC hdc, vector<vector<POINT>>& ObjectPoints);
	BOOL AreaCollider(vector<vector<POINT>>& ObjectPoints); // divided into rectangle and integrel + == �� ���Ѵ�. (����ؼ� �ڵ� ����)
	BOOL RectangleCollider();
	double AreaRatio();
};

