#include "CObject.h"

CObject::CObject(POINT pt)
{
	pos.x = pt.x;
	pos.y = pt.y;
	int sign1 = rand() % 2;
	int sign2 = rand() % 2;

	if (sign1)
		velocity.x = rand() % 10 + 1;
	else
		velocity.x = -rand() % 10 - 1;

	if (sign2)
		velocity.y = rand() % 10 + 1;
	else
		velocity.y = -rand() % 10 - 1;
	
}

void CObject::Update(const HWND & hWnd)
{
	pos.x += velocity.x;
	pos.y += velocity.y;
}


CCircle::CCircle(POINT pt):CObject(pt)
{
	radius = rand() % 30 + 20;
	weight = 2 * 3.141582 * radius;
	CObject::objectNum = 0;
}


CCircle::~CCircle()
{
}

void CCircle::Update(const HWND & hWnd)
{
	CObject::Update(hWnd);
	InvalidateRect(hWnd, NULL, TRUE);
}

void CCircle::Draw(const HDC & hdc)
{
	int x1 = pos.x - radius;
	int y1 = pos.y - radius;
	int x2 = pos.x + radius;
	int y2 = pos.y + radius;

	Ellipse(hdc, x1, y1, x2, y2);
}

BOOL CCircle::Collison(const RECT& recView, const vector<CObject*>& vec)
{

	//다른 물체와 충돌 했을때
	for (int i = 0; i < vec.size(); i++)
	{
		if (Length(pos, vec[i]->GetPos()) <= radius + vec[i]->GetRadius() && Length(pos, vec[i]->GetPos()) > 5)
		{
			POINT normal = { pos.x - vec[i]->GetPos().x, pos.y - vec[i]->GetPos().y }; // 호출 함수 기준
			double distance = radius + vec[i]->GetRadius() - Length(pos, vec[i]->GetPos());
			pos.x += distance * normal.x / Length(pos, vec[i]->GetPos());
			pos.y += distance * normal.y / Length(pos, vec[i]->GetPos());
			velocity.x += normal.x * (weight / (weight + vec[i]->GetWeight())) * 0.2;
			velocity.y += normal.y * (weight / (weight + vec[i]->GetWeight())) * 0.2;
			//collisonNum.push_back(i);
			return TRUE;
		}

	}

	//벽에 충돌했을 때
	if (pos.x + radius >= recView.right)
	{
		pos.x = recView.right - radius;
		velocity.x *= -1;
	}

	else if (pos.x - radius <= recView.left)
	{
		pos.x = recView.left + radius;
		velocity.x *= -1;
	}

	else if (pos.y + radius >= recView.bottom)
	{
		pos.y = recView.bottom - radius;
		velocity.y *= -1;
	}

	else if (pos.y - radius <= recView.top)
	{
		pos.y = recView.top + radius;
		velocity.y *= -1;
	}


	return FALSE;
	
}

BOOL CCircle::Merge(const RECT& recView, vector<CObject*>& vec)
{
	if (CCircle::Collison(recView, vec))
	{
		radius += vec[collisonNum[0]]->GetRadius();
		vec.erase(vec.begin()+collisonNum.front());
		//collisonNum.erase(collisonNum.begin());
	}
	return 0;
}


CRectangle::CRectangle(POINT pt) : CObject(pt)
{
	radius = rand() % 30 + 20;
	weight = 2* radius * radius;
	angle = 0;

	p[0].x = pt.x + radius;
	p[0].y= pt.y;

	p[1].x = pt.x;
	p[1].y = pt.y + radius;

	p[2].x = pt.x - radius;
	p[2].y = pt.y;

	p[3].x = pt.x;
	p[3].y = pt.y - radius;

	CObject::objectNum = 1;

	int sign = rand() % 2;

	if (sign)
		angularVelocity = (rand() % 30 + 10) *PI/180;
	else
		angularVelocity = (rand() % 30 + 10) *PI /(-180);
}

void CRectangle::Update(const HWND& hWnd) //사각형 4점 좌표 갱신
{
	CObject::Update(hWnd);
	angle += angularVelocity;

	if (angle >= 2 * PI)
	{
		angle -= 2 * PI;
	}

	for (int i = 0; i < 4; i++)
	{
		p[i].x = pos.x + cos(angle+PI*i/2) * radius;
		p[i].y = pos.y + sin(angle + PI * i / 2) * radius;
	}


	InvalidateRect(hWnd, NULL, TRUE);
}

//p[i].x = pos.x + cos(angularVelocity) * (p[i].x - pos.x) - sin(angularVelocity) * (p[i].y - pos.y);
//p[i].y = pos.y + sin(angularVelocity) * (p[i].x - pos.x) + cos(angularVelocity) * (p[i].y - pos.y);

void CRectangle::Draw(const HDC& hdc)
{
	Polygon(hdc, p, 4);
}


BOOL CRectangle::Collison(const RECT& recView, const vector<CObject*>& vec)
{

	//벽에 충돌했을 때
	int xMin=p[0].x, xMax = p[0].x, yMin = p[0].y, yMax = p[0].y;

	for (int i = 1; i < 4; i++)
	{
		xMin = (xMin < p[i].x) ? xMin : p[i].x;
		xMax = (xMax > p[i].x) ? xMax : p[i].x;
		yMin = (yMin < p[i].y) ? yMin : p[i].y;
		yMax = (yMax > p[i].y) ? yMax : p[i].y;
	}

	if (xMin <= recView.left)
	{
		pos.x = recView.left + radius;
		velocity.x *= -1;
	}

	else if (xMax >= recView.right)
	{
		pos.x = recView.right - radius;
		velocity.x *= -1;
	}

	else if (yMin <= recView.top)
	{
		pos.y = recView.top + radius;
		velocity.y *= -1;
	}

	else if (yMax >= recView.bottom)
	{
		pos.y = recView.bottom - radius;
		velocity.y *= -1;
	}

	//다른 물체와 충돌했을 때
	for (int i = 0; i < vec.size(); i++)
	{
		if (Length(pos, vec[i]->GetPos()) <= radius + vec[i]->GetRadius() + 2 && Length(pos, vec[i]->GetPos()) > 5)
		{
			POINT normal = { pos.x - vec[i]->GetPos().x, pos.y - vec[i]->GetPos().y }; // 호출 함수 기준
			velocity.x += normal.x * (weight / (weight + vec[i]->GetWeight())) * 0.1;
			velocity.y += normal.y * (weight / (weight + vec[i]->GetWeight())) * 0.1;
			//collisonNum.push_back(i);
			return TRUE;
		}

	}

	return FALSE;
}

