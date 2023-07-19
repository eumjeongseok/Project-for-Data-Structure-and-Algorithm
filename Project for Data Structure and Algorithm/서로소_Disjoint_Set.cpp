#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

//�ִ��� �����ڷ��� �ǻ��ڵ带 �״�� �����ϰ��� ��

const int MAX = 100000;
int p[MAX];
//�θ������� ����׷���(parent pointer tree)�� ���� �迭, index(�ڽ�)�� value(�θ�)�� ����Ų��

int rank_disjoint[MAX];
//union by rank(��� ���չ�): ����� �� ��忡 ���� ����
//Path Compression(��� ����): ����� ���ŵ��� ����, �� ������ ����

// �ʱ�ȭ
void make_set(int u) {
    p[u] = u;
    rank_disjoint[u] = 0;
    //�ð� ���⵵: O(1)
}

// �ش� ������ ��Ʈ(��ǥ ����)�� ã�� �Լ�
int find_set(int u) {
    if (p[u] != u) {
        p[u] = find_set(p[u]);
        // ��� ����(Path Compression)
        //�ð� ���⵵: O(logn) -> Ʈ�� ������ �α����� �ð��� �ɸ�
    }
    return p[u];
}

// �� ���Ҹ� �����ϴ� ������ ��ġ�� �Լ�
void union_set(int u, int v) {
    u = find_set(u); //�̷ν� a�� �ִ� ������ ��Ʈ ��� ����Ŵ
    v = find_set(v); //�̷ν� b�� �ִ� ������ ��Ʈ ��� ����Ŵ

    if (rank_disjoint[u] > rank_disjoint[v]) {
        p[v] = u;
    }
    else {
        p[u] = v;
        if (rank_disjoint[u] == rank_disjoint[v]) {
            rank_disjoint[v] = rank_disjoint[u] + 1;
        }
    }
    //�ð� ���⵵: O(logn) -> Ʈ�� ������ �α����� �ð��� �ɸ�
}

int main() {
    //�׽�Ʈ ���α׷�: ���μ�
    for (int i = 0; i < MAX; i++) {
        make_set(i);
    }

    union_set(0, 1);
    union_set(1, 2);
    union_set(2, 3);

    // 0, 1, 2, 3�� ��� ���� ���տ� ���ϴ��� Ȯ��
    if (find_set(0) == find_set(3)) {
        cout << "0, 1, 2, 3 are connected." << "\n";
    }
    else {
        cout << "0, 1, 2, 3 are not connected." << "\n";
    }

    // 0, 3�� ���� ���տ� ���ϴ��� Ȯ��
    if (find_set(0) == find_set(3)) {
        cout << "0 and 3 are connected." << "\n";
    }
    else {
        cout << "0 and 3 are not connected." << "\n";
    }

    return 0;
}