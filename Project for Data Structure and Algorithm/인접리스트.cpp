#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define MAX_VTXS 256
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

int main() {
	AdjListGraph g;

	for (int i = 0; i < 4; i++) {
		g.insertVertex('A' + i); //���� ����: 'A', 'B', ...
	}

	//���� ����
	g.insertEdge(0, 1);
	g.insertEdge(0, 3);
	g.insertEdge(1, 2);
	g.insertEdge(1, 3);
	g.insertEdge(2, 3);

	//���
	printf("���� ����Ʈ�� ǥ���� �׷���\n");
	g.display(); //ȭ��(stdout)���� ���

	return 0;
}