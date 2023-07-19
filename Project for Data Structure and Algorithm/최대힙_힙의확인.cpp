#include <cstdio>
#include <iostream>
#define MAX_ELEMENT 200
using namespace std;

bool isHeap = true; //������ �ƴ��� �˻��ϴ� ���

//���� ���� ��� Ŭ����
class HeapNode {
	int key; //key ��
public:
	HeapNode(int k = 0) : key(k) {}
	void setKey(int k) { key = k; }
	int getKey() { return key; }
	void display() { printf("%d ", key); }
};

//�ִ� ��
class MaxHeap {
	HeapNode node[MAX_ELEMENT];
	int size; //����� ����

public:
	MaxHeap() : size(0) {}
	bool isEmpty() { return size == 0; }
	bool isFull() { return size == MAX_ELEMENT - 1; } //199���� �� ��ȭ ����

	HeapNode& getParent(int i) { return node[i / 2]; }
	HeapNode& getLeft(int i) { return node[i * 2]; }
	HeapNode& getRight(int i) { return node[i * 2 + 1]; }

	//�Է� ����(UpHeap): ���ο� ��带 ������ �������� ���� �θ� ��� ������ �ö���� ��
	void insert(int key) {
		if (isFull()) { return; }
		int i = ++size; //������ �� ũ�� ��ġ���� ����(���� ������ �ڸ�)

		//Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
		while (i != 1 && key > getParent(i).getKey()) {
			//�θ� ��庸�� �ڽ��� ũ�� �ڽ��� �ö󰣴�.
			node[i] = getParent(i); //�θ� ��带 �� �� �������.

			isHeap = false;
			//�߰��� �κ�
			//insert�� �� ���̶� �ϸ� input�� ����Ž��Ʈ���� ���� �ƴ�.

			i /= 2;
		} //i�� 1�� ������ �ݺ�
		node[i].setKey(key); //���� ��ġ�� Ű �Է�
	}

	//���� ����(DownHeap): ���� ū Ű ���� ���� ��� ����
	//���� �� ������ ������ �� ������ �����ϵ��� ��
	HeapNode remove() {
		if (isFull()) { return NULL; }
		HeapNode item = node[1]; //��Ʈ���(���� ���)
		HeapNode last = node[size--]; //���� ���������
		int parent = 1; //������ ����� ��ġ�� ��Ʈ�� ������, �����δ� ����
		int child = 2; //��Ʈ�� ���� �ڽ� ��ġ

		//�� Ʈ���� ����� �ʴ� ����
		while (child <= size) {
			//���� ����� �ڽ� ��� �� �� ū �ڽĳ�带 ã��, ������ �ڽ����� �̵�
			if (child < size && getLeft(parent).getKey() < getRight(parent).getKey()) { child++; }
			//child: �� ū �ڽ� ����� �ε���

			//������ ��尡 �ڽ� ��庸�� ũ�� ==> �̵� �Ϸ�
			if (last.getKey() >= node[child].getKey()) break;

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
	MaxHeap heap;

	int N; //����� ����
	cin >> N;

	for (int i = 0; i < N; i++) {
		int element;
		cin >> element;
		heap.insert(element); //���� ��� �Է�
	}

	//���
	if (isHeap == false) { printf("NO"); } //���� �ƴϸ� No ���
	else { printf("YES"); } //���̸� Yes ���

	return 0;
}