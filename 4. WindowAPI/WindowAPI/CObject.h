#pragma once

#include "WindowAPI.h"
#include "framework.h"
#include<time.h>
#include<vector>
#include<queue>
#include<cmath>
#define PI (3.1415926535) 

using namespace std;

static queue<int> collisonNum;

struct Vector
{
	double x;
	double y;
};

class CObject
{
protected:
	Vector pos;
	Vector velocity;
	double weight;
	int radius;
	int objectNum; //0:원, 1:사각형, 2: 별
public:
	Vector GetPos() { return pos; }
	void SetPos(Vector p) { pos.x = p.x; pos.y = p.y; }
	Vector GetVelocity() { return velocity; }
	void SetVel(Vector v) { velocity.x = v.x; velocity.y = v.y; }
	double GetWeight() { return weight; }
	int GetObjectNum() { return objectNum; }
	int GetRadius() { return radius; }
	CObject(POINT pt);
	virtual void Update();//다음 위치, 각도로 변환(충돌 X)
	virtual void Draw(const HDC& hdc) = 0;
	virtual BOOL Collison(const RECT & recView,const vector<CObject*> & vec)=0;
	virtual BOOL Merge(const RECT& recView, vector<CObject*> & vec)=0;

	double Length(const Vector a, const Vector b) { return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }
};

class CCircle : public CObject
{
protected:
public:
	CCircle(POINT pt); //마우스 좌표값을 받는다.
	~CCircle();
	void Update();
	void Draw(const HDC & hdc) override;
	BOOL Collison(const RECT &  recView, const vector<CObject*> & vec) override;
	BOOL Merge(const RECT& recView, vector<CObject*>& vec) override;
};

class CRectangle : public CObject
{
protected:
	Vector p[4];
	double angle;
	double angularVelocity;

public:
	int GetRadius() { return radius; }
	double GetAng() { return angle; }
	double GetAngVel() { return angularVelocity; }
	Vector& GetRECT() { return *p; }

	CRectangle(POINT pt);
	void Update() override;
	void Draw(const HDC& hdc) override;
	BOOL Collison(const RECT& recView, const vector<CObject*>& vec) override;
	BOOL Merge(const RECT& recView, vector<CObject*>& vec) override;
};

class CStar : public CObject
{
protected:
	Vector p[10];
	int innerRadius;
	double angle;
	double angularVelocity;

public:
	CStar(POINT pt);
	void Update() override;
	void Draw(const HDC& hdc) override;
	BOOL Collison(const RECT& recView, const vector<CObject*>& vec) override;
	BOOL Merge(const RECT& recView, vector<CObject*>& vec) override;
};
