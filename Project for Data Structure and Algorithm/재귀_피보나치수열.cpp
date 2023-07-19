#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

//��͸� �̿��� �Ǻ���ġ ����: �ߺ� ȣ�� �߻�!
int fib(int n) {
	//Base case
	if (n == 0) { return 0; }
	if (n == 1) { return 1; }

	//Inductive case
	return (fib(n - 1) + fib(n - 2));
}

//�ݺ��� �̿��� �Ǻ���ġ ����
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
	//n�� n��° ���� ��Ÿ��

	int n;
	cin >> n;

	//n�� index�� 0���� �����ϹǷ�, 1���� �����Ϸ��� n-1�� �Է��ؾ� ��
	cout << "��� ������ ��ȯ��: " << fib(n - 1) << "\n";
	cout << "�ݺ� ������ ��ȯ��: " << fibIter(n - 1) << "\n";

	return 0;
}
