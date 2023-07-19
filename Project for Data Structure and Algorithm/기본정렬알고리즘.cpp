#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define MAX_SIZE 10000

int comp1 = 0; //�� Ƚ��, ���� ����
int comp2 = 0; //�� Ƚ��, ��ǰ ����
int comp3 = 0; //�� Ƚ��, ���� ����
int swaping1 = 0; //��ȯ Ƚ��, ���� ����
int swaping2 = 0; //��ȯ Ƚ��, ��ǰ ����
int swaping3 = 0; //��ȯ Ƚ��, ���� ����

//�ִ��� �ǻ��ڵ��� ��Ҹ� ��ġ�� �ʰ� ����!

void swap_function(int& x, int& y) //swap �Լ�
{
    int t = x;
    x = y;
    y = t;
}

void selection_sort(int A[], int n) {
    for (int i = n; i >= 2; i--) {
        int k = 1;
        for (int j = 2; j <= i; j++) {
            bool comp = A[j] > A[k]; //bool �Լ��� �����ϱ�
            comp1++; //��
            if (comp) { //=if(comp == true)
                k = j; //�ִ� index ����
            }
        }
        if (k != i) {
            swap_function(A[k], A[i]);
            swaping1++; //��ȯ
        }
    }
}

void bubble_sort(int A[], int n) {
    for (int a = n; a >= 2; a--) {
        for (int b = 1; b <= a - 1; b++) {
            bool comp = A[b] > A[b + 1];
            comp2++; //��
            if (comp) {
                swap_function(A[b], A[b + 1]);
                swaping2++; //��ȯ
            }
        }
    }
}

void insertion_sort(int A[], int n) {
    for (int c = 2; c <= n; c++) {
        int loc = c - 1;
        int item = A[c];
        while (loc >= 1) {
            bool comp = item < A[loc];
            comp3++; //��
            if (comp) {
                A[loc + 1] = A[loc];
                swaping3++; //��ȯ
                loc = loc - 1;
            }
            else {
                break;
            }
        }
        A[loc + 1] = item;
        swaping3++; //��ȯ
    }
}

int main() {
    int n;
    cin >> n; // �迭�� ũ�� �Է�

    int* arr = new int[MAX_SIZE];
    int* arr2 = new int[MAX_SIZE];
    int* arr3 = new int[MAX_SIZE];
    //���� �������� ���� �ٱ���
    //���� �Ҵ��� ���� ������ Warning C6262 �߻�

    for (int i = 1; i <= n; i++) {
        cin >> arr[i]; // n���� ���� �Է�, ������ �� ����
        arr2[i] = arr[i];
        arr3[i] = arr[i];
    }
    //C++�� �迭 �ε����� 0���� ����
    //�׷��� �ǻ��ڵ�� ��ġ��Ű�� ���� ���ǻ� 1���� ����

    selection_sort(arr, n);
    bubble_sort(arr2, n);
    insertion_sort(arr3, n);

    cout << "comp: " << comp1 << ", " << "swap: " << swaping1 << "\n";
    cout << "comp: " << comp2 << ", " << "swap: " << swaping2 << "\n";
    cout << "comp: " << comp3 << ", " << "swap: " << swaping3 << "\n";

    delete[] arr;
    delete[] arr2;
    delete[] arr3;

    return 0;
}

//����ȫ �������� �˰��� ������ ���� �ۼ��� �ڵ��Դϴ�.
//���� ������ ���۱ǻ� ������ �� ������, �ڵ带 ���� ����� ������ �� �������� ����մϴ�.