//Kruskal 알고리즘: 각 단계에서 사이클을 이루지 않는 최소 비용 간선을 선택하는 알고리즘

//절차
//1. 그래프의 모든 간선을 가중치에 따라 오름차순으로 정렬한다. (모든 정점이 각각 고유한 집합)
//2. 가장 가중치가 작은 간선 e를 뽑는다. -> u와 v가 각각 속한 집합을 찾음
//3. e를 신장 트리에 넣을 경우 사이클이 생기면 삽입하지 않고 2번으로 이동한다.
//4. 사이클이 새이지 않으면 최소 신장 트리에 삽입한다.
//5. n-1개의 간선이 삽입될 때까지 2번으로 이동한다.

//Prim 알고리즘: 하나의 정점에서부터 시작하여 트리를 단계적으로 확장해나가는 방법

//절차
//1. 그래프에서 시작 정점을 선택하여 초기 트리를 만든다.
//2. 현재 트리의 정점들과 인접한 정점들 중에서 가중치가 가장 작은 정점 v를 선택한다.
//3. 이 정점 v와 이때의 간선을 트리에 추가한다.
//4. 모든 정점이 삽입될 때까지 2번으로 이동한다.


#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define MAX_VTXS 256 //표현 가능한 최대 정점의 개수
#define INF 9999
#define MAX_ELEMENT 200

//Union-Find 연산을 위한 정점 집합 클래스
class VertexSets {
private:
    int parent[MAX_VTXS]; //부모 정점의 id
    int nSets; //집합의 개수

public:
    VertexSets(int n) :nSets(n) {
        for (int i = 0; i < nSets; i++) {
            parent[i] = -1; //모든 정점이 고유의 집합에 속함
        }
    }

    bool isRoot(int i) { return parent[i] < 0; }

    int findSet(int v) { //v가 속한 집합을 찾아 반환
        while (!isRoot(v)) { v = parent[v]; }
        return v;
    }

    void unionSets(int s1, int s2) { //집합 s1을 집합 s2에 합침
        parent[s1] = s2;
        nSets--;
    }
};

//Kruskal의 최소 비용 신장 트리 프로그램
class HeapNode {

private:
    int key; //Key 값: 간선의 가중치
    int v1; //정점 v1
    int v2; //정점 2

public:
    HeapNode(int k = 0, int u = -1, int v = -1) :key(k), v1(u), v2(v) { }

    void setKey(int k, int u, int v) { key = k; v1 = u; v2 = v; }
    int getKey() { return key; }
    int getV1() { return v1; }
    int getV2() { return v2; }
};

//최소 힙 클래스
class MinHeap {

private:
    HeapNode node[MAX_ELEMENT]; //요소의 배열
    int size; //힙의 현재 요소의 개수

public:
    MinHeap() :size(0) { }

    bool isEmpty() { return size == 0; }
    bool isFull() { return size == MAX_ELEMENT - 1; }

    HeapNode& getParent(int i) { return node[i / 2]; }
    HeapNode& getLeft(int i) { return node[i * 2]; }
    HeapNode& getRight(int i) { return node[i * 2 + 1]; }

    //삽입 함수
    void insert(int key, int u, int v) {
        if (isFull()) { return; }
        int i = ++size;

        while (i != 1 && key < getParent(i).getKey()) {
            node[i] = getParent(i);
            i /= 2;
        }
        node[i].setKey(key, u, v);
    }

    //삭제 함수
    HeapNode remove() {
        if (isEmpty()) { return NULL; }

        HeapNode root = node[1];
        HeapNode last = node[size--];
        int parent = 1;
        int child = 2;

        while (child <= size) {
            if (child<size && getLeft(parent).getKey()>getRight(parent).getKey()) { child++; }
            if (last.getKey() <= node[child].getKey()) { break; }
            node[parent] = node[child];
            parent = child;
            child *= 2;
        }
        node[parent] = last;
        return root;
    }
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
            int n, val;
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

class WGraph : public AdjMatGraph {
public:
    //insertEdge의 중복 정의
    //매개변수로 간선의 가중치(weight) 추가
    //가중치로 int형을 갖는다고 가정
    void insertEdge(int u, int v, int weight) {
        if (weight > INF) { weight = INF; }
        setEdge(u, v, weight);
    }

    bool hasEdge(int i, int j) { return (getEdge(i, j) < INF); }

    void load(const char* filename) {
        FILE* fp = fopen(filename, "r");

        if (fp != NULL) {
            int n;
            fscanf(fp, "%d", &n);
            for (int i = 0; i < n; i++) {
                char str[80];
                int val;
                fscanf(fp, "%s", str);
                insertVertex(str[0]); //정점 삽입

                for (int j = 0; j < n; j++) {
                    fscanf(fp, "%d", &val); //간선 정보
                    insertEdge(i, j, val); //간선 삽입
                }
            }
            fclose(fp);
        }
    }
};

class WGraphMST :public WGraph {

public:
    void Kruskal() { //kruskal의 최소 비용 신장 트리 프로그램
        MinHeap heap;

        //힙에 모든 간선 삽입
        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                if (hasEdge(i, j)) { heap.insert(getEdge(i, j), i, j); }
            }
        }

        VertexSets set(size); //size개의 집합을 만듬
        int edgeAccepted = 0; //선택된 간선의 수

        while (edgeAccepted < size - 1) {
            HeapNode e = heap.remove(); //최소 힙에서 삭제
            int uset = set.findSet(e.getV1()); //정점 u의 집합 번호
            int vset = set.findSet(e.getV2()); //정점 v의 집합 번호

            if (uset != vset) {//서로 속한 집합이 다르면
                printf("간선 추가 : %c - %c (비용:%d)\n"
                    , getVertex(e.getV1()), getVertex(e.getV2()), e.getKey());
                set.unionSets(uset, vset); //두개의 집합을 합함
                edgeAccepted++;
            }
        }
    }

    //Prim의 최소 비용 신장 트리 프로그램
    void Prim(int s) {
        bool selected[MAX_VTXS]; //정점이 이미 포함
        int dist[MAX_VTXS]; //거리

        for (int i = 0; i < size; i++) {  //배열 초기화
            dist[i] = INF;
            selected[i] = false;
        }
        dist[s] = 0; //시작 정점

        for (int i = 0; i < size; i++) {
            //포함되지 않은 정점들 중에서 MST와의 거리가 최소인 정점
            int u = getMinVertex(selected, dist);

            selected[u] = true;
            if (dist[u] == INF) { return; }
            printf("%c ", getVertex(u));

            for (int v = 0; v < size; v++) {
                if (getEdge(u, v) != INF) {
                    if (!selected[v] && getEdge(u, v) < dist[v]) {
                        dist[v] = getEdge(u, v);
                    }
                }
            }
        }
        printf("\n");
    }

    //MST에 포함되지 않은 정점들 중에서 MST와의 거리가 최소인 정점 선택
    int getMinVertex(bool* selected, int* dist) {
        int minv = 0;
        int mindist = INF;

        for (int v = 0; v < size; v++) {
            if (!selected[v] && dist[v] < mindist) {
                mindist = dist[v];
                minv = v;
            }
        }
        return minv;
    }
};

int main() {
    WGraphMST g;
    g.load("c:\\Users\\jeong\\Desktop\\graph.txt");

    //Kruskal 알고리즘
    printf("MST By Kruskal's Algorithm\n");
    g.Kruskal();

    printf("\n=============================================\n");

    //Prim 알고리즘
    printf("MST By Prim's Algorithm\n");
    g.Prim(0);
    return 0;
}