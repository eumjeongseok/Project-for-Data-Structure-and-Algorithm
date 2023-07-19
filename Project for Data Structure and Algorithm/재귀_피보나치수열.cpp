#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

//재귀를 이용한 피보나치 수열: 중복 호출 발생!
int fib(int n) {
	//Base case
	if (n == 0) { return 0; }
	if (n == 1) { return 1; }

	//Inductive case
	return (fib(n - 1) + fib(n - 2));
}

//반복을 이용한 피보나치 수열
int fibIter(int n) {
	if (n < 2) { return n; }
	else {
		int i, tmp, curr = 1, last = 0;
		for (i = 2; i <= n; i++) {
			tmp = curr;
			curr += last;
			last = tmp;
		}
		return curr;
	}
}

int main() {
	//n은 n번째 수를 나타냄

	int n;
	cin >> n;

	//n의 index가 0부터 시작하므로, 1부터 시작하려면 n-1로 입력해야 함
	cout << "재귀 형태의 반환값: " << fib(n - 1) << "\n";
	cout << "반복 형태의 반환값: " << fibIter(n - 1) << "\n";

	return 0;
}
