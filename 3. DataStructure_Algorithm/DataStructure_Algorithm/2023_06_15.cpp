#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

char top[10][10] = {'\0'};

void Print(int start,int end,int n)
{
	//printf("원반[%d]를 %d 기둥에서 %d 기둥으로 옮김\n", n, start, end);

	int s=0, e=0;

	for (int i = 0; i < 10; i++)
	{
		if (!(top[i][start-1] >= 49 && top[i][start-1] <= 57))
		{
			s++;
		}

		if (!(top[i][end-1] >= 49 && top[i][end-1] <= 57))
		{
			e++;
		}
	}

	top[e-1][end - 1] = top[s][start - 1];
	top[s][start - 1] = '\0';


	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if(top[i][j]>=49 && top[i][j]<=57)
				cout << "[" << top[i][j] << "]" << "\t";

			else
				cout << "[ ]" << "\t";
		}
		cout << "\n";
	}

	cout << "-------------------------------\n";

	cout << "A\t" << "B\t" << "C\t" << endl<<endl;
}

void move(int start,int end,int sub, int n)
{
	if (n > 1)
	{
		move(start,sub,end, n - 1);
	}

	Print(start, end,n);

	if (n > 1)
	{
		move(sub, end, start, n - 1);
	}
	
}

int main()
{
	int n;
	cout << "원반 최대 크기(최대값: 10, 0.exit): ";
	cin >> n;

	int k = n;
	for (int i = 9; i >= 0; i--)
	{
		top[i][0] = k+48;
		k--;
	}

	move(1, 3, 2, n);

	return 0;
}