/**
 * BOJ 2206 벽 부수고 이동하기 문제 풀이
 */

 #include <iostream>
 #include <string>
 #include <queue>
 #include <tuple>
 
 using namespace std;
 
 #define MAX_N 1001
 
 const int dy[] = { -1, 0, 1, 0 };
 const int dx[] = { 0, 1, 0, -1 };
 
 int map[MAX_N][MAX_N] = { 0 };	// 맵
 int visited[MAX_N][MAX_N][2] = { 0 };	// 방문 여부. + 벽이 있는지 여부에 대한 방문 여부
 int N, M;
 
 // 범위 검사
 bool inRange(int y, int x) {
     return 0 < y && y <= N && 0 < x && x <= M;
 }
 
 int bfs(int y, int x) {	
     queue<tuple<int, int, int>> q;
     q.push({ y, x, 0 });
     visited[y][x][0] = 1;
 
     int dist = 1;
     while (!q.empty()) {
 
         int size = q.size();
         for (int i = 0; i < size; i++) {
             int y, x, isBroken;		// 좌표, 벽을 부쉈는 지
             tie(y, x, isBroken) = q.front();
             q.pop();
 
             // 도착 시 거리 반환
             if (y == N && x == M) return dist;
             
             for (int dir = 0; dir < 4; dir++) {
                 int ny = y + dy[dir];
                 int nx = x + dx[dir];
 
                 if (!inRange(ny, nx)) continue;
 
                 // 아직 벽을 부순적이 없고 벽을 부수려고 할 때
                 if (isBroken == 0 && map[ny][nx] == 1) {
                     q.push({ ny, nx, 1 });
                     visited[ny][nx][1] = 1;
                     continue;
                 }
 
                 if (!visited[ny][nx][isBroken] && map[ny][nx] == 0) {
                     q.push({ ny, nx, isBroken });
                     visited[ny][nx][isBroken] = 1;
                 }
             }
         }
 
         dist++;
     }
 
     // (N, M) 도착 못할 시 -1 반환
     return -1;
 }
 int main(void) {
 
     cin >> N >> M;
     
     // input
     string s;
     for (int i = 1; i <= N; i++) {
         cin >> s;
         for (int j = 1; j <= M; j++) {
             map[i][j] = s[j - 1] - '0';
         }
     }
 
     cout << bfs(1, 1) << "\n";
 
 }