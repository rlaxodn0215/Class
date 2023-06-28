#define _CRT_SECURE_NO_WARNINGS
#include<iostream> //istream + ostream
#include<climits>
#include<string>
#include <cstring>
#include<stdlib.h>
#include<crtdbg.h>
#include<vector>
#include<cmath>
#include<fstream> //파일 입출력 라이브러리
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
	//	cout << "첫 번째 사각형 x,y,width,height : ";
	//	cin >> first.posX >> first.posY >> first.width >> first.height;
	//	cout << "두 번째 사각형 x,y,width,height : ";
	//	cin >> second.posX >> second.posY >> second.width >> second.height;

	//	bool horizonalFade = (abs(first.posX - second.posY) <= (first.height + second.height) * 0.5) ? true : false;
	//	bool verticalFade = (abs(first.posY - second.posY) <= (first.width + second.width) * 0.5) ? true : false;

	//	if (horizonalFade && verticalFade)
	//	{
	//		if ((second.posX>=first.posX-((first.width-second.width)/2) && second.posX <= first.posX + ((first.width - second.width) / 2))
	//			&& (second.posY >= first.posY - ((first.height - second.height) / 2) && second.posY <= first.posY + (first.height - second.height) / 2))
	//		{
	//			cout << "첫번째 사각형 내부에 두번째 사각형이 있다." << endl;
	//		}

	//		else if ((first.posX >= second.posX - ((second.width-first.width) / 2) && first.posX <=second.posX + ((second.width - first.width) / 2))
	//			&& (first.posY >= second.posY - ((second.height-first.height) / 2) && first.posY <= second.posY + ((second.height - first.height) / 2)))
	//		{
	//			cout << "두번째 사각형 내부에 첫번째 사각형이 있다." << endl;
	//		}

	//		else
	//		{
	//			cout << "두 사각형은 겹쳤다." << endl;
	//		}

	//	}

	//	else
	//	{
	//		cout << "두 사각형은 겹치지 않는다." << endl;
	//	}

	//	cout << endl;
	//}



	//double* pd1, * pd2;
	//int i;
	//cout << "new와 위치지정 new의 첫 호출" << endl;
	//pd1 = new double[N];
	//pd2 = new (buffer)double[N];
	//for (i = 0; i < N; i++)
	//{
	//	pd2[i] = pd1[i] = 1000 + 20.0 * i;
	//}

	//cout << "메모리 주소:\n" << pd1 << " : 힙;      "
	//	<< (void*)buffer << " : 정적" << endl;
	//cout << "메모리 내용: \n";
	//for (i = 0; i < N; i++)
	//{
	//	cout << &pd1[i] << "에 " << pd1[i] << ";   ";
	//	cout << &pd2[i] << "에 " << pd2[i] << endl;
	//}

	//cout << "\nnew와 위치지정 new 의 두 번째 호출: \n";
	//double* pd3, * pd4;
	//pd3 = new double[3];
	//pd4 = new(buffer)double[N];
	//for (i = 0; i < N; i++)
	//{
	//	cout << &pd3[i] << "에 " << pd3[i] << ";   ";
	//	cout << &pd4[i] << "에 " << pd4[i] << endl;
	//}

	//cout << "\nnew와 위치지정 new의 세 번째 호출:\n";
	//delete[] pd1;

	//pd1 = new double[N];
	//pd2 = new(buffer + N * sizeof(double)) double[N];
	//for (i = 0; i < N; i++)
	//{
	//	pd2[i] = pd1[i] = 1000 + 60.0 * i;
	//}

	//cout << "메모리 내용:\n";
	//for (i = 0; i < N; i++)
	//{
	//	cout << &pd1[i] << "에 " << pd1[i] << ": ";
	//	cout << &pd2[i] << "에 " << pd2[i] << endl;
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
	//cout << "첫 번째 원(x,y,radius): ";
	//cin >> first.x >> first.y >> first.radius;
	//cout << "두 번째 원(x,y,radius): ";
	//cin >> second.x >> second.y >> second.radius;

	//double lenght = sqrt((first.x - second.x) * (first.x - second.x) + (first.y - second.y) * (first.y - second.y));

	//if (lenght <= first.radius - second.radius)
	//{
	//	cout << "두 번째 원은 첫 번째 원 안에 있다." << endl;
	//}

	//else if (lenght <= second.radius - first.radius)
	//{
	//	cout << "첫 번째 원은 두 번째 원 안에 있다." << endl;
	//}

	//else if (lenght > abs(second.radius - first.radius) && lenght <= first.radius + second.radius)
	//{
	//	cout << "두 원은 겹친다." << endl;
	//}

	//else
	//{
	//	cout << "두 원은 겹치지 않는다." << endl;
	//}


	return 0;
}