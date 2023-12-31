//인접 리스트를 활용한 너비 우선 탐색
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
//인접 리스트를 이용한 그래프를 위한 클래스들과 테스트 프로그램

class Node { //노드 클래스
protected:
	int id; //정점의 id
	Node* link; //다음 노드의 포인터

public:
	Node(int i, Node* l = NULL) : id(i), link(l) {}
	~Node() { if (link != NULL) { delete link; } }

	int getId() { return id; }
	Node* getLink() { return link; }
	void setLink(Node* l) { link = l; }
};

class AdjListGraph {
protected:
	int size; //정점의 개수
	char vertices[MAX_VTXS]; //정점 정보(응용에 따라 확장 필요)
	Node* adj[MAX_VTXS]; //각 정점의 인접 리스트

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

	//정점 삽입 연산
	void insertVertex(char val) {
		if (!isFull()) { vertices[size] = val; adj[size++] = NULL; }
		else { printf("Error: 그래프 정점 개수 초과\n"); }
	}

	//간선 삽입 연산
	void insertEdge(int u, int v) {
		adj[u] = new Node(v, adj[u]); //인접 리스트에 추가
		//adj[v] = new Node(u, adj[v]); //유향 그래프인 경우 주석 처리
	}

	void display() {
		printf("%d\n", size); //정점의 개수 출력
		for (int i = 0; i < size; i++) { //각 행의 정보 출력
			printf("%c  ", getVertex(i));
			for (Node* v = adj[i]; v != NULL; v = v->getLink()) {
				printf("   %c", getVertex(v->getId()));
				//printf("%3d", v->getId());
			}
			printf("\n");
		}
	}
	Node* adjacent(int v) { return adj[v]; }

	void load(const char* filename) { //문제가 되는 부분
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
};

//탐색 기능을 가진 그래프 클래스
class SrchAMGraph : public AdjListGraph {
	bool visited[MAX_VTXS]; //정점의 뱡문 정보

public:
	void resetVisited() { //모든 정점을 방문하지 않았다고 설정
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

	//너비 우선 탐색(BFS) 함수
	void BFS(int v) {
		visited[v] = true; //현재 정점을 방문함
		printf("%c  ", getVertex(v)); //정점의 이름 출력

		queue<int> que; //stl로 구현, 큐 클래스의 변수형이 안 맞음
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


	printf("그래프(graph.txt)\n");
	//g.display();

	printf("BFS ==> ");
	g.resetVisited();
	g.BFS(0);
	printf("\n");

	return 0;
}