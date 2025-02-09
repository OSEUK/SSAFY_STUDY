#include<iostream>
#include<algorithm>
#include<queue>
#include<string>

using namespace std;

vector<vector<int>> MAP;       // 맵
vector<vector<int>> dist;	   // 방문확인
vector<vector<int>> visited;   // 각 위치의 거리 정보
int N, M;					   // 맵 범위

const int mov[2][4]{
	{0,0,-1,1},
	{-1,1,0,0}
};

int in_range(int y, int x) {
	return y >= 0 && y < N && x >= 0 && x < M;
}

void bfs(int y, int x) {
	// Queue생성
	queue<pair<int, int>> Q;
	// 처음 위치 입력
	Q.push({y,x});
	dist[y][x] = 1;
	visited[y][x] = 1;

	while (!Q.empty()) {
		pair<int, int> cur = Q.front();
		Q.pop();

		for (int i = 0;i < 4;i++) {
			int dy = cur.first + mov[0][i];
			int dx = cur.second + mov[1][i];
			if (!in_range(dy, dx) || visited[dy][dx] == 1 || MAP[dy][dx] == 0) continue;
			Q.push({ dy,dx });
			dist[dy][dx] = dist[cur.first][cur.second] + 1;
			visited[dy][dx] = 1; // 큐에 넣을때 마다 방문확인 관련 참고 https://djm03178.tistory.com/31
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	// 1. 맵 크기 입력
	cin >> N >> M;

	// 2. 맵 정보 입력
	MAP.resize(N, vector<int>(M, 0));
	visited.resize(N, vector<int>(M, 0));
	dist.resize(N, vector<int>(M, 0));
	string input;
	for (int i = 0;i < N;i++) {
		cin >> input;
		for (int j = 0;j < input.length();j++) {
			MAP[i][j] = input[j] - '0';
		}
	}

	// 3. bfs
	bfs(0, 0);

	// 4. 결과 확인
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

	//cout << "distance\n";
	//for (int i = 0;i < N;i++) {
	//	for (int j = 0;j < M;j++) {
	//		cout << dist[i][j] << " ";
	//	}
	//	cout << "\n";
	//}
	//5. 도착지까지 거리 출력
	cout << MAP[N - 1][M - 1];

	return 0;
}