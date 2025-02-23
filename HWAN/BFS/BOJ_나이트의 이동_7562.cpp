#include <iostream>
#include <queue>
using namespace std;

int dx[] = { 2,2,1,1,-1,-1,-2,-2 };
int dy[] = { 1,-1,2,-2,2,-2,1,-1 };

int N;
int sx, sy;
int ex, ey;
int map[300][300];
int visited[300][300];
int ans;
queue<pair<int, int>>Q;
bool inRange(int x, int y) {
	return 0 <= x && 0 <= y && x < N && y < N;
}

void init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			visited[i][j] = -1;
		}
	}
	ans = 0;
	while (!Q.empty()) {
		Q.pop();
	}
}

void bfs(int x, int y) {
	Q.push({ x,y });
	visited[x][y] = 0;

	int nx, ny;
	while (!Q.empty()) {
		auto cur = Q.front(); Q.pop();

		if (cur.first == ex && cur.second == ey) {
			ans = visited[cur.first][cur.second];
			break;
		}

		for (int dir = 0; dir < 8; dir++) {
			nx = cur.first + dx[dir];
			ny = cur.second + dy[dir];

			if (!inRange(nx, ny))continue;
			if (visited[nx][ny] > -1)continue;

			Q.push({ nx,ny });
			visited[nx][ny] = visited[cur.first][cur.second] + 1;
		}


	}
}

int main() {

	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cin >> N;
		cin >> sx >> sy;
		cin >> ex >> ey;
		init();
		bfs(sx, sy);

		cout << ans<<"\n";
	}
}