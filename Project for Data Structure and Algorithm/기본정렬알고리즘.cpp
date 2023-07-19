#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define MAX_SIZE 10000

int comp1 = 0; //비교 횟수, 선택 정렬
int comp2 = 0; //비교 횟수, 거품 정렬
int comp3 = 0; //비교 횟수, 삽입 정렬
int swaping1 = 0; //교환 횟수, 선택 정렬
int swaping2 = 0; //교환 횟수, 거품 정렬
int swaping3 = 0; //교환 횟수, 삽입 정렬

//최대한 의사코드의 요소를 해치지 않게 구성!

void swap_function(int& x, int& y) //swap 함수
{
    int t = x;
    x = y;
    y = t;
}

void selection_sort(int A[], int n) {
    for (int i = n; i >= 2; i--) {
        int k = 1;
        for (int j = 2; j <= i; j++) {
            bool comp = A[j] > A[k]; //bool 함수로 정의하기
            comp1++; //비교
            if (comp) { //=if(comp == true)
                k = j; //최댓값 index 복사
            }
        }
        if (k != i) {
            swap_function(A[k], A[i]);
            swaping1++; //교환
        }
    }
}

void bubble_sort(int A[], int n) {
    for (int a = n; a >= 2; a--) {
        for (int b = 1; b <= a - 1; b++) {
            bool comp = A[b] > A[b + 1];
            comp2++; //비교
            if (comp) {
                swap_function(A[b], A[b + 1]);
                swaping2++; //교환
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
            comp3++; //비교
            if (comp) {
                A[loc + 1] = A[loc];
                swaping3++; //교환
                loc = loc - 1;
            }
            else {
                break;
            }
        }
        A[loc + 1] = item;
        swaping3++; //교환
    }
}

int main() {
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

//정진홍 교수님의 알고리즘 과제로 직접 작성한 코드입니다.
//과제 내용은 저작권상 보여줄 수 없으나, 코드를 보면 충분히 이해할 수 있으리라 기대합니다.