#pragma once
#include "BrickCrash.h"
#include "framework.h"
#include<iostream>
#include<time.h>
#include<vector>
#include<cmath>

#define PI (3.1415926535) 

using namespace std;

enum TAG		{ PLAYER, BALL, BLOCK, ITEM };
//enum ITEM_TYPE	{ ADD_LENGHT, DECREASE_LENGTH, ADD_BALL };
enum COLOR		{ RED, ORANGE, YELLOW, GREEN, BLUE };

struct Vector
{
	double x;
	double y;
};


class Object
{
protected:
	Vector position;
	Vector velocity;
	TAG tag;
public:
	Vector GetPos()const { return position; } 
	void SetPos(Vector vec) { position = vec; }
	Vector GetVel()const { return velocity; }
	void SetVel(Vector vec) { velocity = vec; }

	Object();
	//virtual ~Object();
	Object(Vector & p, Vector & v);

	virtual void Update();
	virtual void Draw(HDC hdc) {};
	virtual void BallActive(const vector<Object*>& blocks, const Vector& vel) {};
	virtual BOOL Collison(const RECT& recView, Object* player, const vector<Object*>& blocks) { return FALSE; }

	double Length(const Vector & a, const Vector & b)
	{ return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }

};

class Ball :Object
{
protected:
	int radius;
	int hideBlockNum;
	BOOL isAble;

public:
	int GetRad()const { return radius; }
	void SetRad(int r) { radius = r; }
	BOOL GetEnable()const { return isAble; }

	Ball();
	Ball(Vector & p, Vector & v, int r, int hideLo);

	void Update() override;
	void Draw(HDC hdc)override;
	void BallActive(const vector<Object*>& blocks, const Vector& vel) override;
	BOOL Collison(const RECT& recView, Object* player, const vector<Object*>& blocks)override;

};

class Block :Object
{
protected:
	int width;
	int height;
	int Hp;
	BOOL dead;
	COLOR col;
public:
	int GetWidth()const { return width; }
	void SetWidth(int w) { width = w; }
	int GetHeight()const { return height; }
	void SetHeight(int h) { height = h; }
	BOOL GetDead() const { return dead; }
	int GetHp()const { return Hp; }
	void SetHp(int hp) { Hp = hp; }

	Block();
	Block(Vector & p, Vector & v, int w, int h, int hp);

	void Update() override;
	void Draw(HDC hdc)override;
	BOOL BlockDead();
	BOOL Collison(const vector<Object*> & balls);
};

class Player : Object
{
protected:
	int width;
	int height;
	int points;
	string playerName;
public:
	string GetName()const { return playerName; }
	void SetName(string name) { playerName = name; }
	int GetPoint()const { return points; }
	void SetPoint(int p) { points = p; }
	int GetWidth() { return width; }
	void SetWidth(int w) { width = w; }
	int GetHeight() { return height; }
	void SetHeight(int h) { height = h; }

	Player();
	Player(Vector & p, Vector & v, int w,int h, string name, int point);

	void Update() override;
	void Draw(HDC hdc)override;
	BOOL Collison(const RECT& recView, const vector<Object*>& balls);

};

//class Item :Object
//{
//protected:
//	ITEM_TYPE IT;
//public:
//	Item();
//	Item(Vector & p, Vector & v, ITEM_TYPE it);
//
//	void Update() override;
//	void Draw(HDC hdc)override;
//	BOOL Collison(const RECT& recView, const Object * player);
//};

