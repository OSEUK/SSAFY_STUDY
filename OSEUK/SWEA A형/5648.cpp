/**
 * SW Expert Academy A형 모의 테스트
 * 원자 소멸 시뮬레이션
 */

#include<iostream>
#include <cstring>
#include <vector>
#include <tuple>

using namespace std;
using pi = pair<int, int>;

const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { 1, -1, 0, 0 };

// 원자 구조체. 
struct Atom {
	int y, x, dir, power;
	bool alive = true;
}atom[1000];

int N;
int pos_count[4001][4001] = { 0 }; // 0.5초 충돌 알기 위해 2배더 크게.

vector<pi> collision;

bool inRange(int y, int x) {
	return 0 <= y && y <= 4000 && 0 <= x && x <= 4000;
}

int simulate() {
	int cnt = 0; // 최대 반복 횟수 찾기
	int alive_count = N;	// 몇명 살아있는지
	int total_power = 0;	// 총 폭발 횟수

	while (alive_count > 1 && cnt <= 4000) {
		
		for (int i = 0; i < N; i++) {
			if (!atom[i].alive) continue;	// 폭발되면 continue;

			pos_count[atom[i].y][atom[i].x]--;	// 위치 이동할거니까 현재좌표 --;

			int nx = atom[i].x + dx[atom[i].dir];
			int ny = atom[i].y + dy[atom[i].dir];

			// 범위 벗어나면 더이상 움직이지 않게 함.
			if (!inRange(ny, nx)) {	
				atom[i].alive = false;
				alive_count--;
				continue;
			}

			// 해당 원자를 다음 좌표로 이동시킴
			pos_count[ny][nx]++;
			atom[i].x = nx;
			atom[i].y = ny;
		}
				
        // 충돌한 원자를 collision 배열에 추가.
		for (int i = 0; i < N; i++) {
			if (!atom[i].alive) continue; // 죽은 원자 무시

			if (pos_count[atom[i].y][atom[i].x] >= 2) {
				total_power += atom[i].power;
				collision.push_back({ atom[i].y, atom[i].x});
				alive_count--;
				atom[i].alive = false;  // 충돌하면 사망
			}
		}

        // 충돌한 원자들의 좌표값을 줄임
		for (auto& pos : collision) {
			pos_count[pos.first][pos.second]--;
		}
		collision.clear();

		cnt++;
	}

	return total_power;
}

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;

	for (int test_case = 1; test_case <= T; test_case++) {
		cin >> N;

		memset(pos_count, 0, sizeof(pos_count));
		for (int i = 0; i < N; i++) {
			atom[i].alive = true;
		}
		for (int i = 0; i < N; i++) {
			int x, y, dir, K;
			cin >> x >> y >> dir >> K;
			atom[i] = { (y + 1000) * 2, (x + 1000) * 2, dir, K};    // 좌표 2배 이동동
			pos_count[(y + 1000) * 2][(x + 1000) * 2]++;
		}

		cout << "#" << test_case << ' ' << simulate() << "\n";
	}
}