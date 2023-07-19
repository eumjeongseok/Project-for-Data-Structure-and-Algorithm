#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

#define LIST_SIZE 9
#define INDEX_SIZE 3

//Ž��: Ű(key)�� ���� ��(value)�� ã�� ����

//���ĵ��� ���� �迭������ ���� Ž��: O(n)
//Ž�� ����: N+1 / 2 �� ��
//Ž�� ����: N�� ��
int sequentiaSearch(int list[], int key, int low, int high) {
	for (int i = low; i <= high; i++) {
		if (list[i] == key) { return i; } //Ž�� ���� �� Ű ���� �ε��� ��ȯ
	}
	return -1; //���� �� -1 ��ȯ
}
//���ĵ� �迭�� �̿��ϴ� ���: O(logn)
int sortedsequentiaSearch(int list[], int key, int low, int high) {
	for (int i = low; i <= high; i++) {
		if (list[i] > key) { return -1; }
		//�ش� �׸��� ����Ʈ�� �������� ����. (�� ����Ʈ�� Ű�� ����...???)
		if (list[i] == key) { return i; } //Ž�� ���� �� Ű ���� �ε��� ��ȯ
	}
	return -1; //���� �� -1 ��ȯ
}
//���� Ž�� Ʈ���� �̿��ϴ� ���: O(logn) => �����δ� �� ����!
int binarySearch(int list[], int key, int low, int high) { //��� ���
	int middle;
	if (low <= high) {
		middle = (low + high) / 2; //��Ƽ��
		if (key == list[middle]) { return middle; } //Ž�� ����
		else if (key < list[middle]) { return binarySearch(list, key, low, middle - 1); }
		else { return binarySearch(list, key, middle + 1, high); }
	}
	return -1;
}
int binarySearchIter(int list[], int key, int low, int high) { //��� ���
	int middle;
	while (low <= high) {
		middle = (low + high) / 2; //��Ƽ��
		if (key == list[middle]) { return middle; } //Ž�� ����
		else if (key < list[middle]) { low = middle + 1; }
		else { low = middle - 1; }
	}
	return -1;
}


//���� ���� Ž��: index ���̺��� ���� Ž���� ȿ���� ���̴� ���
//index ���̺� m���� �׸� ����, �� �ڷ� ����Ʈ�� ������ ���� n
//�� index �׸��� �� �ڷ� ����Ʈ�� �� n/m��° ������ ����
//��)���̺� 3���� �׸��� �ְ�, �� �ڷ� ���̺� 9���� �ִٸ�, �� index �׸��� ���� 1, 2, 3��° ������ ����
//index[i] <= key <= index[i+1]�� �����ϴ� �׸��� ã��, �ش� �׸� �߰� �� �� ���������� �˻�
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
	//���ݱ��� �ۼ��� �Լ��� ����غ��� �ʹٸ�? -> sequentialSearch �κ��� �μ��� ���� �ٸ� �Լ��� �ٲپ��!
	//sortedsequentiaSearch(��, ���� �˰����� �����;� ��), binarySearch, binarySearchIter
}

//���� Ž��: Ž��Ű�� ������ ��ġ�� �����Ͽ� Ž���ϴ� ��� - O(logn)
//list[high]-list[low]: k-list[low] = high-low:Ž����ġ-low
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
	printf("Ž���� ���ڸ� �Է��Ͻʽÿ�: ");
	cin >> number;
	//ret = indexedSearch(list, LIST_SIZE, index, INDEX_SIZE, number);
	ret = interpolationSearch(list, LIST_SIZE, number);
	if (ret >= 0) { printf("Ž�� ����: ����(%d) ��ġ=%d\n", number, ret); }
	else { printf("����(%d) Ž�� ����\n", number); }

	return 0;
}