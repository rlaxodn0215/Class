#include<iostream>
#include<vector>
#include"StopWatch.h"

//ios::sync_with_stdio(0);
//cin.tie(0);

using namespace std;

int list[100];

void func(int * arr, int arrlen)
{
    int max=arr[0];

    for (int i = 0; i < arrlen; i++)
    {
        list[arr[i]] += 1;
        max = (arr[i] > max) ? arr[i] : max;
    }

    int j = 0;
    while(1)
    {
        while (list[j] != 0)
        {
            cout << j << " ";
            list[j]--;
        }
        if (j == max) break;
         else j++;
    }
    cout << "\n";
}


int main()
{
    int num[13] = {72,8,19,6,55,55,33,2,17,17,69,88,88};
    func(num,13);

    return 0;
}

