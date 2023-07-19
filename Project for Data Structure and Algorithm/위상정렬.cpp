//위상 정렬(topologocal sort)?
//유향 그래프의 각 정점들에 대해서, 선행 순서를 위배하지 않으면서 모든 정점을 나열하는 ㅓㅅ

//위상 순서(topological order)?
//전체 위상 정렬 과정에서 정점이 삭제되는 순서
//진입 차수가 0인 정점을 선택하여, 여기에 연결된 모든 간선 삭제
//진입 차수가 0인 정점이 없다 ==> 사이클이 형성!

//위상 정렬과 위상 순서는 여러 개 존재한다.

#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define MAX_VTXS 256
using namespace std;
const int MAX_STACK_SIZE = 20;

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
	int getSize() { return size; }

	//정점 삽입 연산
	void insertVertex(char val) {
		if (!isFull()) { vertices[size] = val; adj[size++] = NULL; }
		else { printf("Error: 그래프 정점 개수 초과\n"); }
	}

	//간선 삽입 연산
	void insertEdge(int u, int v) {
		adj[u] = new Node(v, adj[u]); //인접 리스트에 추가
		adj[v] = new Node(u, adj[v]); //유향 그래프인 경우 주석 처리
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
};

class ArrayStack {
	int top;
	char data[MAX_STACK_SIZE] = { };

public:
	ArrayStack() { top = -1; } //스택 생성자: create()
	~ArrayStack() {} //스택 소멸자

	bool isEmpty() { return top == -1; }

	bool isFull() { return top == MAX_STACK_SIZE - 1; }

	void push(int e) {
		if (isFull()) { printf("스택 포화 에러"); exit(1); }
		data[++top] = e;
	}

	int pop() {
		if (isEmpty()) { printf("스택 공백 에러"); exit(1); }
		return data[top--];
	}

	int peek() {
		//삭제하지 않고 요소 반환
		if (isEmpty()) { printf("스택 공백 에러"); exit(1); }
		return data[top];
	}

	void display() {
		printf("[스택 항목의 수 = %2d] ==> ", top + 1);
		for (int i = 0; i <= top; i++) {
			printf("<%2c>", data[i]);
		}
		printf("\n");
	}
};

class TopoSortGraph : public AdjListGraph {
	int inDeg[MAX_VTXS]; // 정점의 진입차수

public:
	void insertDirEdge(int u, int v) { //방향성 간선 삽입 연산
		adj[u] = new Node(v, adj[u]);
	}

	//위상 정렬 함수
	void TopoSort() {
		//모든 정점의 진입 차수를 계산
		for (int i = 0; i < getSize(); i++) { inDeg[i] = 0; } //초기화
		for (int i = 0; i < getSize(); i++) {
			Node* node = adj[i]; //정점 i에서 나오는 간선들
			while (node != NULL) {
				inDeg[node->getId()]++;
				node = node->getLink();
			}
		}

		//진입 차수가 0인 정점을 스택에 삽입
		ArrayStack s;
		for (int i = 0; i < getSize(); i++) {
			if (inDeg[i] == 0) { s.push(i); }
		}

		//위상 순서를 생성
		while (s.isEmpty() == false) {
			int w = s.pop();
			printf(" %d ", w); //정점 출력
			Node* node = adj[w]; //각 정점의 진입 차수를 변경
			while (node != NULL) {
				int u = node->getId();
				inDeg[u]--; //진입 차수를 감소
				if (inDeg[u] == 0) { s.push(u); } //진입 차수가 0인 정점을 push
				node = node->getLink(); //다음 정점
			}
		}
		printf("\n");
	}
};

int main() {
	TopoSortGraph g;
	for (int i = 0; i < 6; i++) {
		g.insertVertex(i);
	}
	g.insertDirEdge(0, 2); g.insertDirEdge(0, 3);
	g.insertDirEdge(1, 3); g.insertDirEdge(1, 4);
	g.insertDirEdge(2, 3); g.insertDirEdge(2, 5);
	g.insertDirEdge(3, 5);
	g.insertDirEdge(4, 5);

	printf("Topology Sort: \n");
	g.TopoSort();

	return 0;
}