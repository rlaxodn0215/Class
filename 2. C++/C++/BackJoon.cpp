#include<iostream>
#include<vector>
    //ios::sync_with_stdio(0);
    //cin.tie(0);

using namespace std;

int arr[101][101];
bool rel[101];
int ans[101];
int ansNode = 1;


void func(int n,int node, int depth)
{

    if (depth==2)
    {
        return;
    }


    for (int i = 1; i <= n; i++)
    {
        if (arr[node][i] == 1)// ±æ ¾ø´Ù
        {
            rel[i] = true;
            func(n, i, depth+1);
        }
    }


   /* for (int i = node; i <= n; i++)
    {
        if (rel[i])
        {
            ans[ansNode]++;
            rel[i] = false;
        }
    }*/

}

int main()
{
    int n = 5;
    int m = 6;
    int num = -1;
    int depth = 0;
    int relation[6][2] = { {1,2},{1,3},{1,4},{2,3},{2,4},{4,5} };

    for (int i = 0; i < m; i++)
    {
        arr[relation[i][0]][relation[i][1]] = 1;
        arr[relation[i][1]][relation[i][0]] = 1;
    }

    for (int i = 1; i <= n; i++)
    {

        func(n, i, depth);

        for (int j = 1; j <= n; j++)
        {
            if (rel[j])
            {
                num++;
                rel[j] = false;
            }
        }

        cout << num;
        num = -1;
    }



    cout << '\n';

    return 0;
}

