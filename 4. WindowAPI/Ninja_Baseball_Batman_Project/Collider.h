#pragma once
#include"framework.h"
class Collider
{
private:
	POINT m_Center;
	int m_Width;
	int m_Height;

public:
	Collider();
	Collider(POINT pivot, int width, int height);
	~Collider();

	BOOL OnTriggerEnter();
	BOOL OnTriggerStay();
	BOOL OnTriggerExit();

	BOOL OnCollisionEnter();
	BOOL OnCollisionStay();
	BOOL OnCollisionExit();

	void ShowCollider();
};

