#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
int T;
int K;
int sum;
 
int magnet_state_before_rotate[4][8];
vector<int> magnet[4];
 
int dir;
int target_magnet;
 
 
 
void init() {
    sum = 0;
    for (int i = 0; i < 4; i++) {
        magnet[i].resize(0, 0);
    }
     
}
void input() {
    int num;
    cin >> K;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            cin >> num;
            magnet[i].push_back(num);
            magnet_state_before_rotate[i][j] = num;
        }
    }
}
 
void  update_state(int index, int type) {
    int temp;
    if (type == 1) { //시계 방향 ->
        temp = magnet[index].back();
        magnet[index].pop_back();
        magnet[index].insert(magnet[index].begin(), temp);
    }
    else if (type == -1) { //반시계방향 <-
        temp = magnet[index].front();
        magnet[index].erase(magnet[index].begin());
        magnet[index].push_back(temp);
    }
 
}
 
void rotate(int setType) {
 
    update_state(target_magnet, setType);
 
    // 같으면 멈춤, 다르면 반대로 회전
    //오른쪽
    int setRtype = setType;
    int setLtype = setType;
 
    for (int i = target_magnet; i < 3; i++) { //범위 확인
        if (magnet_state_before_rotate[i][2] != magnet_state_before_rotate[i + 1][6])
        {
            if (setRtype == 1) { setRtype = -1; update_state(i + 1, setRtype);}
            else if (setRtype == -1) { setRtype = 1; update_state(i + 1, setRtype); }
            continue;
        }
        break;
    }
    //왼쪽
 
    for (int i = target_magnet; i > 0; i--) {
        if (magnet_state_before_rotate[i][6] != magnet_state_before_rotate[i - 1][2])
        {
            if (setLtype == 1) { setLtype = -1; update_state(i - 1, setLtype); }
            else if (setLtype == -1) { setLtype = 1; update_state(i - 1, setLtype); }
            continue;
        }
        break;
    }
 
 
    //전체 상태 업데이트
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            magnet_state_before_rotate[i][j] = magnet[i][j];
        }
    }
}
 
void calc_total() {
 
    for (int i = 0; i < 4; i++) {
        if (magnet[i][0] == 0) sum += 0;
        else if (magnet[i][0] == 1)sum += pow(2, i);
    }
}
int main() {
 
    cin >> T;
    for (int testcase = 1; testcase <= T; testcase++) {
 
        init();
        input();
 
 
        for (int i = 0; i < K; i++) {
            cin >> target_magnet >> dir;
            target_magnet--;
            rotate(dir);
        }
        calc_total();
         
 
        cout << "#" << testcase << " " << sum<<"\n";
    }
}