//�̷� ã�� ���� - ���� ���� Ʈ��
//�����ڷ�: <���� Ǯ� C++ �ڷᱸ��>�� �׷��� �ܿ�

//�ּ�: Ctrl + C + K
//�ּ� ����: Ctrl + K + U

#include <vector>
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
	bool visited[MAX_VTXS]; //������ �湮 ����

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
			visited[i] = false; // �湮 ���� �ʱ�ȭ
		}
	}

	//���� ���� ����
	void insertVertex(char name) {
		if (!isFull()) { vertices[size++] = name; }
		else { printf("Error: �׷��� ���� ���� �ʰ�\n"); }
	}

	//���� ���� ����: ������ �׷����� �����. (����, ����ġ �׷��������� ����)
	void insertEdge(char u, char v) {
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

	bool maze(int v, int t) {
		visited[v] = true;

		if (v == t) {
			return true;
		}

		for (int x = 0; x < size; x++) {
			if (adj[v][x] == 1 && !visited[x]) {
				//������ ������ �����ϰ�, �湮���� �ʾ��� ��
				if (maze(x, t)) {
					return true;
				}
			}
		}
		return false;
	}
};

int main() {
	AdjMatGraph g;
	g.insertVertex('A');
	g.insertVertex('B');
	g.insertVertex('C');
	g.insertVertex('D');
	g.insertVertex('E');
	
	//0: A, 1: B, 2: C, 3: D, 4: E
	g.insertEdge(0, 1);
	g.insertEdge(1, 2);
	g.insertEdge(1, 3);
	g.insertEdge(3, 4);

	g.display();

	int startVertex = 0;
	int targetVertex = 4;
	bool canReachTarget = g.maze(startVertex, targetVertex);

	if (canReachTarget) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}

	return 0;
}