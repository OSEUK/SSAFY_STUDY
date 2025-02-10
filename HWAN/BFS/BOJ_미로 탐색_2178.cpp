#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> map;
int N, M;
vector<vector<int>> visited;
queue<pair<int, int>> Q;

bool inRange(int x, int y) {
	return 0 <= x && 0 <= y && x < N && y < M;
}

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

void bfs(int x, int y) {
	int nx, ny;
	Q.push({ x,y });
	visited[x][y] = 1;
	while (!Q.empty()) {
		auto cur = Q.front(); Q.pop();

		for (int i = 0; i < 4; i++) {

			nx = cur.first + dx[i];
			ny = cur.second + dy[i];

			if (!inRange(nx, ny) || visited[nx][ny] || map[nx][ny] == 0) continue;
			Q.push({ nx,ny });
			visited[nx][ny] = visited[cur.first][cur.second]+1;
		}
	}
}
int main() {
	string str;
	cin >> N >> M;

	map.resize(N, vector<int>(M, 0));
	visited.resize(N, vector<int>(M, 0));

	for (int i = 0; i < N; i++) {
		cin >> str;
		for (int j = 0; j < M; j++) {
			map[i][j] = str[j]-'0';
		}
	}
	int val=0;
	int max = 0;
	/*for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if(!visited[i][j] && map[i][j]==0) bfs(i, j);
		}
	}*/
	bfs(0, 0);
	cout << visited[N-1][M-1];


}