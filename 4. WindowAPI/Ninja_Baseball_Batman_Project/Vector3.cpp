#include"Vector3.h"

Vector3::Vector3()
{
	m_Pos_X = m_Pos_Y = m_Pos_Z = 0;
}

Vector3::Vector3(int x, int y, int z)
{
	m_Pos_X = x;
	m_Pos_Y = y;
	m_Pos_Z = z;
}

Vector3::~Vector3()
{
}