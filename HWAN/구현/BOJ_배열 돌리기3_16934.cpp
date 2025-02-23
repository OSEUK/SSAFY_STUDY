#include <iostream>

using namespace std;

int map[100][100];
int tmap[100][100];
int N, M;
int cmd;
int cmdcnt;

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void rotate(int cmd) {
	int div2_N = N / 2;
	int div2_M = M / 2;

	if (cmd == 1) { // 상하반전

		for (int row = 0; row < N; row++) {
			for (int col = 0; col < M; col++) {
				tmap[N-row -1][col] = map[row][col];
			}
		}
		for (int row = 0; row < N; row++) {
			for (int col = 0; col < M; col++) {
				map[row][col] = tmap[row][col];
			}
		}
	}
	else if (cmd == 2) //좌우반전
	{
		for (int row = 0; row < N; row++) {
			for (int col = 0; col < M; col++) {
				tmap[row][M-col-1] = map[row][col];
			}
		}
		for (int row = 0; row < N; row++) {
			for (int col = 0; col < M; col++) {
				map[row][col] = tmap[row][col];
			}
		}
	}
	else if (cmd == 3) //시계 90
	{
		for (int row = 0; row < N; row++) {
			for (int col = 0; col < M; col++) {
				tmap[col][N - row - 1] = map[row][col];
			}
		}
		swap(&N, &M);
		for (int row = 0; row < N; row++) {
			for (int col = 0; col < M; col++) {
				map[row][col] = tmap[row][col];
			}
		}

	}
	else if (cmd == 4) //반시계 90
	{
		for (int row = 0; row < N; row++) {
			for (int col = 0; col < M; col++) {
				tmap[M-col-1][row] = map[row][col];
			}
		}
		swap(&N, &M);
		for (int row = 0; row < N; row++) {
			for (int col = 0; col < M; col++) {
				map[row][col] = tmap[row][col];
			}
		}
	}
	else if (cmd == 5) // 1->2 ~ 4->1
	{
		// 1 | 2
		// -----
		// 4 | 3

		for (int row = 0; row < div2_N; row++) { //1
			for (int col = 0; col < div2_M; col++) {
				tmap[row][div2_M + col] = map[row][col];
			}
		}
		for (int row = 0; row < div2_N; row++) { //2
			for (int col = div2_M; col < M; col++) {
				tmap[div2_N+row][col] = map[row][col];
			}
		}
		for (int row = div2_N; row < N; row++) { //3
			for (int col = div2_M; col < M; col++) {
				tmap[row][col-div2_M] = map[row][col];
			}
		}
		for (int row = div2_N; row < N; row++) { //4
			for (int col = 0; col < div2_M; col++) {
				tmap[row-div2_N][col] = map[row][col];
			}
		}

		for (int row = 0; row < N; row++) {
			for (int col = 0; col < M; col++) {
				map[row][col] = tmap[row][col];
			}
		}
	}
	else if (cmd == 6) {  // 1->4 ~ 2->1
		// 1 | 2
		// -----
		// 4 | 3
		for (int row = 0; row < div2_N; row++) { //1
			for (int col = 0; col < div2_M; col++) {
				tmap[div2_N+row][col] = map[row][col];
			}
		}
		for (int row = 0; row < div2_N; row++) { //2
			for (int col = div2_M; col < M; col++) {
				tmap[row][col-div2_M] = map[row][col];
			}
		}
		for (int row = div2_N; row < N; row++) { //3
			for (int col = div2_M; col < M; col++) {
				tmap[row -div2_N][col] = map[row][col];
			}
		}
		for (int row = div2_N; row < N; row++) { //4
			for (int col = 0; col < div2_M; col++) {
				tmap[row][div2_M + col] = map[row][col];
			}
		}

		for (int row = 0; row < N; row++) {
			for (int col = 0; col < M; col++) {
				map[row][col] = tmap[row][col];
			}
		}
	}

}

int main() {

	cin >> N >> M >> cmdcnt;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	for (int cnt = 0; cnt < cmdcnt; cnt++) {
		cin >> cmd;
		rotate(cmd);
	}

	for (int row = 0; row < N; row++) {
		for (int col = 0; col < M; col++) {
			cout << map[row][col] << " ";
		}
		cout << "\n";
	}


}