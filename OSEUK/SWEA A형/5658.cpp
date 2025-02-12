/**
 * SW Expert Academy A형 모의 테스트
 * 보물상자 비밀번호
 */
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;
using ll = long long;

int N, T;

int main(int argc, char** argv)
{
	int T;
	cin >> T;

	for (int test_case = 1; test_case <= T; test_case++) {
		int N, K;
		cin >> N >> K;

		string s;
		cin >> s;
		int len = s.length();
		set<string, greater<string>> results;   // 문자열을 내림차순으로 정렬한 set 자료구조 (중복 없음)

        // len/4만큼만 회전
		for (int r = 0; r < len / 4; r++) {
			for (int i = 0; i < s.length(); i += len / 4) {
				results.insert(s.substr(i, len / 4));   // 생성 가능한 수를 set에 넣음
			}
			s = s.substr(1, s.length() - 1) + s[0]; // 회전
		}

		int idx = 1;
		string res;
        // set을 순회하며 K번째에 있는 값을 추출
		for (string str : results) {
			if (idx++ == K) res = str;
		}
		
		ll changed_num = 0;
        
        // 16진수 -> 10진수 변환
		for (int i = 0; i < res.length(); i++) {
			ll digit;

			if ('0' <= res[i] && res[i] <= '9') {
				digit = res[i] - '0';   // 숫자일 경우 0을 빼면 숫자.
			}
			else {
				digit = res[i] - 'A' + 10;  // A부터 10이므로 'A'+10을 뺀 수와 같음.
			}

			changed_num += digit * pow(16, res.length() - 1 - i);   // 1F7 = 16^2 * 1 + 16^1 * 15 + 7
		}
		
		cout << "#" << test_case << ' ';
		cout << changed_num << "\n";
	}
}