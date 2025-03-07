#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <math.h>
using namespace std;
vector<char> vect1;
vector<string> vect2;
vector<int> vect3;
 
int cnt_num;
 
void to_int() {
 
    string str;
    int size = vect2.size();
    for (int i = 0; i < size; i++) {
        int num = 0;
        int total = 0;
        str = vect2.back();
 
        vect2.pop_back();
 
        for (int j = cnt_num-1; j >=0; j--) {
            if (str[j] >= '0' && str[j] <= '9')
            {
                num = str[j] - '0';
                total += num * pow(16, cnt_num-1-j);
            }
            else if(str[j]>='A' && str[j]<='F') {
                num = str[j] - 'A'+10;
                total += num * pow(16, cnt_num-1 - j);
            }
        }
        vect3.push_back(total);
         
    }
 
 
}
 
int main() {
    int T;
    char c;
    string pswd;
    string s="";
    int N, K; // N : 문자열 길이, K : K번째로 큰 수
    cin>>T;
 
    for (int testcase = 1; testcase <= T; testcase++) {
        cin >> N >> K;
        cin >> pswd;
        cnt_num = N / 4;
        for (int i = 0; i < pswd.size(); i++) {
            vect1.push_back(pswd[i]);
        }
 
        for (int r = 0; r < cnt_num; r++) {
 
            for (int j = 0; j < N; j++) {
                s += vect1[j];
                if (s.size() == cnt_num) {
                     
                    auto it = find(vect2.begin(), vect2.end(), s);
                    if (it == vect2.end()) vect2.push_back(s);
                    s.clear();
                }
            }
 
            c = vect1.back();
            vect1.pop_back();
            vect1.insert(vect1.begin(),c);
        }
        to_int();
        sort(vect3.begin(), vect3.end(), greater<>());
        cout << "#"<<testcase<<" "<< vect3[K - 1] << "\n";
        vect3.clear();
        vect1.clear();
    }
}