class Solution
{
public:
    int numIslands(vector<vector<char>>& grid)
    {
        int ans = 0;

        int m = grid.size();
        int n = grid[0].size();

        int dx[4] = { -1,0,1,0 };
        int dy[4] = { 0,-1,0,1 };

        bool visited[m][n];
        fill(&visited[0][0], &visited[m - 1][n], false);
        queue<pair<int, int>> num;

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (!visited[i][j] && grid[i][j] == '1')
                {
                    //BFS (other way DFS)
                    num.push({ i,j });
                    visited[i][j] = true;

                    while (!num.empty())
                    {
                        pair<int, int> temp = num.front();
                        num.pop();

                        for (int k = 0; k < 4; k++)
                        {
                            int y = temp.first + dx[k];
                            int x = temp.second + dy[k];

                            if (y < 0 || y >= m || x < 0 || x >= n) continue;
                            if (visited[y][x]) continue;
                            if (grid[y][x] == '1')
                            {
                                visited[y][x] = true;
                                num.push({ y,x });
                            }
                        }


                    }

                    ans++;

                }

                else
                {
                    visited[i][j] = true;
                }
            }
        }

        return ans;
    }
};


