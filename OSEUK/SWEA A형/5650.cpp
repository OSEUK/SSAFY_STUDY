/**
 * SW Expert Academy A형 모의 테스트
 * 핀볼 게임
 */


#include <iostream>
#include <vector>

using namespace std;
using pi = pair<int, int>;

// 상 우 하 좌
const int dy[] = { -1, 0, 1, 0 };
const int dx[] = { 0, 1, 0, -1 };

// 핀볼의 현재 방향의 블럭 별 바꿀 방향 배열
const int dir_change[6][4]{
	{2, 3, 0, 1},	// 벽일 때 
	{2, 3, 1, 0},	// 1번 블럭의 각 방향일 때 변환 ...
	{1, 3, 0, 2},	
	{3, 2, 0, 1},
	{2, 0, 3, 1},
	{2, 3, 0, 1}
};

// 핀볼
struct Ball {
	int y, x, dir;
};

int N;
int result;

// 범위 계산
bool inRange(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < N;
}

vector<vector<pi>> warmHole;	// 웜홀 위치 따로 관리
int map[100][100] = { 0 };		// 맵 초기ㅗ하

int go(Ball& ball) {
	int cnt = 0;
	pi start_pos = { ball.y, ball.x };	// 시작 위치 저장

	while (1) {
		int nx = ball.x + dx[ball.dir];
		int ny = ball.y + dy[ball.dir];
		
		if (!inRange(ny, nx)) {

			// 벽이면 방향만 뒤집음.
			ny = ball.y;
			nx = ball.x;
			ball.dir = dir_change[0][ball.dir];
			cnt++;

			if (map[ny][nx] == -1) return cnt;	// 블랙홀 만나면 종료
			if (ny == start_pos.first && nx == start_pos.second) return cnt;	// 시작 위치 만나면 종료

		}

		// 블럭이 있으면 방향을 바꿈.
		if (1 <= map[ny][nx] && map[ny][nx] <= 5) {
			ball.dir = dir_change[map[ny][nx]][ball.dir];

			cnt++;
		}

		// 웜홀이 있으면 순간이동을 함.
		if (6 <= map[ny][nx] && map[ny][nx] <= 10) {
			pi curr = warmHole[map[ny][nx]][0];
			if (curr == make_pair(ny, nx)) {
				curr = warmHole[map[ny][nx]][1];
			}

			ny = curr.first;
			nx = curr.second;
		}

		// 종료 조건
		if (map[ny][nx] == -1) return cnt;
		if (ny == start_pos.first && nx == start_pos.second) return cnt;
		
		// 이동
		ball.x = nx;
		ball.y = ny;
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	cin >> T;
	
	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N;

		result = -1;

		warmHole.clear();
		
		warmHole.resize(11);

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				if (map[i][j] >= 6) warmHole[map[i][j]].push_back({ i, j });	// 웜홀 저장
			}
		}

		// 모든 위치에서 4가지 방향으로 슛
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] != 0) continue; // 0인 곳에서만 출발

				for (int dir = 0; dir < 4; dir++) {
					Ball b = { i, j, dir };
					result = max(result, go(b));
				}
			}
		}

		cout << "#" << test_case << ' ' << result << "\n";

	}
	return 0;
}