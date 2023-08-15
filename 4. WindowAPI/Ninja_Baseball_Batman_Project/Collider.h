#pragma once
#include"framework.h"
#include<math.h>
#define Clamp(value, minNum, maxNum) min(maxNum, max(value, minNum))

enum TYPE { NONE, CIRCLE, BOX };

class Collider
{
protected:
	TYPE m_type;
	int m_PosZ;

	Collider() { m_type = NONE; m_PosZ = 0; };
	virtual ~Collider() {};

	virtual BOOL OnTrigger(Collider& other, int zOffsetDelta)=0;
	virtual BOOL OnCollision(Collider& other, int zOffsetDelta)=0;

	virtual void ShowCollider(HDC hdc)=0;

public:
	TYPE GetType() { return m_type; }
	int GetPosZ() { return m_PosZ; }
	void SetPosZ(int p) { m_PosZ = p; }
};

class CircleCollider :public Collider
{
private:
	POINT m_Center;
	int m_Radius;

public:
	POINT GetCenter() { return m_Center; }
	void SetCenter(POINT center) { m_Center = center; }
	int GetRadius() { return m_Radius; }
	void SetRadius(int r) { m_Radius = r; }

	CircleCollider();
	CircleCollider(POINT center, int radius);
	~CircleCollider() {};

	BOOL OnTrigger(Collider & other, int zOffsetDelta) override;
	BOOL OnCollision(Collider& other, int zOffsetDelta) override;;

	void ShowCollider(HDC hdc) override;
};

class BoxCollider :public Collider
{
private:
	RECT m_Area;

public:
	RECT GetArea() { return m_Area; }
	void SetArea(RECT area) { m_Area = area; }

	BoxCollider();
	BoxCollider(RECT area);
	~BoxCollider() {};

	BOOL OnTrigger(Collider& other, int zOffsetDelta) override;
	BOOL OnCollision(Collider& other, int zOffsetDelta) override;

	void ShowCollider(HDC hdc) override;
};

