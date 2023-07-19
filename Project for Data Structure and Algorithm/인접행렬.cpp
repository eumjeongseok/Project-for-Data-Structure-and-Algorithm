//인접 행렬을 이용한 그래프 클래스와 테스트 프로그램
//코드가 작동하는 데에 여러 번 수정했습니다...천인국 교수님 저 좀 살려주세요 ㅠㅠ


#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define MAX_VTXS 256 //표현 가능한 최대 정점의 개수

class AdjMatGraph {
protected:
	int size; //정점의 개수
	char vertices[MAX_VTXS]; //정점의 이름
	int adj[MAX_VTXS][MAX_VTXS]; //인접 행렬

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

int main() {
	AdjMatGraph g;

	for (int i = 0; i < 4; i++) {
		g.insertVertex('A' + i); //정점 삽입: 'A', 'B', ...
	}

	//간선 삽입
	g.insertEdge(0, 1);
	g.insertEdge(0, 3);
	g.insertEdge(1, 2);
	g.insertEdge(1, 3);
	g.insertEdge(2, 3);

	//출력
	printf("인접 행렬로 표현한 그래프\n");
	g.display(); //화면(stdout)으로 출력


	// 4
	// A 0 1 0 1
	// B 1 0 1 1
	// C 0 1 0 1
	// D 1 1 1 0


	g.store("c:\\Users\\(사용자)\\Desktop\\graph.txt"); //그래프 g를 파일에 저장
	//사용자는 PC마다 존재하는 계정명을 사용하면 됩니다!

	g.reset(); //그래프 g 초기화
	g.load("c:\\Users\\(사용자)\\Desktop\\graph.txt");

	//출력
	printf("인접 행렬로 표현한 그래프 <파일: graph.txt>\n");
	g.display(); //화면(stdout)으로 출력

	return 0;
}