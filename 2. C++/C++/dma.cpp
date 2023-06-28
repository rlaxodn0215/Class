#define _CRT_SECURE_NO_WARNINGS
#include "dma.h"
#include<cstring>

using namespace std;

baseDMA::baseDMA(const char* l, int r)
{
    label = new char[std::strlen(l) + 1];
    std::strcpy(label, l);
    rating = r;
    cout << "baseDMA 积己磊" << endl;
}

baseDMA::baseDMA(const baseDMA& rs)
{
    label = new char[std::strlen(rs.label) + 1];
    std::strcpy(label, rs.label);
    rating = rs.rating;
    cout << "baseDMA 积己磊" << endl;
}

baseDMA::~baseDMA()
{
    delete[] label;
    cout << "baseDMA 家戈磊" << endl;
}

baseDMA& baseDMA::operator=(const baseDMA& rs)
{
    if (this == &rs)
        return *this;
    delete[] label;
    label = new char[std::strlen(rs.label) + 1];
    std::strcpy(label, rs.label);
    rating = rs.rating;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const baseDMA& rs)
{
    os << "惑钎: " << rs.label << std::endl;
    os << "殿鞭: " << rs.rating << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const lacksDMA& ls)
{
    os << (const baseDMA&)ls;
    os << "祸惑: " << ls.color << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const hasDMA& hs)
{
    os << (const baseDMA&)hs;
    os << "胶鸥老: " << hs.style << std::endl;
    return os;
}

lacksDMA::lacksDMA(const char* c, const char* l, int r): baseDMA(l,r)
{
    std::strncpy(color, c, 39);
    color[39] = '\0';
    cout << "lacksDMA 积己磊" << endl;
}

lacksDMA::lacksDMA(const char* c, const baseDMA& rs): baseDMA(rs)
{
    std::strncpy(color, c, COL_LEN - 1);
    color[COL_LEN - 1] = '\0';
    cout << "lacksDMA 积己磊" << endl;
}

hasDMA::hasDMA(const char* s, const char* l, int r): baseDMA(l,r)
{
    style = new char[std::strlen(s) + 1];
    std::strcpy(style, s);
    cout << "hasDMA 积己磊" << endl;
}

hasDMA::hasDMA(const char* s, const baseDMA& rs): baseDMA(rs)
{
    style = new char[std::strlen(s) + 1];
    std::strcpy(style, s);
    cout << "hasDMA 积己磊" << endl;
}

hasDMA::hasDMA(const hasDMA& hs): baseDMA(hs)
{
    style = new char[std::strlen(hs.style) + 1];
    std::strcpy(style, hs.style);
    cout << "hasDMA 积己磊" << endl;
}

hasDMA::~hasDMA()
{
    cout << "hasDMA 家戈磊" << endl;
    delete[] style;

}

hasDMA& hasDMA::operator=(const hasDMA& hs)
{
    if (this == &hs)
        return *this;
    baseDMA::operator=(hs);
    delete[] style;
    style = new char[std::strlen(hs.style) + 1];
    std::strcpy(style, hs.style);
    return *this;
}
