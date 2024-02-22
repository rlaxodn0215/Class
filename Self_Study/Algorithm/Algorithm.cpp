#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

#define M 3
#define N 2

int solution1();
vector<vector<float>> solution2();
vector<float> FindMid(int startX, int startY, int endX, int endY);

int main()
{
    cout << solution1() << '\n';

    vector<vector<float>> temp = solution2();
    
    for (int i = 0; i < temp.size(); i++)
    {
        cout << "(" << temp[i][0] << ", " << temp[i][1] << ")" << '\n';
    }

    return 0;
}

int solution1()
{
    int answer = 0;
    int dp[M][N] = {0,};

    dp[0][0] = 1;

    for (int i = 1; i < M; i++)
        dp[i][0] = dp[i - 1][0] + (i + 1);
    for (int i = 1; i < N; i++)
        dp[0][i] = dp[0][i-1] + (i + 1);

    for (int i = 1; i < M; i++)
    {
        for (int j = 1; j < N; j++)
        {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + (i + 1) * (j + 1);
        }
    }

    return dp[M-1][N-1];
}

vector<vector<float>> solution2()
{
    vector<vector<float>> ans;
    
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = i + 1; k <= M; k++)
            {
                for (int l = j + 1; l <= N; l++)
                {
                    ans.push_back(FindMid(j,i,l,k));
                }
            }
        }
    }
    return ans;
}

vector<float> FindMid(int startX, int startY, int endX, int endY)
{
    return {(endY- startY)/2.0f, (endX - startX) / 2.0f };
}