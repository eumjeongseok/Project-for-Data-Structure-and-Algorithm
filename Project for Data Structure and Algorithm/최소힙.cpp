#include <cstdio>
#include <iostream>
#define MAX_ELEMENT 200
using namespace std;


//힙을 위한 노드 클래스
class HeapNode {
	int key; //key 값
public:
	HeapNode(int k = 0) : key(k) {}
	void setKey(int k) { key = k; }
	int getKey() { return key; }
	void display() { printf("%d ", key); }
};

//최소 힙
class MinHeap {
	HeapNode node[MAX_ELEMENT];
	int size;

public:
	MinHeap() : size(0) {}
	bool isEmpty() { return size == 0; }
	bool isFull() { return size == MAX_ELEMENT - 1; }

	HeapNode& getParent(int i) { return node[i / 2]; }
	HeapNode& getLeft(int i) { return node[i * 2]; }
	HeapNode& getRight(int i) { return node[i * 2 + 1]; }

	void insert(int key) {
		if (isFull()) { return; }
		int i = ++size; //증가된 힙 크기 위치에서 시작(힙의 마지막 자리)

		//트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
		while (i != 1 && key < getParent(i).getKey()) {
			//부모 노드보다 자신이 작으면 자신이 올라간다. 최대 힙에서 바뀌는 부분
			node[i] = getParent(i);
			i /= 2;
		}
		node[i].setKey(key);
	}

	HeapNode remove() {
		if (isFull()) { return NULL; }
		HeapNode item = node[1]; //루트노드(꺼낼 요소)
		HeapNode last = node[size--]; //힙의 마지막노드
		int parent = 1; //마지막 노드의 위치를 루트로 생각함
		int child = 2; //루트의 왼쪽 자식 위치

		//힙 트리를 벗어나지 않는 동안
		while (child <= size) {
			//현재 노드의 자식 노드 중 더 큰 자식노드를 찾음, 최대 힙에서 바뀌는 부분
			if (child < size && getLeft(parent).getKey() > getRight(parent).getKey()) { child++; }
			//child: 더 큰 자식 노드의 인덱스

			//마지막 노드가 자식 노드보다 크면 ==> 이동 완료
			if (last.getKey() <= node[child].getKey()) break;

			//아니면 ==> 한 단계 아래로 이동
			node[parent] = node[child];
			parent = child;
			child *= 2;
		}
		node[parent] = last; //마지막 노드를 최종 위치에 저장
		return item; //루트 노드 반환(즉, 루트 노드를 제거한다.)
	}

	HeapNode find() { return node[1]; } //루트 노드 반환

	void display() { //출력
		for (int i = 1, level = 1; i <= size; i++) {
			if (i == level) {
				level *= 2;
			}
			node[i].display();
		}
	}
};

int main() {
	int N; //노드의 개수
	int K; //우선순위가 높은 K개
	MinHeap heap; //최소 힙

	cin >> N >> K;

	for (int i = 0; i < N; i++) {
		int element;
		cin >> element;
		heap.insert(element);
	}
	heap.display(); //우선 입력된 힙을 배열 꼴로 출력
	printf("\n");


	for (int i = 0; i < K; i++) {
		heap.remove(); //그 다음 K번의 삭제 연산 수행
	}
	heap.display(); //이후의 힙 모습을 배열 꼴로 출력

	return 0;
}