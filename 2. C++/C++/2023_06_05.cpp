#define _CRT_SECURE_NO_WARNINGS
#include<iostream> //istream + ostream
#include<climits>
#include<string>
#include <cstring>
#include<stdlib.h>
#include<crtdbg.h>
#include<vector>
#include<cmath>
#include<fstream> //���� ����� ���̺귯��
#include<new>

using namespace std;

//struct rect
//{
//	double posX;
//	double posY;
//	double width;
//	double height;
//};

//const int BUF = 512;
//const int N = 5;
//char buffer[BUF];

int main()
{
	//rect first, second;

	//while (1)
	//{
	//	cout << "ù ��° �簢�� x,y,width,height : ";
	//	cin >> first.posX >> first.posY >> first.width >> first.height;
	//	cout << "�� ��° �簢�� x,y,width,height : ";
	//	cin >> second.posX >> second.posY >> second.width >> second.height;

	//	bool horizonalFade = (abs(first.posX - second.posY) <= (first.height + second.height) * 0.5) ? true : false;
	//	bool verticalFade = (abs(first.posY - second.posY) <= (first.width + second.width) * 0.5) ? true : false;

	//	if (horizonalFade && verticalFade)
	//	{
	//		if ((second.posX>=first.posX-((first.width-second.width)/2) && second.posX <= first.posX + ((first.width - second.width) / 2))
	//			&& (second.posY >= first.posY - ((first.height - second.height) / 2) && second.posY <= first.posY + (first.height - second.height) / 2))
	//		{
	//			cout << "ù��° �簢�� ���ο� �ι�° �簢���� �ִ�." << endl;
	//		}

	//		else if ((first.posX >= second.posX - ((second.width-first.width) / 2) && first.posX <=second.posX + ((second.width - first.width) / 2))
	//			&& (first.posY >= second.posY - ((second.height-first.height) / 2) && first.posY <= second.posY + ((second.height - first.height) / 2)))
	//		{
	//			cout << "�ι�° �簢�� ���ο� ù��° �簢���� �ִ�." << endl;
	//		}

	//		else
	//		{
	//			cout << "�� �簢���� ���ƴ�." << endl;
	//		}

	//	}

	//	else
	//	{
	//		cout << "�� �簢���� ��ġ�� �ʴ´�." << endl;
	//	}

	//	cout << endl;
	//}



	//double* pd1, * pd2;
	//int i;
	//cout << "new�� ��ġ���� new�� ù ȣ��" << endl;
	//pd1 = new double[N];
	//pd2 = new (buffer)double[N];
	//for (i = 0; i < N; i++)
	//{
	//	pd2[i] = pd1[i] = 1000 + 20.0 * i;
	//}

	//cout << "�޸� �ּ�:\n" << pd1 << " : ��;      "
	//	<< (void*)buffer << " : ����" << endl;
	//cout << "�޸� ����: \n";
	//for (i = 0; i < N; i++)
	//{
	//	cout << &pd1[i] << "�� " << pd1[i] << ";   ";
	//	cout << &pd2[i] << "�� " << pd2[i] << endl;
	//}

	//cout << "\nnew�� ��ġ���� new �� �� ��° ȣ��: \n";
	//double* pd3, * pd4;
	//pd3 = new double[3];
	//pd4 = new(buffer)double[N];
	//for (i = 0; i < N; i++)
	//{
	//	cout << &pd3[i] << "�� " << pd3[i] << ";   ";
	//	cout << &pd4[i] << "�� " << pd4[i] << endl;
	//}

	//cout << "\nnew�� ��ġ���� new�� �� ��° ȣ��:\n";
	//delete[] pd1;

	//pd1 = new double[N];
	//pd2 = new(buffer + N * sizeof(double)) double[N];
	//for (i = 0; i < N; i++)
	//{
	//	pd2[i] = pd1[i] = 1000 + 60.0 * i;
	//}

	//cout << "�޸� ����:\n";
	//for (i = 0; i < N; i++)
	//{
	//	cout << &pd1[i] << "�� " << pd1[i] << ": ";
	//	cout << &pd2[i] << "�� " << pd2[i] << endl;
	//}

	//delete[] pd1;
	//delete[] pd3;

	//struct circle
	//{
	//	double x;
	//	double y;
	//	double radius;
	//};

	//circle first, second;
	//cout << "ù ��° ��(x,y,radius): ";
	//cin >> first.x >> first.y >> first.radius;
	//cout << "�� ��° ��(x,y,radius): ";
	//cin >> second.x >> second.y >> second.radius;

	//double lenght = sqrt((first.x - second.x) * (first.x - second.x) + (first.y - second.y) * (first.y - second.y));

	//if (lenght <= first.radius - second.radius)
	//{
	//	cout << "�� ��° ���� ù ��° �� �ȿ� �ִ�." << endl;
	//}

	//else if (lenght <= second.radius - first.radius)
	//{
	//	cout << "ù ��° ���� �� ��° �� �ȿ� �ִ�." << endl;
	//}

	//else if (lenght > abs(second.radius - first.radius) && lenght <= first.radius + second.radius)
	//{
	//	cout << "�� ���� ��ģ��." << endl;
	//}

	//else
	//{
	//	cout << "�� ���� ��ġ�� �ʴ´�." << endl;
	//}


	return 0;
}