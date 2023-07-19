//Floyd �˰���: �׷����� ��� ���� ������ �ִ� ��θ� �Ѳ����� ã���ִ� �˰���
//�˰��� -> ���� �ݺ���
//�ð� ���⵵: O(n^3) - ���� �ݺ���


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

class WGraphFloyd :public WGraph{
private:
    int A[MAX_VTXS][MAX_VTXS]; //�ִܰ�� �Ÿ�

public:
    void ShortestPathFloyd(){
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                A[i][j] = getEdge(i, j);
            }
        }

        for (int k = 0; k < size; k++) {
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (A[i][k] + A[k][j] < A[i][j]) {
                        A[i][j] = A[i][k] + A[k][j];
                    }
                }
            }
            printA();
        }
    }

    void printA(){
        printf("===================================================\n");
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                if (A[i][j] == INF) { printf(" INF"); }
                else { printf("%4d", A[i][j]); }


            }
            printf("\n");
        }
    }
};

int main() {
    WGraphFloyd g;
    g.load("c:\\Users\\jeong\\Desktop\\graph.txt");
    printf("Shortest Path by Floyd Algorithm\n");

    g.ShortestPathFloyd();
    return 0;
}
