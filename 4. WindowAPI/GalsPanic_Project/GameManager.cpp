#include "GameManager.h"

void GameManager::StartGame(HDC hdc)
{
}

BOOL GameManager::PlayerMoveable()
{
	return 0;
}

void GameManager::DrawLine(HDC hdc)
{
	MoveToEx(hdc, GetBeforePos().x, GetBeforePos().y, NULL);
	LineTo(hdc, GetCurPos().x, GetCurPos().y);
}

void GameManager::PaintArea(HDC hdc, vector<vector<POINT>> & ObjectPoints)
{
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);


	for (int i = 0; i < ObjectPoints.size(); i++)
	{
		POINT point[100] = {};

		for (int j = 0; j < ObjectPoints[i].size(); j++)
		{
			point[j] = ObjectPoints[i][j];
		}

		Polygon(hdc, point, ObjectPoints[i].size());
	}

	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}

double GameManager::AreaRatio()
{
	return 0.0;
}
