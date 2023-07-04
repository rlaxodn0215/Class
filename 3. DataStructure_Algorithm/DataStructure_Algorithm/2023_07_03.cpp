#include<iostream>

int arr[100005];
int node = 0;

using namespace std;

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void sort()
{
	node--;
	int line = 1;
	int childline;
	int nextChildLine;

	while (1)
	{
		childline = line * 2;
		nextChildLine = childline + 1;

		if (node < childline) //자식 없음
		{
			break;
		}

		else
		{
			int Min = childline;

			if (nextChildLine <= node) //R이 존재
			{
				if (arr[nextChildLine] < arr[Min])
				{
					Min = nextChildLine;
				}
			}


			if (arr[Min] < arr[line])
			{
				swap(arr[line], arr[Min]);
				line = Min;
			}

			else
			{
				break;
			}
		}

	
	}
}

void push(int & n)
{
	arr[++node] = n;
	int temp = node;

	int parentTemp;
	int nextTemp;

	while (temp != 1)
	{
		parentTemp = temp / 2;

		if (arr[temp] < arr[parentTemp])
		{
			swap(arr[temp], arr[parentTemp]);
			temp = parentTemp;
		}

		else
		{
			break;
		}

	}

}

void pop()
{
	cout << arr[1]<<'\n';
	arr[1] = arr[node];
	arr[node]=0;
	//sort();
	node--;
	int line = 1;
	int childline;
	int nextChildLine;

	while (1)
	{
		childline = line * 2;
		nextChildLine = childline + 1;

		if (node < childline) //자식 없음
		{
			break;
		}

		else
		{
			int Min = childline;

			if (nextChildLine <= node) //R이 존재
			{
				if (arr[nextChildLine] < arr[Min])
				{
					Min = nextChildLine;
				}
			}


			if (arr[Min] < arr[line])
			{
				swap(arr[line], arr[Min]);
				line = Min;
			}

			else
			{
				break;
			}
		}


	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	int count;
	int num;

	cin >> count;

	for (int i = 0; i < count; i++)
	{
		cin >> num;
		 
		if (num == 0)
		{
			if (node != 0)
				pop();
			else
				cout << 0<<"\n";
			
		}

		else
		{
			push(num);
		}
	}

	return 0;
}