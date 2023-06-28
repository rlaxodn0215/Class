#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<cstring>
#include<vector>
#include<memory>
#include<algorithm>
#include<list>
#include<iterator>
#include<set>
#include<cmath>
#include<fstream>
#include<iomanip>

using namespace std;

const int ascNum = 128;

int main()
{
	int codeNum = -1123;
	char letter;
	string sourceFileName,encordFileName,decodeFilename;
	cout << "Input source filename: ";
	cin >> sourceFileName;
	cout << "Input encording filename: ";
	cin >> encordFileName;

	ofstream fout;
	fout.open(encordFileName);
	ifstream fin;
	fin.open(sourceFileName);

	if (fout.is_open() && fin.is_open())
	{
		while (!fin.eof())
		{
			fin >> letter;
			if (codeNum < 0)
			{
				int num = codeNum % ascNum;
				letter = (ascNum + num + letter)%ascNum;
			}

			else
			{
				letter = (letter + codeNum) % ascNum;
			}

			fout << letter;
		}
	}
	else
	{
		exit(EXIT_FAILURE);
	}

	fout.close();
	fin. close();

	cout << "DecodeFile name: ";
	cin >> decodeFilename;

	ofstream fdecode;
	fdecode.open(decodeFilename);
	ifstream fencode;
	fencode.open(encordFileName);


	if (fdecode.is_open() && fencode.is_open())
	{
		while (!fencode.eof())
		{
			fencode >> letter;

			if (letter < codeNum)
			{
				int num = codeNum%ascNum;
				letter = num - letter;
			}

			else
			{
				letter = letter - codeNum;
			}

			fdecode << letter;
		}
	}
	else
	{
		exit(EXIT_FAILURE);
	}

	fdecode.close();
	fencode.close();

	return 0;
}