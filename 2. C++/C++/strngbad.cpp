#include "strngbad.h"
#include<cstring>
using std::cout;

int StringBad::num_strings = 0;

StringBad::StringBad(const char* s)
{
	len = std::strlen(s);
	str = new char[len + 1];
	std::strcpy(str, s);
	num_strings++;
	cout << num_strings << ": \"" << str << "\" °´Ã¼»ý¼º\n";
}

StringBad::StringBad()
{
	len = 4;
	str = new char[4];
	std::strcpy(str, "C++");
	num_strings++;
	cout << num_strings << ": \"" << str << "\" µðÆúÆ® °´Ã¼»ý¼º\n";
}

StringBad::~StringBad()
{
	cout << "\"" << str << "\" °´Ã¼ ÆÄ±«, ";
	--num_strings;
	cout << "³²Àº °´Ã¼ ¼ö: " << num_strings << "\n";
	delete[] str;
}

std::ostream& operator<<(std::ostream& os, const StringBad& st)
{
	os << st.str;
	return os;
	// TODO: ¿©±â¿¡ return ¹®À» »ðÀÔÇÕ´Ï´Ù.
}
