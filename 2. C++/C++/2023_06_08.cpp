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
#include<time.h>
#include"Stock.h"

using namespace std;

void main()
{
	//double x0, y0, x1, y1, x2, y2;

	//while(1)
	//{
	//	cout << "p0, p1, p2 : ";
	//	cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2;

	//	int define = y2 * (x1 - x0) - x2 * (y1 - y0);

	//	if (define > 0)
	//		cout << "p2는 선의 왼쪽에 있다." << endl;
	//	else if (define < 0)
	//		cout << "p2는 선의 오른쪽에 있다." << endl;
	//	else
	//		cout << "p2는 선상에 있다." << endl;
	//
	//}

	//srand(time(NULL));
	//string words[3] = {"apple","banana","cat" };
	//int failCount = 0;
	//int correctCount = 0;
	//char answerWord='0';

	//while (1)
	//{
	//	int wordNum = rand() % 3;
	//	string Answer = words[wordNum];
	//	string playerAnswer = "";

	//	for (int i = 0; i < Answer.size(); i++)
	//	{
	//		playerAnswer += '*';
	//	}

	//	while (1)
	//	{

	//		cout << playerAnswer << endl;
	//		bool SameWord = true;

	//		while (SameWord)
	//		{
	//			cout << "단어중 한 글자를 입력하세요 :";
	//			cin >> answerWord;
	//			getchar();

	//			SameWord = false;
	//			for (int i = 0; i < Answer.size(); i++)
	//			{
	//				if (playerAnswer[i] == answerWord)
	//				{
	//					cout << endl;
	//					cout << answerWord << "는 이미 단어에 포함되었습니다." << endl;
	//					SameWord = true;
	//					failCount++;
	//					break;
	//				}
	//			}
	//		}

	//		int check;
	//		bool incorrect=true;
	//		for (check = 0; check < Answer.size(); check++)
	//		{
	//			if (Answer[check] == answerWord)
	//			{
	//				playerAnswer[check] = answerWord;
	//				correctCount++;
	//				incorrect = false;
	//			}
	//		}

	//		if (check == Answer.size() && incorrect)
	//		{
	//			cout << answerWord << "은 단어에 포함되지 않습니다." << endl;
	//			failCount++;
	//		}

	//		if (playerAnswer == Answer)
	//		{
	//			cout << "총 " << failCount << "번 실패, " << failCount+correctCount << "번 만에 정답!" << Answer << endl;
	//			break;
	//		}

	//		cout << endl;
	//	}

	//	char contin;
	//	cout << endl;
	//	cout << "다시 시작하시겠습니까? (y,n) : ";
	//	cin >> contin;

	//	if (contin == 'n') break;

	//}

	//const int STKS = 4;
	//Stock stocks[STKS] = {
	//	Stock("NanpSmart",12,20.0),
	//	Stock("Boffo Obhects",200,2.0),
	//	Stock("Monolithic Oblisks",130,3.25),
	//	Stock("Fleep Enterprise",60,6.5)
	//};

	//cout << "보유주식 리스트\n";
	//int st;

	//for (st = 0; st < STKS; st++)
	//	stocks[st].show();

	//const Stock* top = &stocks[0];

	//for (st = 1; st < STKS; st++)
	//	top = &top->topval(stocks[st]);

	//cout << "\n최고 가치의 주식:\n";
	//top->


}