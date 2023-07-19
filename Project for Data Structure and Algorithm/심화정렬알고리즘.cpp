#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define MAX_SIZE 100001

int comp1 = 0; //비교 횟수, 병합 정렬
int comp2 = 0; //비교 횟수, 퀵 정렬
int comp3 = 0; //비교 횟수, 히프 정렬
int swaping1 = 0; //교환 횟수, 병합 정렬
int swaping2 = 0; //교환 횟수, 퀵 정렬
int swaping3 = 0; //교환 횟수, 히프 정렬

//최대한 의사코드의 요소를 해치지 않게 구성!

//swap 함수
void swap_function(int& x, int& y) //swap 함수
{
    int t = x;
    x = y;
    y = t;
}

//합병 함수
void merge(int arr[], int left, int middle, int right)
{
    int i = left, j = middle + 1, t = 1;
    const int size = MAX_SIZE;
    int temp[MAX_SIZE];
    //allmar만큼의 temp 변수 생성(new), 곧 동적 할당

    while (i <= middle && j <= right) {
        comp1++; //비교
        if (arr[i] <= arr[j]) {
            temp[t++] = arr[i++];
            swaping1++; //교환
        }
        else {
            temp[t++] = arr[j++];
            swaping1++; //교환
        }
    }

    while (i <= middle) {
        temp[t++] = arr[i++];
        swaping1++; // 교환
    }

    while (j <= right) {
        temp[t++] = arr[j++];
        swaping1++; // 교환
    }

    i = left, t = 1;
    while (i <= right) {
        arr[i++] = temp[t++];
        swaping1++; // 교환
    }
}

// 병합 정렬
void merge_sort(int arr[], int left, int right)
{
    if (left < right) {
        int middle = (left + right) / 2;
        merge_sort(arr, left, middle);
        merge_sort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

//피봇을 정하는 함수(Lomuto partition)
int partition(int arr[], int left, int right) {
    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j <= right - 1; j++) {
        comp2++; //비교
        if (arr[j] <= pivot) {
            i = i + 1;
            swap_function(arr[i], arr[j]);
            swaping2++; //교환
        }
    }
    swap_function(arr[i + 1], arr[right]);
    swaping2++; //교환
    return i + 1;
}

//퀵 정렬
void quick_sort(int arr[], int left, int right) {
    if (left < right) {
        int p = partition(arr, left, right);
        quick_sort(arr, left, p - 1);
        quick_sort(arr, p + 1, right);
    }
}

//서브 히프로 내려가서 정렬하는 함수
void down_heap(int arr[], int i, int n) {
    int left = 2 * i;
    int right = 2 * i + 1;
    int largest = i;

    if (left <= n) {
        comp3++; //비교
        if (arr[left] > arr[largest]) {
            largest = left;
        }

    }

    if (right <= n) {
        comp3++; //비교
        if (arr[right] > arr[largest]) {
            largest = right;
        }
    }

    if (largest != i) {
        swap_function(arr[i], arr[largest]);
        swaping3++; //교환
        down_heap(arr, largest, n);
    }
}

//히프 정렬
void heap_sort(int arr[], int n) {
    // 먼저 히프 트리를 만들어 준다.
    for (int i = n / 2; i >= 1; i--) {
        down_heap(arr, i, n);
    }

    //일단 신입을 임시 사장으로 만든 뒤, 점점 강등하면서(?) 정렬하기
    //(이 설명은 천인국 교수님의 자료구조 책에 나온 비유입니다.)
    for (int i = n; i >= 2; i--) {
        swap_function(arr[i], arr[1]);
        swaping3++; //교환
        down_heap(arr, 1, i - 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    //실행 속도 증가

    int n;
    cin >> n; // 배열의 크기 입력

    int* arr = new int[MAX_SIZE];
    int* arr2 = new int[MAX_SIZE];
    int* arr3 = new int[MAX_SIZE];
    //비교할 정수들을 담을 바구니
    //동적 할당을 하지 않으면 Warning C6262 발생

    for (int i = 1; i <= n; i++) {
        cin >> arr[i]; // n개의 정수 입력, 각각에 값 복사
        arr2[i] = arr[i];
        arr3[i] = arr[i];
    }
    //C++은 배열 인덱스가 0부터 시작
    //그러나 의사코드와 일치시키기 위해 편의상 1부터 시작

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
