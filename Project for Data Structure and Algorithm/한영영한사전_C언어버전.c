// 이진 탐색 트리를 사용한 영어 사전
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_WORD_SIZE	 100
#define MAX_MEANING_SIZE 200

// 데이터 형식
typedef struct {
	char word[MAX_WORD_SIZE];		// 키필드
	char meaning[MAX_MEANING_SIZE];
} element;
// 노드의 구조
typedef struct TreeNode {
	element key;
	struct TreeNode* left, * right;
} TreeNode;

// 만약 e1 < e2 이면 -1 반환
// 만약 e1 == e2 이면 0 반환
// 만약 e1 > e2 이면 1 반환
int compare(element e1, element e2) {
	int result = strcmp(e1.word, e2.word);
	if (result < 0)
		return -1;
	else if (result > 0)
		return 1;
	else
		return 0;
}

// 이진 탐색 트리 탐색 함수(더미 데이터)
TreeNode* search(TreeNode* root, element key) {
	TreeNode* p = root;
	while (p != NULL) {
		int cmp = compare(key, p->key);
		if (cmp == 0)
			return p;
		else if (cmp < 0)
			p = p->left;
		else if (cmp > 0)
			p = p->right;
	}
	return NULL;  // 탐색에 실패했을 경우 NULL 반환
}

TreeNode* new_node(element item) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}
TreeNode* insert_node(TreeNode* node, element key) {
	// 트리가 공백이면 새로운 노드를 반환한다. 
	if (node == NULL) return new_node(key);

	// 그렇지 않으면 순환적으로 트리를 내려간다. 
	if (compare(key, node->key) < 0)
		node->left = insert_node(node->left, key);
	else if (compare(key, node->key) > 0)
		node->right = insert_node(node->right, key);

	// 루트 포인터를 반환한다. 
	return node;
}

// 이진 탐색 트리 탐색 함수(단어 검색)
TreeNode* search_binary_tree(TreeNode* root, char* word) {
	TreeNode* p = root;
	while (p != NULL) {
		int cmp = strcmp(word, p->key.word);
		if (cmp == 0)
			return p;
		else if (cmp < 0)
			p = p->left;
		else if (cmp > 0)
			p = p->right;
	}
	return NULL;  // 탐색에 실패했을 경우 NULL 반환
}

// 이진 탐색 트리 출력 함수
void show_word(TreeNode* p) {
	if (p != NULL) {
		show_word(p->left);
		printf("%s %s\n", p->key.word, p->key.meaning);
		show_word(p->right);
	}
}

void help() {
	//printf("**** i: 입력, k: 한국어 단어 검색, e: 영어 단어 검색, p: 출력, q: 종료 ****: ");
}
// 이진 탐색 트리를 사용하는 영어 사전 프로그램 
int main(void)
{
	char command;

	char list[MAX_WORD_SIZE]; //명령 리스트 확인
	int count = 0; //카운트 변수

	element e; //한-영 사전 구조체
	element e2; //영한-사전 구조체
	TreeNode* root = NULL; //한-영 사전 저장 트리
	TreeNode* root2 = NULL; //영-한 사전 저장 트리
	TreeNode* tmp = NULL;

	TreeNode* korean_copy[MAX_WORD_SIZE];
	TreeNode* english_copy[MAX_WORD_SIZE];
	int korean_count = 0; //한국어 트리 배열 카운트
	int english_count = 0; //영어 트리 배열 카운트
	char* result_korean[MAX_WORD_SIZE];
	char* result_english[MAX_WORD_SIZE];


	do {
		help();
		command = getchar();
		getchar();		// 엔터키 제거
		switch (command) {
		case 'i': // 추가
			//printf("한국어 단어:");
			gets(e.word);
			//printf("영어 단어:");
			gets(e.meaning);

			strcpy(e2.meaning, e.word);
			strcpy(e2.word, e.meaning);
			root = insert_node(root, e);
			root2 = insert_node(root2, e2);
			break;
		case 'p': //출력
			list[count] = 'p';
			count++;
			//printf("K-E dictionary:\n");
			//show_korean(root);
			//printf("E-K dictionary:\n");
			//show_english(root);
			break;
		case 'k': //한국어 단어 검색
			list[count] = 'k';
			count++;
			//printf("한국어 단어:");
			gets(e.word);
			tmp = search_binary_tree(root, e.word);
			korean_copy[korean_count] = tmp;

			if (tmp != NULL) {
				//printf("%s %s\n", tmp->key.word, tmp->key.meaning);
			}
			else {
				result_korean[korean_count] = e.word;
				//printf("%s UNKNOWN ENTRY\n", result_korean[korean_count]);
			}
			korean_count++;
			break;
		case 'e': //영어 단어 검색
			list[count] = 'e';
			count++;
			//printf("영어 단어:");
			gets(e2.word);
			tmp = search_binary_tree(root2, e2.word);
			english_copy[english_count] = tmp;

			if (tmp != NULL) {
				//printf("%s %s\n", tmp->key.meaning, tmp->key.word);
			}
			else {
				result_english[english_count] = e2.word;
				//printf("%s UNKNOWN ENTRY\n", result_english[english_count]);
			}
			english_count++;
			break;
		}
	} while (command != 'q'); //q: 종료

	//출력
	if (command == 'q') {
		for (int a = 0; a < count; a++) {
			if (list[a] == 'k') {
				//printf("token for k\n");
				for (int b = 0; b < korean_count; b++) {
					if (korean_copy[b] != NULL) {
						printf("%s %s\n", korean_copy[b]->key.word, korean_copy[b]->key.meaning);
					}
					else {
						printf("%s UNKNOWN ENTRY\n", result_korean[b]);
					}
				}

			}
			else if (list[a] == 'e') {
				//printf("token for e\n");
				for (int c = 0; c < english_count; c++) {
					if (english_copy[c] != NULL) {
						printf("%s %s\n", english_copy[c]->key.word, english_copy[c]->key.meaning);
					}
					else {
						printf("%s UNKNOWN ENTRY\n", result_english[c]);
					}
				}
			}
			else if (list[a] == 'p') {
				if (root != NULL) {
					printf("K-E dictionary:\n");
					show_word(root);
					printf("E-K dictionary:\n");
					show_word(root2);
				}
			}
			else { continue; }
		}
	}
	return 0;
}
