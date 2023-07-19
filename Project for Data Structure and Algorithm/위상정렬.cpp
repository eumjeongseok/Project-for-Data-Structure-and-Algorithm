//���� ����(topologocal sort)?
//���� �׷����� �� �����鿡 ���ؼ�, ���� ������ �������� �����鼭 ��� ������ �����ϴ� �ä�

//���� ����(topological order)?
//��ü ���� ���� �������� ������ �����Ǵ� ����
//���� ������ 0�� ������ �����Ͽ�, ���⿡ ����� ��� ���� ����
//���� ������ 0�� ������ ���� ==> ����Ŭ�� ����!

//���� ���İ� ���� ������ ���� �� �����Ѵ�.

#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define MAX_VTXS 256
using namespace std;
const int MAX_STACK_SIZE = 20;

//���� ����Ʈ�� �̿��� �׷����� ���� Ŭ������� �׽�Ʈ ���α׷�
class Node { //��� Ŭ����
protected:
	int id; //������ id
	Node* link; //���� ����� ������

public:
	Node(int i, Node* l = NULL) : id(i), link(l) {}
	~Node() { if (link != NULL) { delete link; } }

	int getId() { return id; }
	Node* getLink() { return link; }
	void setLink(Node* l) { link = l; }
};

class AdjListGraph {
protected:
	int size; //������ ����
	char vertices[MAX_VTXS]; //���� ����(���뿡 ���� Ȯ�� �ʿ�)
	Node* adj[MAX_VTXS]; //�� ������ ���� ����Ʈ

public:
	AdjListGraph() : size(0) { }
	~AdjListGraph() { reset(); }

	void reset() {
		for (int i = 0; i < size; i++) {
			if (adj[i] != NULL) { delete adj[i]; }
		}
		size = 0;
	}

	bool isEmpty() { return (size == 0); }
	bool isFull() { return (size >= MAX_VTXS); }
	char getVertex(int i) { return vertices[i]; }
	int getSize() { return size; }

	//���� ���� ����
	void insertVertex(char val) {
		if (!isFull()) { vertices[size] = val; adj[size++] = NULL; }
		else { printf("Error: �׷��� ���� ���� �ʰ�\n"); }
	}

	//���� ���� ����
	void insertEdge(int u, int v) {
		adj[u] = new Node(v, adj[u]); //���� ����Ʈ�� �߰�
		adj[v] = new Node(u, adj[v]); //���� �׷����� ��� �ּ� ó��
	}

	void display() {
		printf("%d\n", size); //������ ���� ���
		for (int i = 0; i < size; i++) { //�� ���� ���� ���
			printf("%c  ", getVertex(i));
			for (Node* v = adj[i]; v != NULL; v = v->getLink()) {
				printf("   %c", getVertex(v->getId()));
				//printf("%3d", v->getId());
			}
			printf("\n");
		}
	}
	Node* adjacent(int v) { return adj[v]; }

	void load(const char* filename) {
		FILE* fp = fopen(filename, "r");
		if (fp != NULL) {
			int n;
			fscanf(fp, "%d", &n); //������ ��ü ����
			for (int i = 0; i < n; i++) {
				char str[80];
				fscanf(fp, "%s", str); //������ �̸�
				insertVertex(str[0]); //���� ����
				for (int j = 0; j < n; j++) {
					int val;
					fscanf(fp, "%d", &val); //���� ����
					if (val != 0) { //������ ������
						insertEdge(i, j); //���� ����
					}
				}
			}
		}
	}
};

class ArrayStack {
	int top;
	char data[MAX_STACK_SIZE] = { };

public:
	ArrayStack() { top = -1; } //���� ������: create()
	~ArrayStack() {} //���� �Ҹ���

	bool isEmpty() { return top == -1; }

	bool isFull() { return top == MAX_STACK_SIZE - 1; }

	void push(int e) {
		if (isFull()) { printf("���� ��ȭ ����"); exit(1); }
		data[++top] = e;
	}

	int pop() {
		if (isEmpty()) { printf("���� ���� ����"); exit(1); }
		return data[top--];
	}

	int peek() {
		//�������� �ʰ� ��� ��ȯ
		if (isEmpty()) { printf("���� ���� ����"); exit(1); }
		return data[top];
	}

	void display() {
		printf("[���� �׸��� �� = %2d] ==> ", top + 1);
		for (int i = 0; i <= top; i++) {
			printf("<%2c>", data[i]);
		}
		printf("\n");
	}
};

class TopoSortGraph : public AdjListGraph {
	int inDeg[MAX_VTXS]; // ������ ��������

public:
	void insertDirEdge(int u, int v) { //���⼺ ���� ���� ����
		adj[u] = new Node(v, adj[u]);
	}

	//���� ���� �Լ�
	void TopoSort() {
		//��� ������ ���� ������ ���
		for (int i = 0; i < getSize(); i++) { inDeg[i] = 0; } //�ʱ�ȭ
		for (int i = 0; i < getSize(); i++) {
			Node* node = adj[i]; //���� i���� ������ ������
			while (node != NULL) {
				inDeg[node->getId()]++;
				node = node->getLink();
			}
		}

		//���� ������ 0�� ������ ���ÿ� ����
		ArrayStack s;
		for (int i = 0; i < getSize(); i++) {
			if (inDeg[i] == 0) { s.push(i); }
		}

		//���� ������ ����
		while (s.isEmpty() == false) {
			int w = s.pop();
			printf(" %d ", w); //���� ���
			Node* node = adj[w]; //�� ������ ���� ������ ����
			while (node != NULL) {
				int u = node->getId();
				inDeg[u]--; //���� ������ ����
				if (inDeg[u] == 0) { s.push(u); } //���� ������ 0�� ������ push
				node = node->getLink(); //���� ����
			}
		}
		printf("\n");
	}
};

int main() {
	TopoSortGraph g;
	for (int i = 0; i < 6; i++) {
		g.insertVertex(i);
	}
	g.insertDirEdge(0, 2); g.insertDirEdge(0, 3);
	g.insertDirEdge(1, 3); g.insertDirEdge(1, 4);
	g.insertDirEdge(2, 3); g.insertDirEdge(2, 5);
	g.insertDirEdge(3, 5);
	g.insertDirEdge(4, 5);

	printf("Topology Sort: \n");
	g.TopoSort();

	return 0;
}