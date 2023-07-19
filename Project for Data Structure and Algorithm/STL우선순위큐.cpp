#include <queue>
#include <functional> //최소 힙 사용 시
using namespace std;

//최대 힙: priority_queue<int> maxHeap; (기본 설정, less than operator)
//최소 힙: priority_queue<int, vector<int>, greater<int>> minHeap; (greater than operator)

//추가 연산: push()
//삭제 연산: top()으로 값 복사 후 pop()
//다른 것은 몰라도, 이것만큼은 꼭 알자...! (굉장히 깔끔한 코드!!!)

//STL을 이용하여 내림차순 정렬, 최대힙 사용
void heapSortDec(int a[], int n) {
	priority_queue<int> maxHeap;
	for (int i = 0; i < n; i++) {
		maxHeap.push(a[i]);
	}
	for (int i = 0; i < n; i++) {
		a[i] = maxHeap.top();
		maxHeap.pop();
	}
}

//STL을 이용하여 오름차순 정렬, 최소힙 사용
void heapSortInc(int a[], int n) {
	priority_queue<int, vector<int>, greater<int>> minHeap;
	for (int i = 0; i < n; i++) {
		minHeap.push(a[i]);
	}
	for (int i = 0; i < n; i++) {
		a[i] = minHeap.top();
		minHeap.pop();
	}
}

int main() {
	//이 부분은 교재에 없어요 ㅠㅠ
	//그래서 그냥 테스트 프로그램에서 조금만 변형했습니다...

	priority_queue<int> maxheap;
	priority_queue<int, vector<int>, greater<int>> minheap;
	int data[10];

	//랜덤으로 데이터 생성
	for (int i = 0; i < 10; i++) { data[i] = rand() % 100; }

	//정렬 전 결과 출력
	printf("\n정렬 전: ");
	for (int i = 0; i < 10; i++) { printf("%3d", data[i]); }

	//힙 정렬
	heapSortDec(data, 10);

	//정렬 후 결과 출력
	printf("\n정렬 후: ");
	for (int i = 0; i < 10; i++) { printf("%3d", data[i]); }
	printf("\n");

	//==========================================================
	//랜덤으로 데이터 생성
	for (int i = 0; i < 10; i++) { data[i] = rand() % 100; }

	//정렬 전 결과 출력
	printf("\n정렬 전: ");
	for (int i = 0; i < 10; i++) { printf("%3d", data[i]); }

	//힙 정렬
	heapSortInc(data, 10);

	//정렬 후 결과 출력
	printf("\n정렬 후: ");
	for (int i = 0; i < 10; i++) { printf("%3d", data[i]); }
	printf("\n");

	return 0;
}