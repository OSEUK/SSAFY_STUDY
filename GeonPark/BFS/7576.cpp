#include <iostream>
#include <vector>
#include <string>
#include <deque>
using namespace std;
#define endl '\n'
//g++ algo.cpp && ./a.out

int map[1002][1002];
bool visited[1002][1002];

int main()
{
	int n, m;
	cin >> m >> n;
	deque<pair<int, int>> d;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 1)
			{
				d.push_back({ j, i });
			}
		}
	}

	int dx[4] = { 1, 0, 0, -1 };
	int dy[4] = { 0, -1, 1, 0 };
	int max = 0;

	while (!d.empty())
	{
		int curx = d.front().first;
		int cury = d.front().second;
		d.pop_front();
		for (int k = 0; k < 4; k++)
		{
			int nx = curx + dx[k];
			int ny = cury + dy[k];
			if (nx >= 0 && ny >= 0 && nx < m && ny < n && map[ny][nx] == 0 && !visited[ny][nx])
			{
				visited[ny][nx] = true;
				d.push_back({ nx, ny });
				if (map[ny][nx] == 0)
				{
					map[ny][nx] = map[cury][curx] + 1;
				}
				if (map[ny][nx] > max)
				{
					max = map[ny][nx];
				}
			}
		}
	}
	/*cout << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << map[i][j] << " ";
		}
		cout << endl;
	}*/

	bool flag = true;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] == 0)
			{
				flag = false;
			}
		}
	}

	if (flag)
	{
		if (max <= 0)
		{
			cout << max << endl;
		}
		else
		{
			cout << max - 1 << endl;
		}
	}
	else
	{
		cout << -1 << endl;
	}
}