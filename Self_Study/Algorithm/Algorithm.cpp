#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

enum Status
{
	MOVE_ABLE,
	WALL,
	START,
	END
};

enum List
{
	NONE,
	OPEN_LIST,
	CLOSE_LIST,
	PATH
};

enum Way
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

struct Node
{
	int G;
	int H;
	int F;

	Way curWay;
};

void ReadData(string& way, vector<vector<char>>& map, pair<int, int>& start, pair<int, int>& end);
string AStar(string way, vector<vector<char>>& map, pair<int, int> start, pair<int, int> end);

int main()
{
	string firstWay = "";
	pair<int, int> start;
	pair<int, int> end;
	vector<vector<char>> Map;

	ReadData(firstWay, Map,start,end);

	cout << AStar(firstWay, Map, start, end) << "\n";


	return 0;
}

void ReadData(string& way, vector<vector<char>>& map, pair<int, int>& start, pair<int, int>& end)
{
	int width = 0;
	int height = 0;

	cin >> way;
	cin >> width;
	cin >> height;

	for (int i = 0; i < height; i++)
	{
		vector<char> line;

		for (int j = 0; j < width; j++)
		{
			char temp;
			cin >> temp;
			line.push_back(temp);

			if (temp == 'T')
			{
				start = { i, j };
			}

			else if (temp == 'G')
			{
				end = { i, j };
			}

		}

		map.push_back(line);
	}

}

string AStar(string firstway, vector<vector<char>>& map, pair<int, int> start, pair<int, int> end)
{
	string ans = "";

	string way = firstway;
	pair<int, int> point = start;

	int dx[4] = { -1, 0, 1, 0 };
	int dy[4] = { 0, -1, 0, 1 };

	while (0)
	{
		for (int i = 0; i < 4; i++)
		{
			int x = point.first + dx[i];
			int y = point.second + dy[i];

			if (x < 0 || y < 0 || x >= map.size() || y >= map[0].size()) continue;
			if (map[x][y] == '#') continue;

		}
	}


	return ans;
}

