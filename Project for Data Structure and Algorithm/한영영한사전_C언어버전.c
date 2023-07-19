// ���� Ž�� Ʈ���� ����� ���� ����
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_WORD_SIZE	 100
#define MAX_MEANING_SIZE 200

// ������ ����
typedef struct {
	char word[MAX_WORD_SIZE];		// Ű�ʵ�
	char meaning[MAX_MEANING_SIZE];
} element;
// ����� ����
typedef struct TreeNode {
	element key;
	struct TreeNode* left, * right;
} TreeNode;

// ���� e1 < e2 �̸� -1 ��ȯ
// ���� e1 == e2 �̸� 0 ��ȯ
// ���� e1 > e2 �̸� 1 ��ȯ
int compare(element e1, element e2) {
	int result = strcmp(e1.word, e2.word);
	if (result < 0)
		return -1;
	else if (result > 0)
		return 1;
	else
		return 0;
}

// ���� Ž�� Ʈ�� Ž�� �Լ�(���� ������)
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
	return NULL;  // Ž���� �������� ��� NULL ��ȯ
}

TreeNode* new_node(element item) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}
TreeNode* insert_node(TreeNode* node, element key) {
	// Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�. 
	if (node == NULL) return new_node(key);

	// �׷��� ������ ��ȯ������ Ʈ���� ��������. 
	if (compare(key, node->key) < 0)
		node->left = insert_node(node->left, key);
	else if (compare(key, node->key) > 0)
		node->right = insert_node(node->right, key);

	// ��Ʈ �����͸� ��ȯ�Ѵ�. 
	return node;
}

// ���� Ž�� Ʈ�� Ž�� �Լ�(�ܾ� �˻�)
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
	return NULL;  // Ž���� �������� ��� NULL ��ȯ
}

// ���� Ž�� Ʈ�� ��� �Լ�
void show_word(TreeNode* p) {
	if (p != NULL) {
		show_word(p->left);
		printf("%s %s\n", p->key.word, p->key.meaning);
		show_word(p->right);
	}
}

void help() {
	//printf("**** i: �Է�, k: �ѱ��� �ܾ� �˻�, e: ���� �ܾ� �˻�, p: ���, q: ���� ****: ");
}
// ���� Ž�� Ʈ���� ����ϴ� ���� ���� ���α׷� 
int main(void)
{
	char command;

	char list[MAX_WORD_SIZE]; //��� ����Ʈ Ȯ��
	int count = 0; //ī��Ʈ ����

	element e; //��-�� ���� ����ü
	element e2; //����-���� ����ü
	TreeNode* root = NULL; //��-�� ���� ���� Ʈ��
	TreeNode* root2 = NULL; //��-�� ���� ���� Ʈ��
	TreeNode* tmp = NULL;

	TreeNode* korean_copy[MAX_WORD_SIZE];
	TreeNode* english_copy[MAX_WORD_SIZE];
	int korean_count = 0; //�ѱ��� Ʈ�� �迭 ī��Ʈ
	int english_count = 0; //���� Ʈ�� �迭 ī��Ʈ
	char* result_korean[MAX_WORD_SIZE];
	char* result_english[MAX_WORD_SIZE];


	do {
		help();
		command = getchar();
		getchar();		// ����Ű ����
		switch (command) {
		case 'i': // �߰�
			//printf("�ѱ��� �ܾ�:");
			gets(e.word);
			//printf("���� �ܾ�:");
			gets(e.meaning);

			strcpy(e2.meaning, e.word);
			strcpy(e2.word, e.meaning);
			root = insert_node(root, e);
			root2 = insert_node(root2, e2);
			break;
		case 'p': //���
			list[count] = 'p';
			count++;
			//printf("K-E dictionary:\n");
			//show_korean(root);
			//printf("E-K dictionary:\n");
			//show_english(root);
			break;
		case 'k': //�ѱ��� �ܾ� �˻�
			list[count] = 'k';
			count++;
			//printf("�ѱ��� �ܾ�:");
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
		case 'e': //���� �ܾ� �˻�
			list[count] = 'e';
			count++;
			//printf("���� �ܾ�:");
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
	} while (command != 'q'); //q: ����

	//���
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
