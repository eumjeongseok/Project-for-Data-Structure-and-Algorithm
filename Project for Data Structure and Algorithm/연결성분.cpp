//연결 성분? : 말 그대로 서로 연결된 노드들이 모인 집합


//인접 행렬을 사용한 너비 우선 탐색
#define _CRT_SECURE_NO_WARNINGS
#pragma once
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

public:
	AdjMatGraph() { reset(); }
	char getVertex(int i) { return vertices[i]; }
	int getEdge(int i, int j) { return adj[i][j]; }
	int getsize() { return size; }

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
		}
	}

	//정점 삽입 연산
	void insertVertex(char name) {
		if (!isFull()) { vertices[size++] = name; }
		else { printf("Error: 그래프 정점 개수 초과\n"); }
	}

	//간선 삽입 연산: 무방향 그래프의 경우임. (방향, 가중치 그래프에서는 수정)
	void insertEdge(int u, int v) {
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

	//파일 입력 함수
	void load(const char* filename) {
		FILE* fp = fopen(filename, "r");
		if (fp != NULL) {
			int n;
			fscanf(fp, "%d", &n); //정점의 전체 개수
			for (int i = 0; i < n; i++) {
				char str[80];
				fscanf(fp, "%s", str); //정점의 이름
				insertVertex(str[0]); //정점 삽입
				for (int j = 0; j < n; j++) {
					int val;
					fscanf(fp, "%d", &val); //간선 정보
					if (val != 0) { //간선이 있으면
						insertEdge(i, j); //간선 삽입
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

//탐색 기능을 가진 그래프 클래스
class SrchAMGraph : public AdjMatGraph {
	//만약 visited를 다른 함수에서 쓰려면 protected를 추가해야 함
	bool visited[MAX_VTXS]; //정점의 뱡문 정보

public:
	bool getVisited(int w) { return visited[w]; } //교재에 빠진 함수라 직접 만든 함수...ㅠㅠ
	void setVisitedTrue(int v) { visited[v] = true; } //교재에 빠진 함수라 직접 만든 함수...ㅠㅠ

	void resetVisited() { //모든 정점을 방문하지 않았다고 설정
		for (int i = 0; i < size; i++) {
			visited[i] = false;
		}
	}

	bool isLinked(int u, int v) { return getEdge(u, v) != 0; }

	//깊이 우선 탐색(DFS) 함수
	void DFS(int v) {
		visited[v] = true; //현재 정점을 방문함
		printf("%c ", getVertex(v)); //정점의 이름 출력

		for (int w = 0; w < size; w++) {
			if (isLinked(v, w) && visited[w] == false) {
				DFS(w); //연결 + 방문 X => 순환호출로 방문
			}
		}
	}
};

class ConnectedComponentGraph : public SrchAMGraph {
	int label[MAX_VTXS]; //정점의 색상 필드 추가

public:
	//깊이 우선 탐색
	void labelDFS(int v, int color) {
		setVisitedTrue(v); //현재 정점을 방문함
		label[v] = color; //현재 정점의 색상

		for (int w = 0; w < getsize(); w++) {
			if (isLinked(v, w) && getVisited(w) == false) {
				labelDFS(w, color);
			}
		}
	}

	//그래프의 연결 성분 검출 함수
	void findConnectedComponent() {
		int count = 0; //연결 성분의 수, 곧 color로 넣을 값
		for (int i = 0; i < getsize(); i++) {
			if (getVisited(i) == false) { //방문하지 않았으면
				labelDFS(i, ++count);
			}
		}
		printf("그래프 연결성분 개수 = = %d\n", count);
		//count = 1일 때, 입력된 그래프는 그 자체로 연결 그래프
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

	printf("연결 성분 테스트 그래프\n");
	g.display();
	g.resetVisited(); //visited 배열을 초기화
	g.findConnectedComponent(); //그래프 연결 성분 탐색

	return 0;
}