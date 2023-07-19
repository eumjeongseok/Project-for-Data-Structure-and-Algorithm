//미로 찾기 문제 - 상태 공간 트리
//참고자료: <쉽게 풀어쓴 C++ 자료구조>의 그래프 단원

//주석: Ctrl + C + K
//주석 해제: Ctrl + K + U

#include <vector>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define MAX_VTXS 256 //표현 가능한 최대 정점의 개수
using namespace std;

class AdjMatGraph {
protected:
	int size; //정점의 개수
	char vertices[MAX_VTXS]; //정점의 이름
	int adj[MAX_VTXS][MAX_VTXS]; //인접 행렬
	bool visited[MAX_VTXS]; //정점의 방문 여부

public:
	AdjMatGraph() { reset(); }
	char getVertex(int i) { return vertices[i]; }
	int getEdge(int i, int j) { return adj[i][j]; }
	//여기서는 가중치를 따로 설정하지 않으므로 0, 1만 생각함

	void setEdge(int i, int j, int val) { adj[i][j] = val; }
	//의문점 1: 여기에서 액세스 위반이 발생, 대체 왜? (인식 오류인가?)

	bool isEmpty() { return size == 0; }
	bool isFull() { return size >= MAX_VTXS; }

	//그래프 초기화 ==> 공백 상태의 그래프
	void reset() {
		size = 0;
		for (int i = 0; i < MAX_VTXS; i++) {
			for (int j = 0; j < MAX_VTXS; j++) {
				setEdge(i, j, 0); //모든 인접 행렬의 칸에 0을 집어넣기
				//의문점 2: 여기에서 메모리 오류가 발생했던 이유는...?
			}
			visited[i] = false; // 방문 여부 초기화
		}
	}

	//정점 삽입 연산
	void insertVertex(char name) {
		if (!isFull()) { vertices[size++] = name; }
		else { printf("Error: 그래프 정점 개수 초과\n"); }
	}

	//간선 삽입 연산: 무방향 그래프의 경우임. (방향, 가중치 그래프에서는 수정)
	void insertEdge(char u, char v) {
		setEdge(u, v, 1);
		setEdge(v, u, 1); //무향 그래프이므로, 대각선 기준으로 대칭인 칸에 모두 1 집어넣기!
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
				//간선이 실제로 존재하고, 방문하지 않았을 때
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