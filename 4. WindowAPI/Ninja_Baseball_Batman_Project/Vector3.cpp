#include"Vector3.h"

Vector3::Vector3()
{
	m_X = m_Y = m_Z = 0;
}

Vector3::Vector3(int x, int y, int z)
{
	m_X = x;
	m_Y = y;
	m_Z = z;
}

Vector3::~Vector3()
{
}