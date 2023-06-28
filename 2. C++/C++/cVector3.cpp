#include "cVector3.h"

using namespace std;

cVector3::cVector3()
{
	posX = posY = posZ = 0;
}

cVector3::cVector3(double x, double y, double z)
{
	posX = x;
	posY = y;
	posZ = z;
}

cVector3::~cVector3()
{
	//cout << "나 사라진다~~" << endl;
}

bool cVector3::operator==(const cVector3& vec)
{
	if (posX == vec.posX && posY == vec.posY && posZ == vec.posZ)
	{
		return 1;
	}

	else
	{
		return 0;
	}
}

bool cVector3::operator!=(const cVector3& vec)
{
	if (!(posX == vec.posX && posY == vec.posY && posZ == vec.posZ))
	{
		return 1;
	}

	else
	{
		return 0;
	}
}

cVector3 cVector3::operator+(const cVector3& vec)
{
	cVector3 v;
	v.posX = posX + vec.posX;
	v.posY = posY + vec.posY;
	v.posZ = posZ + vec.posZ;

	return v;
}

cVector3 cVector3::operator-(const cVector3& vec)
{

	cVector3 v;
	v.posX = posX - vec.posX;
	v.posY = posY - vec.posY;
	v.posZ = posZ - vec.posZ;

	return v;
}
cVector3 cVector3::operator=(const cVector3& vec)
{
	posX = vec.posX;
	posY = vec.posY;
	posZ = vec.posZ;

	return *this;
}

cVector3 cVector3::operator*(double d)
{
	cVector3 v;
	v.posX = posX * d;
	v.posY = posY * d;
	v.posZ = posZ * d;

	return v;
}

cVector3 cVector3::operator/(double d)
{
	cVector3 v;
	v.posX = posX / d;
	v.posY = posY / d;
	v.posZ = posZ / d;

	return v;

}

double cVector3::length()
{
	double len;
	len = sqrt(posX * posX + posY * posY + posZ * posZ);

	return len;
}

cVector3 cVector3::Normalize()
{
	double len;
	len = sqrt(posX * posX + posY * posY + posZ * posZ);

	posX /= len;
	posY /= len;
	posZ /= len;

	return *this;
}

double cVector3::Dot(cVector3& v1)
{
	double dot;

	dot = posX * v1.posX + posY * v1.posY + posZ * v1.posZ;

	return dot;
}

cVector3 cVector3::Cross(cVector3& v1)
{
	cVector3 v;

	v.posX = posY * v1.posZ - v1.posY * posZ;
	v.posY = v1.posX * posZ - posX * v1.posZ;
	v.posZ = posX * v1.posY - v1.posX * posY;

	return v;
}

double cVector3::Angle(cVector3& v1)
{
	double cosine = this->Dot(v1) / (this->length() * v1.length());

	double acCos = acos(cosine);

	return acCos*57.2958;
}

cVector3 operator*(double n, cVector3& vec)
{
	cVector3 v;
	v.posX = vec.posX * n;
	v.posY = vec.posY * n;
	v.posZ = vec.posZ * n;
	return v;
}

std::ostream& operator<<(std::ostream& os, const cVector3& vec)
{
	os << "x: " << vec.posX << ", y: " << vec.posY << ", z: " << vec.posZ;
	return os;
}
