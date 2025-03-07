/**
 * SW Expert Academy A형 모의 테스트
 * 줄기세포배양
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

// 세포 구조체
struct Cell {
	int x, y, remainTime;
	int alive; // 0 비활성 1 활성 2 사망;
};

const int dx[] = { -1, 0, 1, 0 };
const int dy[] = { 0, 1, 0, -1 };

// 무한대 범위. 최대 300시간이므로 여유있게 선언
int map[1000][1000] = { 0 };
bool used_map[1000][1000] = { 0 };

vector<Cell> cells;

int spread(int days) {
	vector<Cell> active_cells;
	vector<Cell> ces;
	while (days--) {
		active_cells.clear();
		// 1. 활성 비활성 remainTime을 감소시킴
		for (int i = 0; i < cells.size(); i++) {
			if (cells[i].alive == 2) continue;	// 사망한 세포 제거

			if (cells[i].alive == 1) {
				if (cells[i].remainTime == map[cells[i].x][cells[i].y]) {
					active_cells.push_back(cells[i]);
				}
			}

			if (--cells[i].remainTime == 0) {
				if (cells[i].alive == 1) {	// 세포 사망
					cells[i].alive = 2;
				}
				else {
					// 활성화 시킴
					cells[i].alive = 1;
					cells[i].remainTime = map[cells[i].x][cells[i].y];
				}
			}
		}
		// 2. 활성화 세포는 추가해서 번식시킴.
		ces.clear();
		for (int i = 0; i < active_cells.size(); i++) {
			for (int dir = 0; dir < 4; dir++) {	// 4방향 탐색
				int nx = active_cells[i].x + dx[dir];
				int ny = active_cells[i].y + dy[dir];

				if (used_map[nx][ny]) continue;	//이미 세포가 장악한 부분은 패스
				
				map[nx][ny] = max(map[nx][ny], active_cells[i].remainTime);	// 세포가 장악하지 않앗으면, 더 큰값을 퍼지게 함
				ces.push_back({ nx, ny, active_cells[i].remainTime, 0 }); // 새로운 칸에 비활성 세포로 추가
			}
		}

		for (Cell c : ces){
			if (used_map[c.x][c.y]) continue; // 칸을 채웠으면 패스
			
			if (map[c.x][c.y] != c.remainTime) continue;	// 값이 다르면 최댓값이 아닌 것.
			
			cells.push_back(c);	// cells에 추가시킨다.
			used_map[c.x][c.y] = 1;
		}
	}
	
	// 살아있는 총 세포 수 센 뒤 반환
	int cnt = 0;
	for (int i = 0; i < cells.size(); i++) {
		if (cells[i].alive != 2) cnt++;
	}
	return cnt;
}
int main(int argc, char** argv) {
	int T;
	cin >> T;

	for (int test_case = 1; test_case <= T; test_case++) {
		int N, M, K;
		cin >> N >> M >> K;
		
		// map init
		for (int i = 0; i < 1000; i++) {
			for (int j = 0; j < 1000; j++) {
				map[i][j] = 0;
				used_map[i][j] = 0;
			}
		}
		
		cells.clear();
		// cell init
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
                // 무한대로 배양해야하므로 중앙쪽에서 시작시키기 위함.
				cin >> map[i + 500][j + 500];
				if (map[i + 500][j + 500] > 0) {
					cells.push_back({ i + 500, j + 500, map[i + 500][j + 500], 0 });
					used_map[i + 500][j + 500] = 1;
				}
			}
		}

		cout << "#" << test_case << " " << spread(K) << "\n";

		
	}
}