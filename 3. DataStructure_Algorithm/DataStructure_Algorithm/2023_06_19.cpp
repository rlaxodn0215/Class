#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

void func1() 
{
	int arr[7] = { 1,3,9,4,7,8,6 };

	int pass = 1;
	int compareCount = 0;
	int exchangeCount = 0;

	for (int i = 0; i < 7; i++)
	{
		cout << "패스 " << pass << endl;

		for (int j = 6; j >= i+1; j--)
		{
			compareCount++;
			if (arr[j] < arr[j - 1])
			{
				for (int k = 0; k < 7; k++)
				{
					if (k != j - 1)
						cout << arr[k] << "   ";
					else
					{
						cout << arr[k];
						cout << " + ";
					}
				}

				int temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
				exchangeCount++;
			}

			else
			{
				for (int k = 0; k < 7; k++)
				{
					if (k != j - 1)
						cout << arr[k] << "   ";
					else
					{
						cout << arr[k];
						cout << " - ";
					}
				}
			}

			cout << endl;

		}

		for (int k = 0; k < 7; k++)
		{
			cout << arr[k] << "   ";
		}
		cout << endl;

		pass++;
	}
	cout << endl;
	cout << "비교를 " << compareCount << "회 했습니다." << endl;
	cout << "교환을 " << exchangeCount << "회 했습니다." << endl;

}

void func2()
{
	int arr[7] = { 1,3,9,4,7,8,6 };

	int pass = 1;
	int compareCount = 0;
	int exchangeCount = 0;
	int exchange=0;

	for (int i = 0; i < 7; i++)
	{
		cout << "패스 " << pass << endl;

		for (int j = 6; j >= i + 1; j--)
		{
			compareCount++;
			if (arr[j] < arr[j - 1])
			{
				exchange++;
				for (int k = 0; k < 7; k++)
				{
					if (k != j - 1)
						cout << arr[k] << "   ";
					else
					{
						cout << arr[k];
						cout << " + ";
					}
				}

				cout << endl;

				int temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
				exchangeCount++;
			}

			else
			{
				for (int k = 0; k < 7; k++)
				{
					if (k != j - 1)
						cout << arr[k] << "   ";
					else
					{
						cout << arr[k];
						cout << " - ";
					}
				}

				cout << endl;
			}

		}

		for (int k = 0; k < 7; k++)
		{
			cout << arr[k] << "   ";
		}

		cout << endl;
		if (exchange == 0)
		{
			cout << endl;
			break;
		}

		else
		{
			cout << endl;
			exchange = 0;
		}
		pass++;
	}
	cout << endl;
	cout << "비교를 " << compareCount << "회 했습니다." << endl;
	cout << "교환을 " << exchangeCount << "회 했습니다." << endl;
}

void func3()
{
	int arr[7] = { 1,3,9,4,7,8,6 };

	int pass = 1;
	int compareCount = 0;
	int exchangeCount = 0;
	int lastChange=-1;
	for (int i = 0; i < 7; i++)
	{
		lastChange = -1;
		cout << "패스 " << pass << endl;

		for (int j = 6; j >= i + 1; j--)
		{
			compareCount++;
			if (arr[j] < arr[j - 1])
			{
				lastChange = j-1;
				for (int k = 0; k < 7; k++)
				{
					if (k != j - 1)
						cout << arr[k] << "   ";
					else
					{
						cout << arr[k];
						cout << " + ";
					}
				}

				cout << endl;

				int temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
				exchangeCount++;
			}

			else
			{
				for (int k = 0; k < 7; k++)
				{
					if (k != j - 1)
						cout << arr[k] << "   ";
					else
					{
						cout << arr[k];
						cout << " - ";
					}
				}

				cout << endl;
			}

		}

		if(lastChange !=-1)
		i = lastChange;

		for (int k = 0; k < 7; k++)
		{
			cout << arr[k] << "   ";
		}

		cout << endl;
		pass++;
	}
	cout << endl;
	cout << "비교를 " << compareCount << "회 했습니다." << endl;
	cout << "교환을 " << exchangeCount << "회 했습니다." << endl;
}

void main()
{
	func3();
}