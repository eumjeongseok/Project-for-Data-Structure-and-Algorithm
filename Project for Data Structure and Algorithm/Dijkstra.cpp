//Dijkstra 알고리즘 + 최단 경로 탐색 기능
//Dijkstra 알고리즘: 하나의 시작 정점 v에서 다른 정점까지의 최단 경로를 찾는 알고리즘
//시간 복잡도: O(n^2), 그러나 모든 정점에서 출발 시 O(n^3)


#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define MAX_VTXS 256 //표현 가능한 최대 정점의 개수
#define INF 9999

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

class WGraphDijkstra :public WGraph{

private:
    int dist[MAX_VTXS]; //시작노드로부터의 최단경로 거리
    bool found[MAX_VTXS]; //방문한 정점 표시

public:
    //방문하지 않은 정점들 중에서 최단 경로 거리가 가장 작은 정점을 찾아 반환
    int chooseVertex() {
        int min = INF;
        int minpos = -1;

        for (int i = 0; i < size; i++) {
            if (dist[i] < min && !found[i]) {
                min = dist[i];
                minpos = i;
            }
        }
        return minpos;
    }

    //Dijkstra의 최단 경로 알고리즘:start 정점에서 시작함
    void ShortestPath(int start){
        for (int i = 0; i < size; i++){
            dist[i] = getEdge(start, i);
            found[i] = false;
        }

        found[start] = true; //시작노드 방문 표시
        dist[start] = 0; //최초거리

        for (int i = 0; i < size; i++) {
            printf("Step%2d:", i + 1);
            printDistance();
            int u = chooseVertex();
            found[u] = true;

            for (int w = 0; w < size; w++) {
                if (found[w] == false) {
                    if (dist[u] + getEdge(u, w) < dist[w])
                        dist[w] = dist[u] + getEdge(u, w);
                }
            }
        }
    }

    void printDistance() { //dist 상태를 출력하는 함수
        for (int i = 0; i < size; i++) {
            printf("%5d", dist[i]);
        }
        printf("\n");
    }
};

int main() {
    WGraphDijkstra g;

    g.load("c:\\Users\\jeong\\Desktop\\graph.txt");
    printf("Shortest Path By Dijkstra Algorithm\n");
    g.ShortestPath(0);
    return 0;
}