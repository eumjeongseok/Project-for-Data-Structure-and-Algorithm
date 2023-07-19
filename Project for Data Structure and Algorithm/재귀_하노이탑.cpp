#include <cstdio>

//하노이 탑 알고리즘(재귀 사용)
void hanoiTower(int n, char from, char tmp, char to) {
	if (n == 1) { printf("원판 1을 %c에서 %c로 옮긴다.\n", from, to); }
	else {
		hanoiTower(n - 1, from, to, tmp);
		printf("원판 %d를 %c에서 %c로 옮긴다.\n", n, from, to);
		hanoiTower(n - 1, tmp, from, to);
	}
}

int main() {
	hanoiTower(4, 'A', 'B', 'C');
	return 0;
}

//재귀: 자기 함수를 다시 호출하는 방식
//재귀의 한계: 중복호출이 발생(재귀트리를 그리면 알 수 있음)
//하노이 탑 알고리즘의 원리: n개의 원판을 옮기는 문제는 n-1개의 원판을 옮기는 것과 같다!