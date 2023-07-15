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
	HPEN hPen, oldPen;
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	oldPen = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, GetBeforePos().x, GetBeforePos().y, NULL);
	LineTo(hdc, GetCurPos().x, GetCurPos().y);

	SelectObject(hdc, oldPen);
	DeleteObject(hPen);
}

void GameManager::PaintArea(HDC hdc, vector<vector<POINT>> & ObjectPoints)
{
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(0, 0, 255));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);


	for (int i = 0; i < ObjectPoints.size(); i++)
	{
		POINT point[500] = {};

		for (int j = 0; j < ObjectPoints[i].size(); j++)
		{
			point[j] = ObjectPoints[i][j];
		}

		Polygon(hdc, point, ObjectPoints[i].size());
	}

	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}

BOOL GameManager::AreaCollider(vector<vector<POINT>>& ObjectPoints)
{
	return false;
}

BOOL GameManager::RectangleCollider()
{
	return 0;
}

double GameManager::AreaRatio()
{
	return 0.0;
}