BOOL CRectangle::Merge(const RECT& recView, vector<CObject*>& vec)
{
	if (CRectangle::Collison(recView, vec))
	{
		radius += vec[collisonNum[0]]->GetRadius();
		vec.erase(vec.begin() + collisonNum.front());
		//체크해서 나중에 삭제
		collisonNum.erase(collisonNum.begin());
	}
	return 0;

}


//for (int i = 0; i < vec.size(); i++)
//{
//	if (vec[i]->GetObjectNum() == 0)
//	{
//		CCircle* circle = (CCircle*)vec[i];
//		POINT checkPos;
//		checkPos.x = cos(PI / 4 + angle) * (circle->GetPos().x - pos.x) - sin(PI / 4 + angle) * (circle->GetPos().y - pos.y);
//		checkPos.y = sin(PI / 4 + angle) * (circle->GetPos().x - pos.x) + cos(PI / 4 + angle) * (circle->GetPos().y - pos.y);
//
//		POINT closeRec = { 0,0 };
//		closeRec.x = max((-0.707 * radius), min(0.707 * radius, closeRec.x));
//		closeRec.y = max((-0.707 * radius), min(0.707 * radius, closeRec.y));
//
//		if (Length(checkPos, closeRec) <= circle->GetRadius() + 10)
//		{
//			//원과 충돌 됨
//			POINT normal = { checkPos.x - closeRec.x, checkPos.y - closeRec.y };
//
//			velocity.x += (-normal.x) * 0.1;
//			velocity.y += (-normal.y) * 0.1;
//
//		}
//
//
//	}
//
//}

CStar::CStar(POINT pt) :CObject(pt)
{
	radius = rand() % 30 + 20;
	innerRadius = radius / 2;
	weight = 2 * radius * radius;
	angle = 0;
	CObject::objectNum = 2;

	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
		{
			p[i].x = pos.x + radius * cos(angle);
			p[i].y = pos.y + radius * sin(angle);
		}

		else
		{
			p[i].x = pos.x + innerRadius * cos(angle);
			p[i].y = pos.y + innerRadius * sin(angle);
		}

		angle += 36*PI/180;
	}


	int sign = rand() % 2;

	if (sign)
		angularVelocity = (rand() % 30 + 10) * PI / 180;
	else
		angularVelocity = (rand() % 30 + 10) * PI / (-180);
}

void CStar::Update(const HWND& hWnd)
{
	CObject::Update(hWnd);
	angle += angularVelocity;

	if (angle >= 2 * PI)
	{
		angle -= 2 * PI;
	}

	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
		{
			p[i].x = pos.x + cos(angle + 36 * PI*i / 180) * radius;
			p[i].y = pos.y + sin(angle + 36 * PI * i / 180) * radius;
		}

		else
		{
			p[i].x = pos.x + cos(angle + 36 * PI * i / 180) * innerRadius;
			p[i].y = pos.y + sin(angle + 36 * PI * i / 180) * innerRadius;
		}
	}


	InvalidateRect(hWnd, NULL, TRUE);
}

void CStar::Draw(const HDC& hdc)
{
	Polygon(hdc, p, 10);
}

BOOL CStar::Collison(const RECT& recView, const vector<CObject*>& vec)
{
	//벽에 충돌했을 때
	if (pos.x + radius >= recView.right)
	{
		pos.x = recView.right - radius;
		velocity.x *= -1;
	}

	else if (pos.x - radius <= recView.left)
	{
		pos.x = recView.left + radius;
		velocity.x *= -1;
	}

	else if (pos.y + radius >= recView.bottom)
	{
		pos.y = recView.bottom - radius;
		velocity.y *= -1;
	}

	else if (pos.y - radius <= recView.top)
	{
		pos.y = recView.top + radius;
		velocity.y *= -1;
	}

	//다른 물체와 충돌 했을때
	for (int i = 0; i < vec.size(); i++)
	{
		if (Length(pos, vec[i]->GetPos()) <= radius + vec[i]->GetRadius() + 2 && Length(pos, vec[i]->GetPos()) > 5)
		{
			POINT normal = { pos.x - vec[i]->GetPos().x, pos.y - vec[i]->GetPos().y }; // 호출 함수 기준
			velocity.x += normal.x * (weight / (weight + vec[i]->GetWeight())) * 0.1;
			velocity.y += normal.y * (weight / (weight + vec[i]->GetWeight())) * 0.1;
			//collisonNum.push_back(i);
			return TRUE;
		}

	}

	return FALSE;
}

BOOL CStar::Merge(const RECT& recView, vector<CObject*>& vec)
{
	if (CStar::Collison(recView, vec))
	{
		radius += vec[collisonNum[0]]->GetRadius();
		innerRadius+= vec[collisonNum[0]]->GetRadius()/2;
		vec.erase(vec.begin() + collisonNum.front());
		collisonNum.erase(collisonNum.begin());
	}
	return 0;
}
