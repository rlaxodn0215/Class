#pragma once
#include"framework.h"
class BoxCollider
{
private:
	POINT m_Center;
	int m_Width;
	int m_Height;

public:
	BoxCollider();
	BoxCollider(POINT pivot, int width, int height);
	~BoxCollider();

	BOOL OnTriggerEnter();
	BOOL OnTriggerStay();
	BOOL OnTriggerExit();

	BOOL OnCollisionEnter();
	BOOL OnCollisionStay();
	BOOL OnCollisionExit();
};

