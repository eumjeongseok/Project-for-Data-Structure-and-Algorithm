//���� ����? : �� �״�� ���� ����� ������ ���� ����


//���� ����� ����� �ʺ� �켱 Ž��
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define MAX_VTXS 256 //ǥ�� ������ �ִ� ������ ����
using namespace std;

class AdjMatGraph {
protected:
	int size; //������ ����
	char vertices[MAX_VTXS]; //������ �̸�
	int adj[MAX_VTXS][MAX_VTXS]; //���� ���

public:
	AdjMatGraph() { reset(); }
	char getVertex(int i) { return vertices[i]; }
	int getEdge(int i, int j) { return adj[i][j]; }
	int getsize() { return size; }

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
	//���� visited�� �ٸ� �Լ����� ������ protected�� �߰��ؾ� ��
	bool visited[MAX_VTXS]; //������ ���� ����

public:
	bool getVisited(int w) { return visited[w]; } //���翡 ���� �Լ��� ���� ���� �Լ�...�Ф�
	void setVisitedTrue(int v) { visited[v] = true; } //���翡 ���� �Լ��� ���� ���� �Լ�...�Ф�

	void resetVisited() { //��� ������ �湮���� �ʾҴٰ� ����
		for (int i = 0; i < size; i++) {
			visited[i] = false;
		}
	}

	bool isLinked(int u, int v) { return getEdge(u, v) != 0; }

	//���� �켱 Ž��(DFS) �Լ�
	void DFS(int v) {
		visited[v] = true; //���� ������ �湮��
		printf("%c ", getVertex(v)); //������ �̸� ���

		for (int w = 0; w < size; w++) {
			if (isLinked(v, w) && visited[w] == false) {
				DFS(w); //���� + �湮 X => ��ȯȣ��� �湮
			}
		}
	}
};

class ConnectedComponentGraph : public SrchAMGraph {
	int label[MAX_VTXS]; //������ ���� �ʵ� �߰�

public:
	//���� �켱 Ž��
	void labelDFS(int v, int color) {
		setVisitedTrue(v); //���� ������ �湮��
		label[v] = color; //���� ������ ����

		for (int w = 0; w < getsize(); w++) {
			if (isLinked(v, w) && getVisited(w) == false) {
				labelDFS(w, color);
			}
		}
	}

	//�׷����� ���� ���� ���� �Լ�
	void findConnectedComponent() {
		int count = 0; //���� ������ ��, �� color�� ���� ��
		for (int i = 0; i < getsize(); i++) {
			if (getVisited(i) == false) { //�湮���� �ʾ�����
				labelDFS(i, ++count);
			}
		}
		printf("�׷��� ���Ἲ�� ���� = = %d\n", count);
		//count = 1�� ��, �Էµ� �׷����� �� ��ü�� ���� �׷���
		for (int i = 0; i < getsize(); i++) {
			printf("%c=%d ", getVertex(i), label[i]);
		}
		printf("\n");
	}
};

int main() {
	ConnectedComponentGraph g;
	for (int i = 0; i < 5; i++) {
		g.insertVertex('A' + i);
	}
	g.insertEdge(1, 0);
	g.insertEdge(2, 0);
	g.insertEdge(3, 4);

	printf("���� ���� �׽�Ʈ �׷���\n");
	g.display();
	g.resetVisited(); //visited �迭�� �ʱ�ȭ
	g.findConnectedComponent(); //�׷��� ���� ���� Ž��

	return 0;
}