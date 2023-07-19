#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

#define LIST_SIZE 9
#define INDEX_SIZE 3

//탐색: 키(key)를 통해 값(value)를 찾는 과정

//정렬되지 않은 배열에서의 순차 탐색: O(n)
//탐색 성공: N+1 / 2 번 비교
//탐색 실패: N번 비교
int sequentiaSearch(int list[], int key, int low, int high) {
	for (int i = low; i <= high; i++) {
		if (list[i] == key) { return i; } //탐색 성공 시 키 값의 인덱스 반환
	}
	return -1; //실패 시 -1 반환
}
//정렬된 배열을 이용하는 방법: O(logn)
int sortedsequentiaSearch(int list[], int key, int low, int high) {
	for (int i = low; i <= high; i++) {
		if (list[i] > key) { return -1; }
		//해당 항목이 리스트에 존재하지 않음. (이 리스트는 키만 존재...???)
		if (list[i] == key) { return i; } //탐색 성공 시 키 값의 인덱스 반환
	}
	return -1; //실패 시 -1 반환
}
//이진 탐색 트리를 이용하는 방법: O(logn) => 실제로는 퀵 선택!
int binarySearch(int list[], int key, int low, int high) { //재귀 사용
	int middle;
	if (low <= high) {
		middle = (low + high) / 2; //파티션
		if (key == list[middle]) { return middle; } //탐색 성공
		else if (key < list[middle]) { return binarySearch(list, key, low, middle - 1); }
		else { return binarySearch(list, key, middle + 1, high); }
	}
	return -1;
}
int binarySearchIter(int list[], int key, int low, int high) { //재귀 사용
	int middle;
	while (low <= high) {
		middle = (low + high) / 2; //파티션
		if (key == list[middle]) { return middle; } //탐색 성공
		else if (key < list[middle]) { low = middle + 1; }
		else { low = middle - 1; }
	}
	return -1;
}


//색인 순차 탐색: index 테이블을 통해 탐색의 효율을 높이는 방법
//index 테이블에 m개의 항목 존재, 주 자료 리스트의 데이터 수가 n
//각 index 항목은 주 자료 리스트의 각 n/m번째 데이터 존재
//예)테이블에 3개의 항목이 있고, 주 자료 테이블에 9개가 있다면, 각 index 항목은 각각 1, 2, 3번째 데이터 존재
//index[i] <= key <= index[i+1]을 만족하는 항목을 찾고, 해당 항목 발견 시 그 범위에서만 검색
struct Index {
	int key;
	int index;
};
int indexedSearch(int list[], int nList, Index* tbl, int nTbl, int key) {
	if (key<list[0] || key>list[nList - 1]) { return -1; }
	for (int i = 0; i < nTbl - 1; i++) {
		if (tbl[i].key <= key && tbl[i + 1].key > key) {
			return sequentiaSearch(list, key, tbl[i].index, tbl[i + 1].index);
		}
	}
	return sequentiaSearch(list, key, tbl[nTbl - 1].index, nList);
	//지금까지 작성한 함수를 사용해보고 싶다면? -> sequentialSearch 부분을 인수가 같은 다른 함수로 바꾸어보기!
	//sortedsequentiaSearch(단, 정렬 알고리즘을 가져와야 함), binarySearch, binarySearchIter
}

//보간 탐색: 탐색키가 존재할 위치를 예측하여 탐색하는 방법 - O(logn)
//list[high]-list[low]: k-list[low] = high-low:탐색위치-low
int interpolationSearch(int list[], int nList, int key) {
	int low = 0;
	int high = nList - 1;
	while ((list[low] <= key) && (key <= list[high])) {
		int j = low + ((float)(key - list[low]) / (list[high] - list[low])) * (high - low);
		if (key > list[j]) { low = j + 1; }
		else if (key < list[j]) { high = j - 1; }
		else return j;
	}
	return -1;
}

int main() {
	int list[LIST_SIZE] = { 3, 9, 15, 22, 31, 55, 67, 88, 91 };
	Index index[INDEX_SIZE] = { {3, 0}, {15, 3}, {67, 6} };

	int number, ret;
	printf("탐색할 숫자를 입력하십시오: ");
	cin >> number;
	//ret = indexedSearch(list, LIST_SIZE, index, INDEX_SIZE, number);
	ret = interpolationSearch(list, LIST_SIZE, number);
	if (ret >= 0) { printf("탐색 성공: 숫자(%d) 위치=%d\n", number, ret); }
	else { printf("숫자(%d) 탐색 실패\n", number); }

	return 0;
}