#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

using namespace std;

class String
{
private:
	char* str;
	int len;
	static int num_strings;
	static const int CINLIM = 80;
public:
	String(const char* s);
	String();
	String(const String& st);
	~String();
	int length()const { return len; }
	String& operator=(const String& st);
	String& operator=(const char* s);
	char& operator[](int i);
	const char& operator[](int i)const;
	friend bool operator<(const String& st1, const String st2);
	friend bool operator>(const String& st1, const String& st2);
	friend bool operator == (const String& st1, const String& st2);
	friend ostream& operator<<(ostream& os, const String& st);
	friend istream& operator>>(istream& is, String& st);
	static int HowMany();

	void stringlow();
	void stringup();
	int has(char ch);
	friend String operator+(const String& st1, const String& st2);
};