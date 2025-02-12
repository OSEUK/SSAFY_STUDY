#include<iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>

using namespace std;

struct pos {
	int y;
	int x;
	bool punch;
};

int map[1000][1000];
int dist[2][1000][1000];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	
	int dy[4] = { 1, -1, 0, 0 };
	int dx[4] = { 0, 0, 1, -1 };
	deque<pos> dq;
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < s.length(); j++) {
			map[i][j] = s[j] - '0';
		}
	}

	dq.push_back({ 0, 0, 1 });
	dist[1][0][0] = 1;
	
	while (!dq.empty()) {
		pos cur = dq.front();
		dq.pop_front();

		for (int i = 0; i < 4; i++) {
			int ny = cur.y + dy[i];
			int nx = cur.x + dx[i];

			if (ny >= 0 && nx >= 0 && ny < n && nx < m) { // 범위에 있으면
				
				if (cur.punch == 0) { //펀치를 못할 때
					if (map[ny][nx] == 0 && dist[0][ny][nx] == 0) {
						dq.push_back({ ny, nx, cur.punch });
						dist[0][ny][nx] = dist[0][cur.y][cur.x] + 1;
					}
				}

				else {
					if (map[ny][nx] == 1 && dist[0][ny][nx] == 0) {
						dq.push_back({ ny, nx, 0 });
						dist[0][ny][nx] = dist[1][cur.y][cur.x] + 1;
					}
					else if (map[ny][nx] == 0 && dist[1][ny][nx] == 0) {
						dq.push_back({ ny, nx, cur.punch });
						dist[1][ny][nx] = dist[1][cur.y][cur.x] + 1;
					}
				}

			}

		}
	}

	/*cout << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << dist[0][i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << dist[1][i][j] << " ";
		}
		cout << endl;
	}*/

	if (dist[1][n - 1][m - 1] != 0 && dist[0][n - 1][m - 1] != 0) {
		cout << min(dist[1][n - 1][m - 1], dist[0][n - 1][m - 1]) << endl;
	}
	else if(dist[1][n - 1][m - 1] == 0 && dist[0][n - 1][m - 1] == 0){
		cout << -1 << endl;
	}
	else {
		cout << max(dist[1][n - 1][m - 1], dist[0][n - 1][m - 1]) << endl;
	}


	return 0;
}