#include <iostream>
#include <vector>
#include <string>
#include<algorithm>
#include <queue>
using namespace std;

struct Data {
	string name;
	priority_queue<int> pq;
};
string name;
bool find_name(Data d) {
	return d.name == name;
}

long long int total;
int main() {

	int cmd;
	int N;
	string info;
	vector<Data> vect;
	cin >> N;
	int k;
	int num;
	for (int i = 0; i < N; i++) {
		cin >> cmd >> name;

		if (cmd == 1) {  // 정보 사기
			cin >> k;
			auto it = find_if(vect.begin(), vect.end(), find_name); // 벡터 내 같은 이름 함수 찾음
			if (it == vect.end()) { //못찾았을 시
				vect.push_back({ name });
			}

			it = find_if(vect.begin(), vect.end(), find_name);
			
			for (int j = 0; j < k; j++) {
				cin >> num;
				it->pq.push(num);
			}


		}
		else {	//정보 팔기, cmd ==2 
			int cnt;
			cin >> cnt;
			auto it = find_if(vect.begin(), vect.end(), find_name);

			if (it == vect.end()); //정보 없으면 넘김
			else {

				if (it->pq.empty());
				else {
					while (cnt--) {
						long long int val = it->pq.top();
						it->pq.pop();
						total += val;

						if (it->pq.empty())break;

					}
				}

			}
		}

	}
	cout << total;

}