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
#include<time.h>
#include"Stock.h"

using namespace std;

int main()
{
	/*srand(time(NULL));

	unsigned long long int CoinCount = 1000000;
	unsigned long long int showStandard = 100;
	unsigned long long int front=0;
	unsigned long long int back=0;

	for (unsigned long long int i = 1; i <= CoinCount; i++)
	{
		int num = rand() % 2;
		if (num) front++;
		else back++;

		if (i == showStandard)
		{
			cout << i << "     ��°�� �� . ." << "�ո�: " << (double)front*100 / i << "%  " << "�޸�: " << (double)back*100 / i << "%" << endl;
			showStandard *= 10;
		}
	}*/

	//struct item
	//{
	//	char itemName;
	//	int itemRank;
	//	int probability;
	//};

	//item items[11] = {
	//{'A',5,1},
	//{'B',4,3},
	//{'C',4,3},
	//{'D',3,5},
	//{'E',3,5},
	//{'F',3,5},
	//{'G',2,10},
	//{'H',2,10},
	//{'I',2,10},
	//{'J',2,10},
	//{'K',1,38},
	//};

	//srand(time(NULL));

	//const long long int Count = 100;
	//char itemSpawn[Count] = {};

	//long long int start = 0;
	//for (int i = 0; i < 11; i++)
	//{	
	//	long long int countings = (items[i].probability * Count) / 100;

	//	for (int j = start; j < start+countings; j++)
	//	{
	//		itemSpawn[j] = items[i].itemName;
	//	}

	//	start += countings;
	//}


	//for (long long int i = 0; i < Count * 20; i++)
	//{
	//	int nSrc = rand() % Count;
	//	int nDest = rand() % Count;

	//	char temp = itemSpawn[nSrc];
	//	itemSpawn[nSrc]=itemSpawn[nDest];
	//	itemSpawn[nDest]=temp;
	//}


	//for (int i = 0; i < Count; i++)
	//{
	//	cout << itemSpawn[i] << " ";
	//}


	//Stock fluffy_the_cat;
	//fluffy_the_cat.acquire("NanoSmart", 20, 12.50);
	//fluffy_the_cat.show();
	//fluffy_the_cat.buy(15, 18.125);
	//fluffy_the_cat.show();
	//fluffy_the_cat.sell(400, 20.00);
	//fluffy_the_cat.show();
	//fluffy_the_cat.buy(300000, 40.125);
	//fluffy_the_cat.show();
	//fluffy_the_cat.sell(300000, 0.125);
	//fluffy_the_cat.show();

	//cout << "�����ڸ� ����Ͽ� ���ο� ��ü�� �����Ѵ�" << endl;
	//Stock stock1("NanoSmart", 12, 20.0);
	//stock1.show();
	//Stock stock2 = Stock("Boffo Objects", 2, 2.0);
	//stock2.show();

	//cout << "stock1�� stock2�� �����Ѵ�" << endl;

	//stock2 = stock1;

	//cout << "stock1�� stock2�� ����Ѵ�" << endl;
	//stock1.show();
	//stock2.show();

	//cout << "�����ڸ� ����Ͽ� ��ü�� �缳���Ѵ�" << endl;
	//stock1 = Stock("Nifty Foods", 10, 50.0);
	//cout << "���ŵ� stock1: " << endl;
	//stock1.show();
	//cout << "���α׷��� �����մϴ�." << endl;

	/*const int lockerNum = 100;
	bool locker[lockerNum] = {false,};
	int StudentNum = 100;
	int JumpNum = 1;

	for (int i = 0; i < StudentNum; i++)
	{
		
		for(int j=i;j<lockerNum;j+=JumpNum)
		{
			if (locker[j] == false) 
				locker[j] = true;
			else locker[j] = false;
		}

		JumpNum++;
	}

	for (int i = 0; i < lockerNum  ; i++)
	{
		if(locker[i] == true)
			cout << i + 1 << "�� �繰��" << endl;
	}*/
	
	return 0;
}