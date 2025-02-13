#include <iostream>
using namespace std;
 
int W, D, T, K;
int cnt;
int min_cnt;
int map[13][20];
 
int state_map[13][20];
 
 
void init() {
    cnt = 0;
    min_cnt = 99999;
}
void input() {
    cin >> D >> W >> K;
    for (int i = 0; i < D; i++) {
        for (int j = 0; j < W; j++) {
            cin>> map[i][j];
        }
    }
}
 
bool check_std() {
    int d; // k==1일때 히든 찾기
    int c;
    bool flag;
    for (int w = 0; w < W; w++) {
        d = 0;
        c = 1;
        flag = false;
        while (d < D-1) {
            if (map[d][w] == map[d + 1][w]) c++;
            else c = 1;
 
            if (c >= K) { flag = true;  break; }
            d++;
        }
 
        if (flag == false) return false;
    }
    return true;
 
}
void put_item(int target_d, int set) {
 
    for (int i = 0; i < W; i++) {
        state_map[target_d][i] = map[target_d][i];
        map[target_d][i] = set;
    }
 
}
void recur_state(int target_d) {
    for (int i = 0; i < W; i++) {
        map[target_d][i] = state_map[target_d][i];
    }
}
void solution(int level, int cnt_item) {
 
    if (cnt_item >= min_cnt) return;
 
    if (level == D) {
        if (check_std()) {
            cnt = cnt_item; 
            if (min_cnt > cnt) min_cnt = cnt;
        }
        return;
    }
 
    // 안 넣기
    solution(level + 1, cnt_item);
     
    // A넣기
 
    put_item(level, 0);
    solution(level + 1, cnt_item+1);
    recur_state(level);
 
    // B넣기
 
    put_item(level, 1);
    solution(level + 1, cnt_item+1);
    recur_state(level);
         
 
 
}
 
 
int main() {
    cin >> T;
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int testcase = 1; testcase <= T; testcase++) {
 
        init();
        input();
        solution(0,0);
 
        cout << "#" << testcase << " " << min_cnt << "\n";
    }
}