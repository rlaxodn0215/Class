#include "Collider.h"

CircleCollider::CircleCollider()
{
	m_type = CIRCLE;
	m_Center = { 0,0 };
	m_Radius = 0;
}

CircleCollider::CircleCollider(POINT center, int radius)
{
	m_type = CIRCLE;
	m_Center = center;
	m_Radius = radius;
}

BOOL CircleCollider::OnTrigger(Collider& other, int zOffsetDelta)
{
	Collider* base = &other;

	if (m_PosZ <= base->GetPosZ() + zOffsetDelta && m_PosZ >= base->GetPosZ() - zOffsetDelta)
	{
		if (other.GetType() == CIRCLE)
		{
			CircleCollider* circleOther = (CircleCollider*)base;
			int sumRadius = m_Radius + circleOther->m_Radius;
			int distance = (m_Center.x - circleOther->m_Center.x) * (m_Center.x - circleOther->m_Center.x)
				+ (m_Center.y - circleOther->m_Center.y) * (m_Center.y - circleOther->m_Center.y);

			if (sumRadius * sumRadius >= distance) return TRUE;
			else return FALSE;

		}

		else if (other.GetType() == BOX)
		{
			BoxCollider* boxOther = (BoxCollider*)base;
			int nearX = Clamp(m_Center.x, boxOther->GetArea().left, boxOther->GetArea().right);
			int nearY = Clamp(m_Center.y, boxOther->GetArea().top, boxOther->GetArea().bottom);

			int distance = (m_Center.x - nearX) * (m_Center.x - nearX) + (m_Center.y - nearY) * (m_Center.y - nearY);

			if (m_Radius * m_Radius >= distance) return TRUE;
			else return FALSE;
		}

		else
			return FALSE;
	}

	else
		return FALSE;
}

BOOL CircleCollider::OnCollision(Collider& other, int zOffsetDelta)
{
	Collider* base = &other;

	if (m_PosZ <= base->GetPosZ() + zOffsetDelta && m_PosZ >= base->GetPosZ() - zOffsetDelta)
	{
		if (other.GetType() == CIRCLE)
		{
			CircleCollider* circleOther = (CircleCollider*)base;
			int sumRadius = m_Radius + circleOther->m_Radius;
			int distance = (m_Center.x - circleOther->m_Center.x) * (m_Center.x - circleOther->m_Center.x)
				+ (m_Center.y - circleOther->m_Center.y) * (m_Center.y - circleOther->m_Center.y);

			if (sumRadius * sumRadius >= distance) //캐릭터의 위치를 collider위치에 맞춘다
			{
				POINT way = { m_Center.x - circleOther->m_Center.x , m_Center.y - circleOther->m_Center.y };

				double xGo = way.x * ((sumRadius - sqrt(distance)) / sqrt(distance));
				double yGo = way.y * ((sumRadius - sqrt(distance)) / sqrt(distance));

				m_Center.x += xGo;
				m_Center.y += yGo;

				return TRUE;
			}
			else
				return FALSE;

		}

		else if (other.GetType() == BOX)
		{
			BoxCollider* boxOther = (BoxCollider*)base;
			int nearX = Clamp(m_Center.x, boxOther->GetArea().left, boxOther->GetArea().right);
			int nearY = Clamp(m_Center.y, boxOther->GetArea().top, boxOther->GetArea().bottom);

			int distance = (m_Center.x - nearX) * (m_Center.x - nearX) + (m_Center.y - nearY) * (m_Center.y - nearY);

			if (m_Radius * m_Radius >= distance)
			{
				POINT way = { m_Center.x - nearX , m_Center.y - nearY };

				double xGo = way.x * (m_Radius - sqrt(distance)) /sqrt(distance);
				double yGo = way.y * (m_Radius - sqrt(distance)) / sqrt(distance);

				m_Center.x += xGo;
				m_Center.y += yGo;

				return TRUE;
			}
			else
				return FALSE;
		}
	}

	else
		return FALSE;
}

void CircleCollider::ShowCollider(HDC hdc)
{
	HPEN hPen, oldPen;
	HBRUSH hBrush, hOldBrush;
	hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	oldPen = (HPEN)SelectObject(hdc, hPen);
	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	Ellipse(hdc, m_Center.x - m_Radius, m_Center.y - m_Radius, m_Center.x + m_Radius, m_Center.y + m_Radius);

	SelectObject(hdc, oldPen);
	DeleteObject(hPen);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
}

BoxCollider::BoxCollider()
{
	m_type = BOX;
	m_Area = { 0,0,0,0 };
}

BoxCollider::BoxCollider(RECT area)
{
	m_type = BOX;
	m_Area = area;
}

