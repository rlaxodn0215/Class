#include "GameManager.h"

void GameManager::StartGame(POINT recCenter, int width, int height, Player * player, vector<POINT> & AreaPoints)
{

	POINT num1 = { recCenter.x - width / 2, recCenter.y - height / 2 };
	POINT num2 = { recCenter.x + width / 2, recCenter.y - height / 2 };
	POINT num3 = { recCenter.x + width / 2, recCenter.y + height / 2 };
	POINT num4 = { recCenter.x - width / 2, recCenter.y + height / 2 };

	AreaPoints.push_back(num1);
	AreaPoints.push_back(num2);
	AreaPoints.push_back(num3);
	AreaPoints.push_back(num4);

	player->SetBeforePos(num1);
	player->SetCurPos(num1);

	//LinePoints.push_back(GetCurPos());

}

BOOL GameManager::PlayerMoveable()
{
	return 0;
}

void GameManager::DrawLine(HDC hdc)
{
	HPEN hPen, oldPen;
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
	oldPen = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, GetBeforePos().x, GetBeforePos().y, NULL);
	LineTo(hdc, GetCurPos().x, GetCurPos().y);

	SelectObject(hdc, oldPen);
	DeleteObject(hPen);
}

void GameManager::PaintArea(HDC hdc, vector<POINT> & ObjectPoints)
{
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(255, 0, 255));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	POINT point[500] = {};
	
	for (int j = 0; j < ObjectPoints.size(); j++)
	{
		point[j] = ObjectPoints[j];
	}
	
	Polygon(hdc, point, ObjectPoints.size());
	

	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}

BOOL GameManager::AreaCollider(vector<vector<POINT>>& ObjectPoints, vector<RECT> Colliders)
{
	
	

	return false;
}


double GameManager::AreaRatio()
{
	return 0.0;
}
