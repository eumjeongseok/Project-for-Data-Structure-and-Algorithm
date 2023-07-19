//Dijkstra �˰��� + �ִ� ��� Ž�� ���
//Dijkstra �˰���: �ϳ��� ���� ���� v���� �ٸ� ���������� �ִ� ��θ� ã�� �˰���
//�ð� ���⵵: O(n^2), �׷��� ��� �������� ��� �� O(n^3)


#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define MAX_VTXS 256 //ǥ�� ������ �ִ� ������ ����
#define INF 9999

class AdjMatGraph {
protected:
    int size; //������ ����
    char vertices[MAX_VTXS]; //������ �̸�
    int adj[MAX_VTXS][MAX_VTXS]; //���� ���

public:
    AdjMatGraph() { reset(); }
    char getVertex(int i) { return vertices[i]; }
    int getEdge(int i, int j) { return adj[i][j]; }

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
            int n, val;
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

class WGraph : public AdjMatGraph {
public:
    //insertEdge�� �ߺ� ����
    //�Ű������� ������ ����ġ(weight) �߰�
    //����ġ�� int���� ���´ٰ� ����
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
                insertVertex(str[0]); //���� ����

                for (int j = 0; j < n; j++) {
                    fscanf(fp, "%d", &val); //���� ����
                    insertEdge(i, j, val); //���� ����
                }
            }
            fclose(fp);
        }
    }
};

class WGraphDijkstra :public WGraph{

private:
    int dist[MAX_VTXS]; //���۳��κ����� �ִܰ�� �Ÿ�
    bool found[MAX_VTXS]; //�湮�� ���� ǥ��

public:
    //�湮���� ���� ������ �߿��� �ִ� ��� �Ÿ��� ���� ���� ������ ã�� ��ȯ
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

    //Dijkstra�� �ִ� ��� �˰���:start �������� ������
    void ShortestPath(int start){
        for (int i = 0; i < size; i++){
            dist[i] = getEdge(start, i);
            found[i] = false;
        }

        found[start] = true; //���۳�� �湮 ǥ��
        dist[start] = 0; //���ʰŸ�

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

    void printDistance() { //dist ���¸� ����ϴ� �Լ�
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