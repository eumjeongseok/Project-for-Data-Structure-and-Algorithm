#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;
#define MAX_SIZE 10001

//파티션 함수(Lomuto partition)
int partition(int A[], int l, int r) {
    int pivot = A[r];
    int i = l - 1;
    for (int j = l; j <= r - 1; ++j)
        if (A[j] <= pivot)
            swap(A[++i], A[j]);
    swap(A[i + 1], A[r]);
    return i + 1;
}

//MoM 알고리즘 차원에서 쓰이는 파티션 함수
int mom_partition(int A[], int l, int r, int M) {
    int idx = 0;
    for (int i = l; i <= r; ++i)
        if (A[i] == M) {
            idx = i;
            break;
        }
    swap(A[idx], A[r]);
    return partition(A, l, r);
}

//퀵 탐색
int quick_select(int A[], int l, int r, int i) {
    if (l == r)
        return A[l];

    int p = partition(A, l, r);
    int k = p - l + 1;

    if (i < k)
        return quick_select(A, l, p - 1, i);
    else if (i == k)
        return A[p];
    else
        return quick_select(A, p + 1, r, i - k);
}

//MoM 선택 알고리즘 -> 의사코드를 거의 그대로 구현
int mom_select(int A[], int l, int r, int i) {
    int n = r - l + 1;
    if (n <= 5)
        return quick_select(A, l, r, i);
    else {
        int G = ceil(n / 5.0);
        int* B = new int[G]; //동적 할당 + 형 변환
        for (int j = 0; j < G - 1; ++j) {
            int l_j = l + j * 5;
            int r_j = l_j + 4;
            int m_j = quick_select(A, l_j, r_j, 3);
            B[j] = m_j;
        }
        int l_j = l + (G - 1) * 5;
        int r_j = r;
        int m_j;
        if ((r_j - l_j + 1) % 2 == 0)
            m_j = quick_select(A, l_j, r_j, (r_j - l_j + 1) / 2);
        else
            m_j = quick_select(A, l_j, r_j, (r_j - l_j + 1) / 2 + 1);
        B[G - 1] = m_j;
        int M = mom_select(B, 0, G - 1, ceil(G / 2.0));
        int p = mom_partition(A, l, r, M);
        int k = p - l + 1;
        cout << M << ' ' << k << ' ' << n << ' ' << fixed << setprecision(2) << (double)k / n << endl;
        if (i < k)
            return mom_select(A, l, p - 1, i);
        else if (i == k)
            return A[p];
        else
            return mom_select(A, p + 1, r, i - k);

        delete[] B;
    }
}

int main() {
    int n, k;
    cin >> n >> k;
    int* A = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }

    mom_select(A, 0, n - 1, k - 1);

    delete[] A;
    return 0;
}
