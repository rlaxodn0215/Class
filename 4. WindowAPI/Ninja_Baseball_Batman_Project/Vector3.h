#pragma once
#include<iostream>

class Vector3
{
public:
	int m_X;
	int m_Y;
	int m_Z;

	Vector3();
	Vector3(int x, int y, int z);
	~Vector3();

	bool operator==(const Vector3& other)const
	{
		return((m_X == other.m_X) && (m_Y == other.m_Y) && (m_Z == other.m_Z));
	}

	Vector3 operator+(const Vector3 & other)const
	{
		return(Vector3(m_X+other.m_X, m_Y +other.m_Y, m_Z + other.m_Z));
	}
	
	friend std::ostream & operator<<(std::ostream & out, const Vector3 vec)
	{
		out << "(" << vec.m_X << ", " << vec.m_Y << ", " << vec.m_Z << ")";
		return out;
	}
};

