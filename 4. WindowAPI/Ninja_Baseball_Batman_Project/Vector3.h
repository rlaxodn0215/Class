#pragma once
#include<iostream>

class Vector3
{
public:
	int m_Pos_X;
	int m_Pos_Y;
	int m_Pos_Z;

	Vector3();
	Vector3(int x, int y, int z);
	~Vector3();

	bool operator==(const Vector3& other)const
	{
		return((m_Pos_X == other.m_Pos_X) && (m_Pos_Y == other.m_Pos_Y) && (m_Pos_Z == other.m_Pos_Z));
	}

	Vector3 operator+(const Vector3 & other)const
	{
		return(Vector3(m_Pos_X+other.m_Pos_X, m_Pos_Y +other.m_Pos_Y, m_Pos_Z + other.m_Pos_Z));
	}
	
	friend std::ostream & operator<<(std::ostream & out, const Vector3 vec)
	{
		out << "(" << vec.m_Pos_X << ", " << vec.m_Pos_Y << ", " << vec.m_Pos_Z << ")";
		return out;
	}
};

