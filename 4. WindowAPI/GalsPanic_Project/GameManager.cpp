#include "GameManager.h"

void GameManager::StartGame(POINT recCenter, int width, int height, Player * player, vector<vector<POINT>>& ObjectPoints, vector<POINT> & LinePoints)
{

	POINT num1 = { recCenter.x - width / 2, recCenter.y - height / 2 };
	POINT num2 = { recCenter.x + width / 2, recCenter.y - height / 2 };
	POINT num3 = { recCenter.x + width / 2, recCenter.y + height / 2 };
	POINT num4 = { recCenter.x - width / 2, recCenter.y + height / 2 };


	vector<POINT> firstPoint = { num1,num2,num3,num4 };

	ObjectPoints.push_back(firstPoint);

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

void GameManager::PaintArea(HDC hdc, vector<vector<POINT>> & ObjectPoints)
{
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(255, 0, 255));
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

BOOL GameManager::AreaCollider(vector<vector<POINT>>& ObjectPoints, vector<RECT> Colliders)
{
	
	

	return false;
}


double GameManager::AreaRatio()
{
	return 0.0;
}
