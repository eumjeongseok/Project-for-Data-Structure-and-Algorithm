#include <queue>
#include <functional> //�ּ� �� ��� ��
using namespace std;

//�ִ� ��: priority_queue<int> maxHeap; (�⺻ ����, less than operator)
//�ּ� ��: priority_queue<int, vector<int>, greater<int>> minHeap; (greater than operator)

//�߰� ����: push()
//���� ����: top()���� �� ���� �� pop()
//�ٸ� ���� ����, �̰͸�ŭ�� �� ����...! (������ ����� �ڵ�!!!)

//STL�� �̿��Ͽ� �������� ����, �ִ��� ���
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

//STL�� �̿��Ͽ� �������� ����, �ּ��� ���
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
	//�� �κ��� ���翡 ����� �Ф�
	//�׷��� �׳� �׽�Ʈ ���α׷����� ���ݸ� �����߽��ϴ�...

	priority_queue<int> maxheap;
	priority_queue<int, vector<int>, greater<int>> minheap;
	int data[10];

	//�������� ������ ����
	for (int i = 0; i < 10; i++) { data[i] = rand() % 100; }

	//���� �� ��� ���
	printf("\n���� ��: ");
	for (int i = 0; i < 10; i++) { printf("%3d", data[i]); }

	//�� ����
	heapSortDec(data, 10);

	//���� �� ��� ���
	printf("\n���� ��: ");
	for (int i = 0; i < 10; i++) { printf("%3d", data[i]); }
	printf("\n");

	//==========================================================
	//�������� ������ ����
	for (int i = 0; i < 10; i++) { data[i] = rand() % 100; }

	//���� �� ��� ���
	printf("\n���� ��: ");
	for (int i = 0; i < 10; i++) { printf("%3d", data[i]); }

	//�� ����
	heapSortInc(data, 10);

	//���� �� ��� ���
	printf("\n���� ��: ");
	for (int i = 0; i < 10; i++) { printf("%3d", data[i]); }
	printf("\n");

	return 0;
}