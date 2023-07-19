#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

//최대한 강의자료의 의사코드를 그대로 구현하고자 함

const int MAX = 100000;
int p[MAX];
//부모노드지향 유향그래프(parent pointer tree)를 위한 배열, index(자식)는 value(부모)를 가리킨다

int rank_disjoint[MAX];
//union by rank(등수 병합법): 등수는 각 노드에 대한 노피
//Path Compression(경로 압축): 등수가 갱신되지 않음, 즉 높이의 상한

// 초기화
void make_set(int u) {
    p[u] = u;
    rank_disjoint[u] = 0;
    //시간 복잡도: O(1)
}

// 해당 원소의 루트(대표 원소)를 찾는 함수
int find_set(int u) {
    if (p[u] != u) {
        p[u] = find_set(p[u]);
        // 경로 압축(Path Compression)
        //시간 복잡도: O(logn) -> 트리 연산은 로그형의 시간이 걸림
    }
    return p[u];
}

// 두 원소를 포함하는 집합을 합치는 함수
void union_set(int u, int v) {
    u = find_set(u); //이로써 a가 있는 집합의 루트 노드 가리킴
    v = find_set(v); //이로써 b가 있는 집합의 루트 노드 가리킴

    if (rank_disjoint[u] > rank_disjoint[v]) {
        p[v] = u;
    }
    else {
        p[u] = v;
        if (rank_disjoint[u] == rank_disjoint[v]) {
            rank_disjoint[v] = rank_disjoint[u] + 1;
        }
    }
    //시간 복잡도: O(logn) -> 트리 연산은 로그형의 시간이 걸림
}

int main() {
    //테스트 프로그램: 서로소
    for (int i = 0; i < MAX; i++) {
        make_set(i);
    }

    union_set(0, 1);
    union_set(1, 2);
    union_set(2, 3);

    // 0, 1, 2, 3이 모두 같은 집합에 속하는지 확인
    if (find_set(0) == find_set(3)) {
        cout << "0, 1, 2, 3 are connected." << "\n";
    }
    else {
        cout << "0, 1, 2, 3 are not connected." << "\n";
    }

    // 0, 3이 같은 집합에 속하는지 확인
    if (find_set(0) == find_set(3)) {
        cout << "0 and 3 are connected." << "\n";
    }
    else {
        cout << "0 and 3 are not connected." << "\n";
    }

    return 0;
}