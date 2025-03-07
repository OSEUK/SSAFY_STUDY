#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int K, N;
vector<int> ans;

int cut(int dis) {
	int ret = 0;
	for (int i = 0;i < K;i++) {
		ret += ans[i] / dis;
	}
	return ret;
}

int search() {
	long long st = 0;
	long long en = ans[K-1];

	while (st <= en) {
		long long idx = (st + en) / 2;
		int num = cut(idx);
		if (num < N) en = idx - 1;
		if (num >= N) st = idx + 1;
	}
	
	return en;
}

int main() {

	cin >> K >> N;
	ans.resize(K);
	for (int i = 0;i < K;i++) {
		cin >> ans[i];
	}
	sort(ans.begin(), ans.end());

	int result = search();

	cout << result;
	return 0;
}