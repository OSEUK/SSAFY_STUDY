#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

int M, N;
vector<vector<int>> MAP;
vector<vector<int>> visited;
queue<pair<int, int>>Q;

int mov[2][4] = {
	{0,0,1,-1},
	{-1,1,0,0}
};

int in_range(int y, int x) {
	return y >= 0 && y < N && x >= 0 && x < M;
}

void bfs() {
	while (!Q.empty()) {
		pair<int,int> cur = Q.front();
		Q.pop();
		for (int i = 0;i < 4;i++) {
			int dy = cur.first + mov[0][i];
			int dx = cur.second + mov[1][i];
			if (!in_range(dy, dx) || visited[dy][dx] == 1 || MAP[dy][dx] == -1)continue;
			Q.push({ dy,dx });
			MAP[dy][dx] = MAP[cur.first][cur.second] + 1;
			visited[dy][dx] = 1;
		}
	}
	return;
}

void result() {
	int max = 0;
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M;j++) {
			if (MAP[i][j] == 0) {
				cout << -1;
				return;
			}
			if (max < MAP[i][j]) max = MAP[i][j];
		}
	}
	cout << max-1;
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	// 1. 맵 크기 입력
	cin >> M >> N;

	// 2. 맵 입력
	MAP.resize(N, vector<int>(M, 0));
	visited.resize(N, vector<int>(M, 0));

	int input;
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M;j++) {
			cin >> input;
			MAP[i][j] = input;
			if (input == 1) {
				Q.push({ i,j });
				visited[i][j] = 1;
			}
		}
	}

	// 3. bfs
	bfs();

	//// 4. 결과 확인
	//cout << "MAP\n";
	//for (int i = 0;i < N;i++) {
	//	for (int j = 0;j < M;j++) {
	//		cout << MAP[i][j] << " ";
	//	}
	//	cout << "\n";
	//}

	//cout << "visited\n";
	//for (int i = 0;i < N;i++) {
	//	for (int j = 0;j < M;j++) {
	//		cout << visited[i][j] << " ";
	//	}
	//	cout << "\n";
	//}

	// 5. 최대값 및 못익은 경우 체크
	result();

	

	return 0;
}

