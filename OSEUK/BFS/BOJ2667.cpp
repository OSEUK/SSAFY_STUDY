#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;
using pi = pair<int, int>;

const int dx[] = { -1, 0, 1, 0 };
const int dy[] = { 0, 1, 0, -1 };

int N;
vector<vector<int>> map;
vector<vector<int>> visited;

bool inRange(int x, int y) {
	return 0 <= x && x < N && 0 <= y && y < N;
}

int bfs(int x, int y) {
	queue<pi> q;
	q.push({ x, y });
	visited[x][y] = 1;
	
	int cnt = 0;
	while (!q.empty()) {
		pi curr = q.front();
		q.pop();
		
		cnt++;

		for (int dir = 0; dir < 4; dir++) {
			int nx = curr.first + dx[dir];
			int ny = curr.second + dy[dir];

			if (!inRange(nx, ny) || visited[nx][ny] == 1 || map[nx][ny] == 0) continue;
			
			q.push({ nx, ny });
			visited[nx][ny] = 1;
		}
	}
	
	return cnt;
}
int main(void) {
	
	cin >> N;
	
	map.resize(N, vector<int>(N, 0));
	visited.resize(N, vector<int>(N, 0));

	for (int i = 0; i < N; i++) {
		string s;
		cin >> s;
		
		for (int j = 0; j < s.length(); j++) {
			map[i][j] = s[j] - '0';
		}
	}
	
	vector<int> group_size;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!visited[i][j] && map[i][j] == 1) {
				group_size.push_back(bfs(i, j));
			}
		}
	}

	cout << group_size.size() << "\n";
	sort(group_size.begin(), group_size.end());

	for (int num : group_size) {
		cout << num << "\n";
	}

	return 0;

}