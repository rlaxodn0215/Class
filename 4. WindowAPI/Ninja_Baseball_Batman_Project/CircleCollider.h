#pragma once
#include"framework.h"

class CircleCollider
{
private:
	POINT m_Center;
	int m_Radius;

public:
	CircleCollider();
	CircleCollider(POINT pivot, int width, int height);
	~CircleCollider();

	BOOL OnTriggerEnter();
	BOOL OnTriggerStay();
	BOOL OnTriggerExit();

	BOOL OnCollisionEnter();
	BOOL OnCollisionStay();
	BOOL OnCollisionExit();
};

