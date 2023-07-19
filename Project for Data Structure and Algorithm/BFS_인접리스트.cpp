//���� ����Ʈ�� Ȱ���� �ʺ� �켱 Ž��
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <cstring>
#include <iostream>
#define MAX_VTXS 256
using namespace std;
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
		//adj[v] = new Node(u, adj[v]); //���� �׷����� ��� �ּ� ó��
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

	void load(const char* filename) { //������ �Ǵ� �κ�
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

//Ž�� ����� ���� �׷��� Ŭ����
class SrchAMGraph : public AdjListGraph {
	bool visited[MAX_VTXS]; //������ ���� ����

public:
	void resetVisited() { //��� ������ �湮���� �ʾҴٰ� ����
		for (int i = 0; i < size; i++) {
			visited[i] = false;
		}
	}

	bool isLinked(int u, int v) {
		for (Node* p = adj[u]; p != NULL; p = p->getLink()) {
			if (p->getId() == v) { return true; }
		}
		return false;
	}

	//�ʺ� �켱 Ž��(BFS) �Լ�
	void BFS(int v) {
		visited[v] = true; //���� ������ �湮��
		printf("%c  ", getVertex(v)); //������ �̸� ���

		queue<int> que; //stl�� ����, ť Ŭ������ �������� �� ����
		que.push(v);

		while (!que.empty()) {
			int v = que.front(); que.pop();

			for (Node* w = adj[v]; w != NULL; w = w->getLink()) {
				int id = w->getId();
				if (!visited[id]) {
					visited[id] = true;
					printf("%c  ", getVertex(id));
					que.push(id);
				}
			}
		}
	}
};

int main() {
	SrchAMGraph g;
	g.load("c:\\Users\\jeong\\Desktop\\graph.txt");

	// A-C-E-G  
	// | |  \|
	// B-D-F H


	printf("�׷���(graph.txt)\n");
	//g.display();

	printf("BFS ==> ");
	g.resetVisited();
	g.BFS(0);
	printf("\n");

	return 0;
}