#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
int N, M;
vector<vector<int>> map;
vector<vector<vector<int>>> visited;
int dis=-1;
struct state {
    int X;
    int Y;
    int item;
    int dist;
};

bool inRange(int x, int y) {
    return 0 <= x && 0 <= y && x < N && y < M;
}
//벽 1개까지 부수기 가능...
int main()
{

    cin >> N >> M;
    string str;
    queue<state> Q;
    map.resize(N, vector<int>(M, 0));
    visited.resize(N, vector<vector<int>>(M, vector<int>(2, 0)));

    for (int i = 0; i < N; i++) {
        cin >> str;
        int k = 0;
        for (int c = 0; c < str.size(); c++) {
            map[i][k++] = str[c] - '0';
        }
    }

    Q.push({ 0,0,1,0 });
    visited[0][0][1] = 1;
    while (!Q.empty()) {
        auto cur = Q.front(); Q.pop();

        if (cur.X == N - 1 && cur.Y == M - 1)
        {
            dis = cur.dist +1;
            break;
        }

        int nx, ny, ns, nd;
        for (int dir = 0; dir < 4; dir++) {
            nx = cur.X + dx[dir];
            ny = cur.Y + dy[dir];
            ns = cur.item;
            nd = cur.dist + 1;

            if (!inRange(nx, ny))continue;
            if (ns < 0) continue;
            if (visited[nx][ny][ns]) continue;

            if (map[nx][ny]) {
                if (ns == 1)
                {
                    Q.push({ nx, ny, ns - 1, nd });
                    visited[nx][ny][ns-1] = 1;
                }
                else continue;
               
            }
            else {
                Q.push({ nx, ny, ns, nd });
                visited[nx][ny][ns] = 1;
            }
          
        }
    }

    cout << dis;

}