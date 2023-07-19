//���� ����� �̿��� �ʺ� �켱 Ž�� �ڵ�
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#define MAX_VTXS 256 //ǥ�� ������ �ִ� ������ ����
#define MAX_QUEUE_SIZE 100
using namespace std;

inline void error(const char* str) {
	fprintf(stderr, "%s\n", str);
	exit(1);
}

class BinaryNode {
protected:
	int data; //Ʈ���� ������ ������
	BinaryNode* left; //���� �ڽ� ����� ������
	BinaryNode* right; //������ �ڽ� ����� ������

public:
	BinaryNode(int val = 0, BinaryNode* l = NULL, BinaryNode* r = NULL)
		: data(val), left(l), right(r) { }

	//Ű ������ ��带 Ž���ϴ� �Լ�(��� Ŭ�������� ��ȯ���� ����)
	BinaryNode* search(int key) {
		if (key == data)
			return this;

		else if (key < data && left != NULL)
			return left->search(key);

		else if (key > data && right != NULL)
			return right->search(key);

		else
			return NULL;
	}

	void setData(int val) { data = val; }
	void setLeft(BinaryNode* l) { left = l; }
	void setRight(BinaryNode* r) { right = r; }

	int getData() { return data; } //��尪 ��ȯ
	BinaryNode* getLeft() { return left; } //���� ��尪 ��ȯ
	BinaryNode* getRight() { return right; } //������ ��尪 ��ȯ

	bool isLeaf() { return left == NULL && right == NULL; } //�� ��� ���� Ȯ��
};

class AdjMatGraph {
protected:
	int size; //������ ����
	char vertices[MAX_VTXS]; //������ �̸�
	int adj[MAX_VTXS][MAX_VTXS]; //���� ���

public:
	AdjMatGraph() { reset(); }
	char getVertex(int i) { return vertices[i]; }
	int getEdge(int i, int j) { return adj[i][j]; }

	void setEdge(int i, int j, int val) { adj[i][j] = val; }
	//�ǹ��� 1: ���⿡�� �׼��� ������ �߻�, ��ü ��? (�ν� �����ΰ�?)

	bool isEmpty() { return size == 0; }
	bool isFull() { return size >= MAX_VTXS; }

	//�׷��� �ʱ�ȭ ==> ���� ������ �׷���
	void reset() {
		size = 0;
		for (int i = 0; i < MAX_VTXS; i++) {
			for (int j = 0; j < MAX_VTXS; j++) {
				setEdge(i, j, 0); //��� ���� ����� ĭ�� 0�� ����ֱ�
				//�ǹ��� 2: ���⿡�� �޸� ������ �߻��ߴ� ������...?
			}
		}
	}

	//���� ���� ����
	void insertVertex(char name) {
		if (!isFull()) { vertices[size++] = name; }
		else { printf("Error: �׷��� ���� ���� �ʰ�\n"); }
	}

	//���� ���� ����: ������ �׷����� �����. (����, ����ġ �׷��������� ����)
	void insertEdge(int u, int v) {
		setEdge(u, v, 1);
		setEdge(v, u, 1); //���� �׷����̹Ƿ�, �밢�� �������� ��Ī�� ĭ�� ��� 1 ����ֱ�!
	}

	void display(FILE* fp = stdout) {
		fprintf(fp, "%d\n", size);
		for (int i = 0; i < size; i++) {
			fprintf(fp, "%c   ", getVertex(i));
			for (int j = 0; j < size; j++) {
				fprintf(fp, " %3d", getEdge(i, j));
			}
			fprintf(fp, "\n");
		}
	}

	//���� �Է� �Լ�
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

	void store(const char* filename) {
		FILE* fp = fopen(filename, "w");
		if (fp != NULL) {
			display(fp);
			fclose(fp);
		}
	}
};

//Ž�� ����� ���� �׷��� Ŭ����
class SrchAMGraph : public AdjMatGraph {
	bool visited[MAX_VTXS]; //������ ���� ����

public:
	void resetVisited() { //��� ������ �湮���� �ʾҴٰ� ����
		for (int i = 0; i < size; i++) {
			visited[i] = false;
		}
	}

	bool isLinked(int u, int v) { return getEdge(u, v) != 0; }

	//�ʺ� �켱 Ž��(BFS) �Լ�
	void BFS(int v) {
		visited[v] = true; //���� ������ �湮��
		printf("%c  ", getVertex(v)); //������ �̸� ���

		queue<int> que; //stl�� ����, ť Ŭ������ �������� �� ����
		que.push(v);

		while (!que.empty()) {
			int v = que.front(); que.pop();

			for (int w = 0; w < size; w++) {
				if (isLinked(v, w) && visited[w] == false) {
					visited[w] = true;
					printf("%c  ", getVertex(w));
					que.push(w);
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