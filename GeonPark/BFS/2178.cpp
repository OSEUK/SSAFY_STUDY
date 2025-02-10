#include <iostream>
#include <vector>
#include <string>
#include <deque>
using namespace std;
#define endl '\n'
//g++ algo.cpp && ./a.out

int map[103][103];
bool visited[103][103];

int main()
{
    int n, m;
    cin >> n >> m;
    string s;
    for(int i=1; i<=n; i++)
    {
        cin >> s;
        for(int j=1; j<=m; j++)
        {
            map[i][j] = s[j-1]-'0';
        }
    }
    bool flag = false;
    int dx[4] = {1, 0, 0, -1};
    int dy[4] = {0, -1, 1, 0};
    deque<pair<int, int>> d;
    d.push_back({1, 1});
    visited[1][1] = true;
    while(!d.empty())
    {
        int curx = d.front().first;
        int cury = d.front().second;
        d.pop_front();
        for(int k=0; k<4; k++)
        {
            int nx = curx + dx[k];
            int ny = cury + dy[k];
            if(nx>=1 && ny>=1 && map[ny][nx] > 0 && !visited[ny][nx])
            {
                visited[ny][nx] = true;
                map[ny][nx] += map[cury][curx];
                d.push_back({nx, ny});
                if(nx == m && ny == n)
                {
                    flag = true;
                }
            }
        }
        if(flag == true)
        {
            break;
        }
    }
    cout << map[n][m] << endl;
}