BOOL BoxCollider::OnTrigger(Collider& other, int zOffsetDelta)
{
	Collider* base = &other;

	if (m_PosZ <= base->GetPosZ() + zOffsetDelta && m_PosZ >= base->GetPosZ() - zOffsetDelta)
	{
		if (other.GetType() == CIRCLE)
		{
			CircleCollider* circleOther = (CircleCollider*)base;

			int nearX = Clamp(circleOther->GetCenter().x, m_Area.left, m_Area.right);
			int nearY = Clamp(circleOther->GetCenter().y, m_Area.top, m_Area.bottom);

			int distance = (circleOther->GetCenter().x - nearX) * (circleOther->GetCenter().x - nearX)
							+ (circleOther->GetCenter().y - nearY) * (circleOther->GetCenter().y - nearY);

			if (circleOther->GetRadius() * circleOther->GetRadius() >= distance) return TRUE;
			else return FALSE;


		}

		else if (other.GetType() == BOX) //AABB
		{
			BoxCollider* boxOther = (BoxCollider*)base;

			BOOL xAxis = FALSE;
			BOOL yAxis = FALSE;

			if (m_Area.left <= boxOther->GetArea().left)
			{                   
				if (m_Area.right >= boxOther->GetArea().left) xAxis = TRUE;
				else xAxis = FALSE;
			}

			else
			{
				if (m_Area.left <= boxOther->GetArea().right) xAxis = TRUE;
				else xAxis = FALSE;
			}

			if (m_Area.top <= boxOther->GetArea().top)
			{
				if (m_Area.bottom >= boxOther->GetArea().top) yAxis = TRUE;
				else yAxis = FALSE;
			}

			else
			{
				if (m_Area.top <= boxOther->GetArea().bottom) yAxis = TRUE;
				else yAxis = FALSE;
			}

			return (xAxis && yAxis);

		}

		else
			return FALSE;
	}

	else
		return FALSE;
}

BOOL BoxCollider::OnCollision(Collider& other, int zOffsetDelta)
{
	Collider* base = &other;

	if (m_PosZ <= base->GetPosZ() + zOffsetDelta && m_PosZ >= base->GetPosZ() - zOffsetDelta)
	{
		if (other.GetType() == CIRCLE)
		{
			CircleCollider* circleOther = (CircleCollider*)base;

			int nearX = Clamp(circleOther->GetCenter().x, m_Area.left, m_Area.right);
			int nearY = Clamp(circleOther->GetCenter().y, m_Area.top, m_Area.bottom);

			int distance = (circleOther->GetCenter().x - nearX) * (circleOther->GetCenter().x - nearX)
				+ (circleOther->GetCenter().y - nearY) * (circleOther->GetCenter().y - nearY);

			if (circleOther->GetRadius() * circleOther->GetRadius() >= distance)
			{
				POINT way = { nearX -  circleOther->GetCenter().x , nearY - circleOther->GetCenter().y };

				double xGo = way.x * (circleOther->GetRadius() - sqrt(distance)) / sqrt(distance);
				double yGo = way.y * (circleOther->GetRadius() - sqrt(distance)) / sqrt(distance);

				m_Area.left += xGo;
				m_Area.top += yGo;
				m_Area.right += xGo;
				m_Area.bottom += yGo;

				return TRUE;
			}
			else
				return FALSE;


		}

		else if (other.GetType() == BOX) //AABB
		{
			BoxCollider* boxOther = (BoxCollider*)base;

			BOOL xAxis = FALSE;
			BOOL yAxis = FALSE;
			int xDiff = 0;
			int yDiff = 0;

			if (m_Area.left <= boxOther->GetArea().left)
			{
				if (m_Area.right >= boxOther->GetArea().left)
				{
					xDiff = boxOther->GetArea().left - m_Area.right;
					if (xDiff > (boxOther->GetArea().right - boxOther->GetArea().left)) xDiff = 0;
					xAxis = TRUE;
				}
				else xAxis = FALSE;
			}

			else
			{
				if (m_Area.left <= boxOther->GetArea().right)
				{
					xDiff = boxOther->GetArea().right - m_Area.left;
					if (xDiff > (boxOther->GetArea().right - boxOther->GetArea().left)) xDiff = 0;
					xAxis = TRUE;
				}
				else xAxis = FALSE;
			}

			if (m_Area.top <= boxOther->GetArea().top)
			{
				if (m_Area.bottom >= boxOther->GetArea().top)
				{
					yDiff = boxOther->GetArea().top - m_Area.bottom;
					if (yDiff > boxOther->GetArea().bottom - boxOther->GetArea().top) yDiff = 0;
					yAxis = TRUE;
				}
				else yAxis = FALSE;
			}

			else
			{
				if (m_Area.top <= boxOther->GetArea().bottom)
				{
					yDiff = boxOther->GetArea().bottom - m_Area.top;
					if(yDiff > boxOther->GetArea().bottom - boxOther->GetArea().top) yDiff = 0;
					yAxis = TRUE;
				}
				else yAxis = FALSE;
			}

			if (xAxis && yAxis)
			{
				m_Area.left += xDiff;
				m_Area.top += yDiff;
				m_Area.right += xDiff;
				m_Area.bottom += yDiff;
			}

			return (xAxis && yAxis);

		}

		else
			return FALSE;
	}

	else
		return FALSE;
}

void BoxCollider::ShowCollider(HDC hdc)
{
	HPEN hPen, oldPen;
	HBRUSH hBrush, hOldBrush;
	hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	oldPen = (HPEN)SelectObject(hdc, hPen);
	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	Rectangle(hdc, m_Area.left, m_Area.top, m_Area.right, m_Area.bottom);

	SelectObject(hdc, oldPen);
	DeleteObject(hPen);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
}
