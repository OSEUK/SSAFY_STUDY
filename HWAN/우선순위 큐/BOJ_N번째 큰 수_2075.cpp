#include <iostream>
#include <vector>
#include <string>
#include<algorithm>
#include <queue>
using namespace std;
priority_queue<int, vector<int>, greater<int>> pq;
int main() {
    int N;
    cin >> N;
    int num;
    int top;
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    for (int i = 0; i < N; i++) {
        cin >> num;
        pq.push(num);
    }
    top = pq.top();
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> num;

            if (num > top) {
                pq.pop();
                pq.push(num);
                top = pq.top();
            }
        }
    }


    cout << top;

}