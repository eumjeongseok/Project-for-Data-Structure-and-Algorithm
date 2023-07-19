#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define MAX_SIZE 100001

int comp1 = 0; //�� Ƚ��, ���� ����
int comp2 = 0; //�� Ƚ��, �� ����
int comp3 = 0; //�� Ƚ��, ���� ����
int swaping1 = 0; //��ȯ Ƚ��, ���� ����
int swaping2 = 0; //��ȯ Ƚ��, �� ����
int swaping3 = 0; //��ȯ Ƚ��, ���� ����

//�ִ��� �ǻ��ڵ��� ��Ҹ� ��ġ�� �ʰ� ����!

//swap �Լ�
void swap_function(int& x, int& y) //swap �Լ�
{
    int t = x;
    x = y;
    y = t;
}

//�պ� �Լ�
void merge(int arr[], int left, int middle, int right)
{
    int i = left, j = middle + 1, t = 1;
    const int size = MAX_SIZE;
    int temp[MAX_SIZE];
    //allmar��ŭ�� temp ���� ����(new), �� ���� �Ҵ�

    while (i <= middle && j <= right) {
        comp1++; //��
        if (arr[i] <= arr[j]) {
            temp[t++] = arr[i++];
            swaping1++; //��ȯ
        }
        else {
            temp[t++] = arr[j++];
            swaping1++; //��ȯ
        }
    }

    while (i <= middle) {
        temp[t++] = arr[i++];
        swaping1++; // ��ȯ
    }

    while (j <= right) {
        temp[t++] = arr[j++];
        swaping1++; // ��ȯ
    }

    i = left, t = 1;
    while (i <= right) {
        arr[i++] = temp[t++];
        swaping1++; // ��ȯ
    }
}

// ���� ����
void merge_sort(int arr[], int left, int right)
{
    if (left < right) {
        int middle = (left + right) / 2;
        merge_sort(arr, left, middle);
        merge_sort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

//�Ǻ��� ���ϴ� �Լ�(Lomuto partition)
int partition(int arr[], int left, int right) {
    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j <= right - 1; j++) {
        comp2++; //��
        if (arr[j] <= pivot) {
            i = i + 1;
            swap_function(arr[i], arr[j]);
            swaping2++; //��ȯ
        }
    }
    swap_function(arr[i + 1], arr[right]);
    swaping2++; //��ȯ
    return i + 1;
}

//�� ����
void quick_sort(int arr[], int left, int right) {
    if (left < right) {
        int p = partition(arr, left, right);
        quick_sort(arr, left, p - 1);
        quick_sort(arr, p + 1, right);
    }
}

//���� ������ �������� �����ϴ� �Լ�
void down_heap(int arr[], int i, int n) {
    int left = 2 * i;
    int right = 2 * i + 1;
    int largest = i;

    if (left <= n) {
        comp3++; //��
        if (arr[left] > arr[largest]) {
            largest = left;
        }

    }

    if (right <= n) {
        comp3++; //��
        if (arr[right] > arr[largest]) {
            largest = right;
        }
    }

    if (largest != i) {
        swap_function(arr[i], arr[largest]);
        swaping3++; //��ȯ
        down_heap(arr, largest, n);
    }
}

//���� ����
void heap_sort(int arr[], int n) {
    // ���� ���� Ʈ���� ����� �ش�.
    for (int i = n / 2; i >= 1; i--) {
        down_heap(arr, i, n);
    }

    //�ϴ� ������ �ӽ� �������� ���� ��, ���� �����ϸ鼭(?) �����ϱ�
    //(�� ������ õ�α� �������� �ڷᱸ�� å�� ���� �����Դϴ�.)
    for (int i = n; i >= 2; i--) {
        swap_function(arr[i], arr[1]);
        swaping3++; //��ȯ
        down_heap(arr, 1, i - 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    //���� �ӵ� ����

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

    merge_sort(arr, 1, n);
    quick_sort(arr2, 1, n);
    heap_sort(arr3, n);

    cout << "comp: " << comp1 << ", " << "swap: " << swaping1 << "\n";
    cout << "comp: " << comp2 << ", " << "swap: " << swaping2 << "\n";
    cout << "comp: " << comp3 << ", " << "swap: " << swaping3 << "\n";

    delete[] arr;
    delete[] arr2;
    delete[] arr3;

    return 0;
}
