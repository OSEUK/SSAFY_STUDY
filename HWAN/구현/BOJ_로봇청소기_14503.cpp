#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct state {
	int x;
	int y;
	int dir;
};
int N, M;
int ans;
int map[51][51];
int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1};

bool inRange(int x, int y) {
	return 0 <= x && 0 <= y && x < N && y < M;
}
void solution(int s_x, int s_y, int s_d) {
	queue<state> Q;
	Q.push({ s_x,s_y,s_d });
	while (1)
	{
		auto cur = Q.front(); Q.pop();
		//1번 동작
		if (map[cur.x][cur.y] == 0) { 
			map[cur.x][cur.y] = 2;  // 2: 청소한 상태
		} 

		int nx, ny;
		bool check = false;
		for (int dir = 0; dir < 4; dir++) { //주변 청소 상태 파악
			nx = cur.x + dx[dir];
			ny = cur.y + dy[dir];

			if (!inRange(nx, ny))continue;
			if (map[nx][ny] == 0) check = true; // 청소 안한 곳이 있다!
		}

		if (check) {			//청소 안한 곳이 있는 경우(3번)
			int ndir = cur.dir;

			while (1) {
				ndir--; //반시계방향 회전
				if (ndir < 0) ndir += 4;

				nx = cur.x + dx[ndir];
				ny = cur.y + dy[ndir];

				if (map[nx][ny] == 0) {
					Q.push({ nx,ny,ndir });
					break;
				}
			}
		}
		else {	//청소 안한 곳이 없는 경우(2번)
			int back;
			back = (cur.dir + 2) % 4; //후진
			nx = cur.x + dx[back];
			ny = cur.y + dy[back];

			if (map[nx][ny] == 1) break; //후진했을 때 벽이 있으면 작동 중지
			else Q.push({ nx,ny,cur.dir });	//벽이 없으면 1번으로 돌아가기
		}

	}
	
}

int main() {
	cin >> N >> M;
	
	int start_x, start_y, start_dir;
	cin >> start_x >> start_y >> start_dir;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			// 0: 청소x , 1:벽, 2:청소o
			cin >> map[i][j];   
		}
	}
	
	solution(start_x, start_y, start_dir);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 2)ans++;
		}
	}
	cout << ans;
}