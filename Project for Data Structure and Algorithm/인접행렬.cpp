//���� ����� �̿��� �׷��� Ŭ������ �׽�Ʈ ���α׷�
//�ڵ尡 �۵��ϴ� ���� ���� �� �����߽��ϴ�...õ�α� ������ �� �� ����ּ��� �Ф�


#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define MAX_VTXS 256 //ǥ�� ������ �ִ� ������ ����

class AdjMatGraph {
protected:
	int size; //������ ����
	char vertices[MAX_VTXS]; //������ �̸�
	int adj[MAX_VTXS][MAX_VTXS]; //���� ���

public:
	AdjMatGraph() { reset(); }
	char getVertex(int i) { return vertices[i]; }
	int getEdge(int i, int j) { return adj[i][j]; }
	//���⼭�� ����ġ�� ���� �������� �����Ƿ� 0, 1�� ������

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

int main() {
	AdjMatGraph g;

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
	printf("���� ��ķ� ǥ���� �׷���\n");
	g.display(); //ȭ��(stdout)���� ���


	// 4
	// A 0 1 0 1
	// B 1 0 1 1
	// C 0 1 0 1
	// D 1 1 1 0


	g.store("c:\\Users\\(�����)\\Desktop\\graph.txt"); //�׷��� g�� ���Ͽ� ����
	//����ڴ� PC���� �����ϴ� �������� ����ϸ� �˴ϴ�!

	g.reset(); //�׷��� g �ʱ�ȭ
	g.load("c:\\Users\\(�����)\\Desktop\\graph.txt");

	//���
	printf("���� ��ķ� ǥ���� �׷��� <����: graph.txt>\n");
	g.display(); //ȭ��(stdout)���� ���

	return 0;
}