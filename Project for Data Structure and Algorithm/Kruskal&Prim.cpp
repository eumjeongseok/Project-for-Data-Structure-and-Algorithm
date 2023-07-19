//Kruskal �˰���: �� �ܰ迡�� ����Ŭ�� �̷��� �ʴ� �ּ� ��� ������ �����ϴ� �˰���

//����
//1. �׷����� ��� ������ ����ġ�� ���� ������������ �����Ѵ�. (��� ������ ���� ������ ����)
//2. ���� ����ġ�� ���� ���� e�� �̴´�. -> u�� v�� ���� ���� ������ ã��
//3. e�� ���� Ʈ���� ���� ��� ����Ŭ�� ����� �������� �ʰ� 2������ �̵��Ѵ�.
//4. ����Ŭ�� ������ ������ �ּ� ���� Ʈ���� �����Ѵ�.
//5. n-1���� ������ ���Ե� ������ 2������ �̵��Ѵ�.

//Prim �˰���: �ϳ��� ������������ �����Ͽ� Ʈ���� �ܰ������� Ȯ���س����� ���

//����
//1. �׷������� ���� ������ �����Ͽ� �ʱ� Ʈ���� �����.
//2. ���� Ʈ���� ������� ������ ������ �߿��� ����ġ�� ���� ���� ���� v�� �����Ѵ�.
//3. �� ���� v�� �̶��� ������ Ʈ���� �߰��Ѵ�.
//4. ��� ������ ���Ե� ������ 2������ �̵��Ѵ�.


#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define MAX_VTXS 256 //ǥ�� ������ �ִ� ������ ����
#define INF 9999
#define MAX_ELEMENT 200

//Union-Find ������ ���� ���� ���� Ŭ����
class VertexSets {
private:
    int parent[MAX_VTXS]; //�θ� ������ id
    int nSets; //������ ����

public:
    VertexSets(int n) :nSets(n) {
        for (int i = 0; i < nSets; i++) {
            parent[i] = -1; //��� ������ ������ ���տ� ����
        }
    }

    bool isRoot(int i) { return parent[i] < 0; }

    int findSet(int v) { //v�� ���� ������ ã�� ��ȯ
        while (!isRoot(v)) { v = parent[v]; }
        return v;
    }

    void unionSets(int s1, int s2) { //���� s1�� ���� s2�� ��ħ
        parent[s1] = s2;
        nSets--;
    }
};

//Kruskal�� �ּ� ��� ���� Ʈ�� ���α׷�
class HeapNode {

private:
    int key; //Key ��: ������ ����ġ
    int v1; //���� v1
    int v2; //���� 2

public:
    HeapNode(int k = 0, int u = -1, int v = -1) :key(k), v1(u), v2(v) { }

    void setKey(int k, int u, int v) { key = k; v1 = u; v2 = v; }
    int getKey() { return key; }
    int getV1() { return v1; }
    int getV2() { return v2; }
};

//�ּ� �� Ŭ����
class MinHeap {

private:
    HeapNode node[MAX_ELEMENT]; //����� �迭
    int size; //���� ���� ����� ����

public:
    MinHeap() :size(0) { }

    bool isEmpty() { return size == 0; }
    bool isFull() { return size == MAX_ELEMENT - 1; }

    HeapNode& getParent(int i) { return node[i / 2]; }
    HeapNode& getLeft(int i) { return node[i * 2]; }
    HeapNode& getRight(int i) { return node[i * 2 + 1]; }

    //���� �Լ�
    void insert(int key, int u, int v) {
        if (isFull()) { return; }
        int i = ++size;

        while (i != 1 && key < getParent(i).getKey()) {
            node[i] = getParent(i);
            i /= 2;
        }
        node[i].setKey(key, u, v);
    }

    //���� �Լ�
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

class WGraphMST :public WGraph {

public:
    void Kruskal() { //kruskal�� �ּ� ��� ���� Ʈ�� ���α׷�
        MinHeap heap;

        //���� ��� ���� ����
        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                if (hasEdge(i, j)) { heap.insert(getEdge(i, j), i, j); }
            }
        }

        VertexSets set(size); //size���� ������ ����
        int edgeAccepted = 0; //���õ� ������ ��

        while (edgeAccepted < size - 1) {
            HeapNode e = heap.remove(); //�ּ� ������ ����
            int uset = set.findSet(e.getV1()); //���� u�� ���� ��ȣ
            int vset = set.findSet(e.getV2()); //���� v�� ���� ��ȣ

            if (uset != vset) {//���� ���� ������ �ٸ���
                printf("���� �߰� : %c - %c (���:%d)\n"
                    , getVertex(e.getV1()), getVertex(e.getV2()), e.getKey());
                set.unionSets(uset, vset); //�ΰ��� ������ ����
                edgeAccepted++;
            }
        }
    }

    //Prim�� �ּ� ��� ���� Ʈ�� ���α׷�
    void Prim(int s) {
        bool selected[MAX_VTXS]; //������ �̹� ����
        int dist[MAX_VTXS]; //�Ÿ�

        for (int i = 0; i < size; i++) {  //�迭 �ʱ�ȭ
            dist[i] = INF;
            selected[i] = false;
        }
        dist[s] = 0; //���� ����

        for (int i = 0; i < size; i++) {
            //���Ե��� ���� ������ �߿��� MST���� �Ÿ��� �ּ��� ����
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

    //MST�� ���Ե��� ���� ������ �߿��� MST���� �Ÿ��� �ּ��� ���� ����
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

    //Kruskal �˰���
    printf("MST By Kruskal's Algorithm\n");
    g.Kruskal();

    printf("\n=============================================\n");

    //Prim �˰���
    printf("MST By Prim's Algorithm\n");
    g.Prim(0);
    return 0;
}