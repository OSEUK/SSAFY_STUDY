/**
 * SW Expert Academy A형 모의 테스트
 * 벽돌 깨기
 */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

using pi = pair<int, int>;

const int dx[] = { -1, 0, 1, 0 };
const int dy[] = { 0, 1, 0, -1 };

int result;
// 범위 검사
bool inRange(int x, int y, int h, int w) {
	return 0 <= x && x < h && 0 <= y && y < w;
}

// 남아있는 벽돌의 개수를 반환하는 함수
int check(vector<vector<int>> map, int H, int W) {
	int cnt = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (map[i][j] > 0) {
				cnt++;
			}
		}
	}

	return cnt;
}

// 구슬을 떨군다.
vector<vector<int>> drop(vector<vector<int>>& map, int idx) {
	vector<vector<int>> visited(map.size(), vector<int>(map[0].size(), 0));
	int h = 0;
	// 블럭 만날 때까지 내려감
	while (inRange(h, idx, map.size(), map[0].size())) {
		if (map[h][idx] > 0) {
			break;
		}
		h++;
	}

	// 블럭 못만나면 return
	if (!inRange(h, idx, map.size(), map[0].size())) {
		return visited;
	}

	//만난다면 bfs
	queue<pi> q;
	q.push({ h, idx });
	visited[h][idx] = 1;

	while (!q.empty()) {
		pi curr = q.front();
		q.pop();

		int x = curr.first;
		int y = curr.second;

        // map[x][y] 만큼 한번에 bfs에 넣음. 크레이지아케이드 물풍선마냥
		for (int i = 1; i < map[x][y]; i++) {
			for (int dir = 0; dir < 4; dir++) {
				int nx = x + dx[dir] * i;
				int ny = y + dy[dir] * i;

				if (!inRange(nx, ny, map.size(), map[0].size()) || visited[nx][ny] || map[nx][ny] == 0) continue;

				q.push({nx, ny});
				visited[nx][ny] = 1;
			}
		}
	}
	return visited;
}

// 폭파된 자리를 지운다.
void clean(vector<vector<int>>& visited, vector<vector<int>>& new_map) {
	for (int i = 0; i < visited.size(); i++) {
		for (int j = 0; j < visited[0].size(); j++) {
			if (visited[i][j]) {
				new_map[i][j] = 0;
			}
		}
	}
}

void move_to_bottom(vector<vector<int>>& map) {
	for (int k = 0; k < map[0].size(); k++) {  // 각 열에 대해
		vector<int> temp;  // 해당 열의 숫자들을 저장할 벡터

		// 위에서부터 숫자들을 순서대로 저장
		for (int i = 0; i < map.size(); i++) {
			if (map[i][k] > 0) {
				temp.push_back(map[i][k]);
				map[i][k] = 0;
			}
		}

		// 아래서부터 채우기
		int idx = map.size() - 1;
		for (int i = temp.size() - 1; i >= 0; i--) {
			map[idx--][k] = temp[i];
		}
	}
}

// 디버깅 위한 print
void print(vector<vector<int>>& new_map) {
	for (int i = 0; i < new_map.size(); i++) {
		for (int j = 0; j < new_map[0].size(); j++) {
			cout << new_map[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "---------" << "\n";
}

// 구슬 경우의 수 별로 폭파시킴.
void dfs(vector<vector<int>> map, int level, int N) {
    
    // 벽돌을 N개 떨어뜨렸다면, 남은 벽돌 검사
	if (level == N) {
		result = min(result, check(map, map.size(), map[0].size()));
		return;
	}

	for (int i = 0; i < map[0].size(); i++) {
		vector<vector<int>> new_map = map;  // 복사
		vector<vector<int>> visited = drop(new_map, i); // 떨궈서 한번에 벽돌 제거 
		clean(visited, new_map);    // 폭파된 자리 제거
		move_to_bottom(new_map);    // 폭발 된 후 전부 밑으로 내림.


		dfs(new_map, level + 1, N); // 다음 벽돌 제거하러 이동.
	}
}
int main(void)
{
	int T;
	cin >> T;

	for (int test_case = 1; test_case <= T; test_case++) {
		int N, W, H;
		cin >> N >> W >> H;
		
		vector<vector<int>> map(H, vector<int>(W, 0));

		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cin >> map[i][j];
			}
		}

		result = INT_MAX;

		dfs(map, 0, N);
		
		cout << "#" << test_case << " " << result << "\n";
	}
	
	return 0;
}