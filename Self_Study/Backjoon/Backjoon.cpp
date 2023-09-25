#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>

using namespace std;

vector<int> solution(vector<string> maps);

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

    vector<string> map = { "X591X","X1X5X","X231X", "1XXX1" };

    vector<int> sol = solution(map);

    for (int i = 0; i < sol.size(); i++)
    {
        cout << sol[i] << endl;
    }

	return 0;
}

vector<int> solution(vector<string> maps)
{
    vector<int> answer;

    const int m = 4;
    const int n = 5;

    int dx[4] = { -1,0,1,0 };
    int dy[4] = { 0,-1,0,1 };

    bool visited[m][n];
    fill(&visited[0][0], &visited[m - 1][n], false);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (maps[i][j] != 'X' && !visited[i][j])
            {
                int num = 0;

                queue<pair<int, int>> temp;
                temp.push({ i,j });
                visited[i][j] = true;

                while (!temp.empty())
                {
                    pair<int, int> point = temp.front();
                    temp.pop();
                    num += maps[point.first][point.second] - 48;

                    for (int i = 0; i < 4; i++)
                    {
                        int nx = point.second + dx[i];
                        int ny = point.first + dy[i];

                        if (ny < 0 || ny >= m || nx < 0 || ny >= n)
                            continue;
                        if (maps[ny][nx] == 'X')
                        {
                            visited[ny][nx] = true;
                            continue;
                        }

                        if (!visited[ny][nx])
                        {
                            visited[ny][nx] = true;
                            temp.push({ ny,nx });
                        }
                    }

                }

                if (num != 0) 
                    answer.push_back(num);
            }
        }
    }

    if (answer.empty())
    {
        answer.push_back(-1);
        return answer;
    }

    else
    {
        //sort(answer.begin(), answer.end(),less<int>());
        return answer;
    }
}