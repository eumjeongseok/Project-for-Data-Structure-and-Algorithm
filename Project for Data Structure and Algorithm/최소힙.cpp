#include <cstdio>
#include <iostream>
#define MAX_ELEMENT 200
using namespace std;


//���� ���� ��� Ŭ����
class HeapNode {
	int key; //key ��
public:
	HeapNode(int k = 0) : key(k) {}
	void setKey(int k) { key = k; }
	int getKey() { return key; }
	void display() { printf("%d ", key); }
};

//�ּ� ��
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
		int i = ++size; //������ �� ũ�� ��ġ���� ����(���� ������ �ڸ�)

		//Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
		while (i != 1 && key < getParent(i).getKey()) {
			//�θ� ��庸�� �ڽ��� ������ �ڽ��� �ö󰣴�. �ִ� ������ �ٲ�� �κ�
			node[i] = getParent(i);
			i /= 2;
		}
		node[i].setKey(key);
	}

	HeapNode remove() {
		if (isFull()) { return NULL; }
		HeapNode item = node[1]; //��Ʈ���(���� ���)
		HeapNode last = node[size--]; //���� ���������
		int parent = 1; //������ ����� ��ġ�� ��Ʈ�� ������
		int child = 2; //��Ʈ�� ���� �ڽ� ��ġ

		//�� Ʈ���� ����� �ʴ� ����
		while (child <= size) {
			//���� ����� �ڽ� ��� �� �� ū �ڽĳ�带 ã��, �ִ� ������ �ٲ�� �κ�
			if (child < size && getLeft(parent).getKey() > getRight(parent).getKey()) { child++; }
			//child: �� ū �ڽ� ����� �ε���

			//������ ��尡 �ڽ� ��庸�� ũ�� ==> �̵� �Ϸ�
			if (last.getKey() <= node[child].getKey()) break;

			//�ƴϸ� ==> �� �ܰ� �Ʒ��� �̵�
			node[parent] = node[child];
			parent = child;
			child *= 2;
		}
		node[parent] = last; //������ ��带 ���� ��ġ�� ����
		return item; //��Ʈ ��� ��ȯ(��, ��Ʈ ��带 �����Ѵ�.)
	}

	HeapNode find() { return node[1]; } //��Ʈ ��� ��ȯ

	void display() { //���
		for (int i = 1, level = 1; i <= size; i++) {
			if (i == level) {
				level *= 2;
			}
			node[i].display();
		}
	}
};

int main() {
	int N; //����� ����
	int K; //�켱������ ���� K��
	MinHeap heap; //�ּ� ��

	cin >> N >> K;

	for (int i = 0; i < N; i++) {
		int element;
		cin >> element;
		heap.insert(element);
	}
	heap.display(); //�켱 �Էµ� ���� �迭 �÷� ���
	printf("\n");


	for (int i = 0; i < K; i++) {
		heap.remove(); //�� ���� K���� ���� ���� ����
	}
	heap.display(); //������ �� ����� �迭 �÷� ���

	return 0;
}