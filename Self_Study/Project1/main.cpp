#include<iostream>
#include<vector>

using namespace std;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };
int visited = -1;
bool ans = false;

void BackTracking(int index, int m, int n, vector<vector<char>>& board, string word, int visited)
{
    if (index == word.size())
    {
        ans = true;
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        if (i == visited) continue;

        int y = m + dy[i];
        int x = n + dx[i];

        if (y < 0 || y >= board.size() || x < 0 || x >= board[0].size()) continue;
        if (board[y][x] == word[index])
        {
            BackTracking(index + 1, y, x, board, word, (i+2)%4);
        }
    }

}

bool exist(vector<vector<char>>& board, string word)
{
    int m = board.size();
    int n = board[0].size();

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == word[0])
            {
                BackTracking(1, i, j, board, word, -1);
            }
        }
    }

    return true;
}

int main()
{
    vector<vector<char>> board = { {'A','B','C','E' }, {'S', 'F', 'C', 'S'},{'A', 'D', 'E', 'E'} };
    string word = "ABCCED";

    exist(board, word);
    cout << ans << endl;

    return 0;
}