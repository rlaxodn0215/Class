#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>

using namespace std;

void reverseDisplay(int value);
void reverseDisplay(const string value);

int main()
{
	reverseDisplay(12345);
	cout << endl;
	reverseDisplay("abcd");
	return 0;
}

void reverseDisplay(int value)
{
	int digit = value % 10;
	cout << digit;
	value /=10;

	if (value != 0)
	{
		reverseDisplay(value);
	}

	return;
}

void reverseDisplay(const string value)
{
	string val = value;
	int length = val.size();


	if (length > 0)
	{
		cout << val[length - 1];
		length--;
		val = "";

		for (int i = 0; i < length; i++)
		{
			val += value[i];
		}

		reverseDisplay(val);
	}

	return;
}