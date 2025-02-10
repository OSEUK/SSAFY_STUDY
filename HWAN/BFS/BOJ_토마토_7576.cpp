#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int N, M;
vector<vector<int>> map;
vector<vector<int>> day;

bool inRange(int x, int y) {
	return 0 <= x && 0 <= y && x < M && y < N;
}

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

int main() {
	int flag = 1;
	int tomato;
	int last_day = 0;
	cin >> N >> M;
	map.resize(M, vector<int>(N, 0));
	day.resize(M, vector<int>(N, -1));
	queue<pair<int, int>> Q;

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> tomato;
			map[i][j] = tomato;
		}
	}
	
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[i][j] == 1) {
				Q.push({ i,j });
				day[i][j] = 0;
			}
		}
	}

	while (!Q.empty()) {
		auto cur = Q.front(); Q.pop();
		int nx, ny;

		for (int dir = 0; dir < 4; dir++) {
			nx = cur.first + dx[dir];
			ny = cur.second + dy[dir];
			if (!inRange(nx,ny)) continue;
			if (map[nx][ny] == -1 || day[nx][ny] >= 0) continue;
			Q.push({ nx,ny });
			map[nx][ny] = 1;
			day[nx][ny] = day[cur.first][cur.second] + 1;
			last_day = day[nx][ny];
		}
	}

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {

			if (map[i][j] == 0) {
				flag = 0;
			}
		}
	}
	if (flag) cout << last_day;
	else cout << -1;

	


}