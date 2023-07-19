//인접 행렬을 이용한 너비 우선 탐색 코드
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#define MAX_VTXS 256 //표현 가능한 최대 정점의 개수
#define MAX_QUEUE_SIZE 100
using namespace std;

inline void error(const char* str) {
	fprintf(stderr, "%s\n", str);
	exit(1);
}

class BinaryNode {
protected:
	int data; //트리에 저장할 데이터
	BinaryNode* left; //왼쪽 자식 노드의 포인터
	BinaryNode* right; //오른쪽 자식 노드의 포인터

public:
	BinaryNode(int val = 0, BinaryNode* l = NULL, BinaryNode* r = NULL)
		: data(val), left(l), right(r) { }

	//키 값으로 노드를 탐색하는 함수(노드 클래스에서 순환으로 구현)
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

	int getData() { return data; } //노드값 반환
	BinaryNode* getLeft() { return left; } //왼쪽 노드값 반환
	BinaryNode* getRight() { return right; } //오른쪽 노드값 반환

	bool isLeaf() { return left == NULL && right == NULL; } //잎 노드 여부 확인
};

class AdjMatGraph {
protected:
	int size; //정점의 개수
	char vertices[MAX_VTXS]; //정점의 이름
	int adj[MAX_VTXS][MAX_VTXS]; //인접 행렬

public:
	AdjMatGraph() { reset(); }
	char getVertex(int i) { return vertices[i]; }
	int getEdge(int i, int j) { return adj[i][j]; }

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
	bool visited[MAX_VTXS]; //정점의 뱡문 정보

public:
	void resetVisited() { //모든 정점을 방문하지 않았다고 설정
		for (int i = 0; i < size; i++) {
			visited[i] = false;
		}
	}

	bool isLinked(int u, int v) { return getEdge(u, v) != 0; }

	//너비 우선 탐색(BFS) 함수
	void BFS(int v) {
		visited[v] = true; //현재 정점을 방문함
		printf("%c  ", getVertex(v)); //정점의 이름 출력

		queue<int> que; //stl로 구현, 큐 클래스의 변수형이 안 맞음
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


	printf("그래프(graph.txt)\n");
	//g.display();

	printf("BFS ==> ");
	g.resetVisited();
	g.BFS(0);
	printf("\n");

	return 0;
}