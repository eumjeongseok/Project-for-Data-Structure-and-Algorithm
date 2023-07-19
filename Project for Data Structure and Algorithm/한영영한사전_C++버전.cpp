#define _CRT_SECURE_NO_WARNINGS //strcpy ������ �־�� �մϴ�.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <conio.h> //getche()�� ���� ���� ���
#include <iostream>
using namespace std;
#define MAX_WORD_SIZE 40
#define MAX_MEANING_SIZE 200
#define MAX_QUEUE_SIZE 100

//������ ���� ���ڵ� Ŭ����
class Record {

public:
	char word[MAX_WORD_SIZE];
	char meaning[MAX_MEANING_SIZE];

	Record(const char* w = "", const char* m = "") { set(w, m); } //""�� ���� ���� ���� ���� �߻�!
	void set(const char* w, const char* m) {
		strcpy(word, w);
		strcpy(meaning, m);
	}

	//���� ���ڵ��� word �ʵ�� ���ڿ� w ��
	int compare(Record* n) { return compare(n->word); }
	int compare(char* w) { return strcmp(w, word); }

	//�ǹ̸� �̿��� �˻�
	int compareMeaning(char* m) { return strcmp(meaning, m); }

	//���: "�ܾ� : �ǹ�"
	void display() {
		printf("%s %s\n", word, meaning);
	}

	//���ڵ� n�� ������ �ڽſ� ����
	void copy(Record* n) { set(n->word, n->meaning); }
};

class BinaryNode : public Record {
	BinaryNode* left;
	BinaryNode* right;

public:
	BinaryNode(const char* w, const char* m) : Record(w, m), left(NULL), right(NULL) {}

	//���� �ڽ�, ������ �ڽ� ����
	void setData(char* val) { strcpy(word, val); } //���� �κ� �߰�!
	void setLeft(BinaryNode* l) { left = l; }
	void setRight(BinaryNode* r) { right = r; }

	//���� �ڽ�, ������ �ڽ� ��ȯ
	char* getData() { return word; } //��尪 ��ȯ, ���� �κ� �߰�!
	char* getMeaning() { return meaning; }
	BinaryNode* getLeft() { return left; }
	BinaryNode* getRight() { return right; }

	//�� ���(�ܸ� ���) ��ȯ: ���� �ڽİ� ������ �ڽ� ��� ���� �� true
	bool isLeaf() { return (left == NULL) && (right == NULL); }
};

class CircularQueue {
	int front = 0;
	int rear = 0;
	BinaryNode* data[MAX_QUEUE_SIZE] = { };

public:
	CircularQueue() { front = rear = 0; }
	bool isEmpty() { return front == rear; }
	bool isFull() { return ((rear + 1) % MAX_QUEUE_SIZE) == front; }
	void enqueue(BinaryNode* n) {
		if (isFull()) { printf("  Error: ť�� ��ȭ�����Դϴ�.\n"); }
		else {
			rear = (rear + 1) % MAX_QUEUE_SIZE;
			data[rear] = n;
		}
	}
	BinaryNode* dequeue() {
		if (isEmpty()) { printf("  Error: ť�� ��������Դϴ�.\n"); }
		else {
			front = (front + 1) % MAX_QUEUE_SIZE;
			return data[front];
		}
	}
};

class BinaryTree {
protected:
	BinaryNode* root;

public:
	BinaryTree() : root(NULL) { }
	BinaryNode* getRoot() { return root; }

	bool isEmpty() { return root == NULL; } //��Ʈ�� �ִ� Ʈ�������� ���� Ȯ��

	//����Ʈ���� ��ȸ ����
	void inorder(BinaryNode* node) {
		//���� ��ȸ: LVR
		if (node != NULL) { //��Ʈ ��尡 0�� �ƴ� ��
			inorder(node->getLeft()); //���� ����Ʈ��
			node->display(); //��Ʈ ��� ó��
			inorder(node->getRight()); //������ ����Ʈ��
		}
	}
};

class BinSrchTree : public BinaryTree {
public:
	//���� Ž�� Ʈ���� Ž�� ����
	BinaryNode* search(char* key) { return searchRecur(root, key); }
	//Ű ������ ��带 Ž���ϴ� �Լ�(��ȯ�� ���)
	//�Ϲ� �Լ��� ����(BinSrchTree�� ��� �Լ��� �־ ��)
	BinaryNode* searchRecur(BinaryNode* n, char* key) {
		if (n == NULL) { return NULL; }
		if (n->compare(key) == 0) { return n; }
		else if (n->compare(key) < 0) { return searchRecur(n->getLeft(), key); }
		else return searchRecur(n->getRight(), key);
	}

	//��Ʈ ��尡 �ִ°��� ����
	bool hasData() { return getRoot(); }

	//���� Ž�� Ʈ���� ���� ����
	void insert(BinaryNode* n) {
		if (n == NULL) { return; }
		if (isEmpty()) { root = n; }
		else { insertRucur(root, n); }

	}
	//���� Ž�� Ʈ���� ���� �Լ�
	void insertRucur(BinaryNode* r, BinaryNode* n) {
		//root�� key�� ������ return
		if (n->compare(r) == 0) { return; }
		//root���� key�� ���� ��
		else if (n->compare(r) > 0) {
			if (r->getLeft() == NULL) { r->setLeft(n); } //root�� ���� �ڽ��� ������ n�� ���� �ڽ�
			else { insertRucur(r->getLeft(), n); } //root�� ���� �ڽ��� ������ ��ȯ ȣ��
		}
		//root���� key�� Ŭ ��
		else {
			if (r->getRight() == NULL) { r->setRight(n); } //root�� ������ �ڽ��� ������ n�� ������ �ڽ�
			else { insertRucur(r->getRight(), n); } //root�� ������ �ڽ��� ������ ��ȯ ȣ��
		}
	}


	//=============================================================

	//���� Ž�� Ʈ���� ���� ����
	void remove(char* key) {
		if (isEmpty()) { return; } //�� Ʈ���̸� return

		//���� ���� �� ����� �θ� ��带 ã�´�.
		BinaryNode* parent = NULL;
		BinaryNode* node = root;
		while (node != NULL && node->compare(key) != 0) {
			parent = node;
			node = (node->compare(key) < 0) ? node->getLeft() : node->getRight();
		}
		//���� ��尡 Ʈ���� ����
		if (node == NULL) {
			printf("Error: Ű�� Ʈ���� �����ϴ�.\n");
			return;
		}
		//���� ��尡 Ʈ���� ����
		else { remove(parent, node); }
	}
	void remove(BinaryNode* parent, BinaryNode* node) {
		//case 1: �����Ϸ��� ��尡 �ܸ� ����� ��� ->�ܸ� ����� ��ũ�� ���´�.
		if (node->isLeaf()) {
			if (parent == NULL) { root = NULL; } //node == root�̸� �������
			else { //node != root�� ���
				if (parent->getLeft() == node) {
					parent->setLeft(NULL);
				}
				else {
					parent->setRight(NULL);
				}
			}
		}
		//case 2: �����Ϸ��� ��尡 �����̳� ������ �ڽĸ� ���� ���
		else if (node->getLeft() == NULL || node->getRight() == NULL) {
			//������ ����� ������ �ڽ� ��� => child
			BinaryNode* child = (node->getLeft() != NULL) ?
				node->getLeft() : node->getRight();
			//������ ��尡 ��Ʈ�̸� ==> child�� ���ο� root�� ��
			if (node == root) { root = child; }
			else {
				if (parent->getLeft() == node) {
					parent->setLeft(child);
				}
				else {
					parent->setRight(child);
				}
			}
		}
		//case 3: �����Ϸ��� ��尡 �� ���� �ڽ��� ��� �ִ� ���
		else {
			//�����Ϸ��� ����� ������ ����Ʈ������ ���� ���� ��带 Ž��
			//succp => �İ� ����� �θ� ���
			//succ => �İ� ���: ������ ����Ʈ������ ���� key�� ���� ���
			BinaryNode* succp = node;
			BinaryNode* succ = node->getRight();

			while (succ->getLeft() != NULL) { //�İ� ��� Ž��
				succp = succ; //�İ� ����� �θ� ���
				succ = succ->getLeft(); //�İ� ���
			}
			//�İ� ����� �θ�� �İ� ����� ������ �ڽ��� ���� ����
			if (succp->getLeft() == succ) {
				succp->setLeft(succ->getRight());
			}
			else { //�İ� ��尡 ������ ����� �ٷ� ������ �ڽ��� ���
				succp->setRight(succ->getRight());
				//�İ� ��� ������ ������ ��忡 ����
			}
			node->setData(succ->getData());
			//������ ��带 �İ� ���� ����: �����δ� �İ� ��尡 ���ŵ�
			//word�� ��ȯ�ص� ��������? -> �ϴ� ���߿� ���캸��...�Ф�
			node = succ;
		}
		delete node; //�޸� ���� ����
	}
};

class Dictionary : public BinSrchTree {
public:
	//���� ��ȸ�ϸ鼭, �� ����� �ܾ�� �ǹ� ���
	void printAllWords() {
		//printf("     >> ���� �ܾ���:\n");
		if (!isEmpty()) { inorder(root); }
	}
	//�ܾ ���� �˻� ����
	BinaryNode* searchWord(char* word) {
		BinaryNode* node = search(word);
		if (node != NULL) {
			return node;
			//printf("     >> ");
			//node->display();
		}
		else {
			//printf("     >> ��ϵ��� ���� �ǹ�: %s\n", word); 
			return NULL;
		}
		return NULL;
	}
};

void help() {
	//printf("[����] i-�߰�, k-�ѱ��� �ܾ� �˻�, e-���� �ܾ� �˻�, p-���, q-���� =>");
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	char* result_korean[MAX_WORD_SIZE];
	char* result_english[MAX_WORD_SIZE];
	int korean_count = 0; //�ѱ��� Ʈ�� �迭 ī��Ʈ
	int english_count = 0; //���� Ʈ�� �迭 ī��Ʈ

	char list[MAX_WORD_SIZE]; //��� ����Ʈ Ȯ��
	int count = 0; //ī��Ʈ ����

	char command;

	char word[80]; //�ѿ����� �ѱ��� �ܾ�
	char meaning[200]; //�ѿ����� ���� �ܾ�
	Dictionary tree; //�ѿ�����

	char word2[80]; //���ѻ��� ���� �ܾ�
	char meaning2[200]; //���ѻ��� �ѱ��� �ܾ�
	Dictionary tree2; //���ѻ���

	BinaryNode* tmp = NULL; //���� ������ �ӽ� ����(�ѿ�����)
	BinaryNode* tmp2 = NULL; //���� ������ �ӽ� ����(���ѻ���)
	BinaryNode* korean_copy[MAX_WORD_SIZE];
	BinaryNode* english_copy[MAX_WORD_SIZE];

	do {
		help();
		cin >> command;
		while (getchar() != '\n');
		//command = _getche(); //Ű���带 ġ�� ���� �����Ͽ� ����Ű ���� �ٷ� �� Ű���� ���� �Է�, _getche()�� �ؾ� ���� ���� X
		//printf("\n");
		switch (command) {
		case 'i':
			//printf("   > �ѱ��� �ܾ�: "); 
			cin.getline(word, 80, '\n');//���� gets ����� VS 2022���� �ƿ� �ν� X
			strcpy(meaning2, word);
			//printf("   > ���� �ܾ�: "); 
			cin.getline(meaning, 200, '\n');
			strcpy(word2, meaning);
			tree.insert(new BinaryNode(word, meaning));
			tree2.insert(new BinaryNode(word2, meaning2));
			break;

		case 'k':
			//printf("   > �˻� �ܾ�: "); 
			cin.getline(word, 80, '\n');
			tmp = tree.searchWord(word);
			korean_copy[korean_count] = tmp;
			list[count] = 'k';
			count++;
			if (tmp != NULL) {
				//printf("%s %s\n", tmp->getData(), tmp->getData());
			}
			else {
				result_korean[korean_count] = word;
				//printf("%s UNKNOWN ENTRY\n", result_korean[korean_count]);
			}
			korean_count++;
			break;

		case 'e':
			//printf("   > �˻� �ܾ�: "); 
			cin.getline(word2, 80, '\n');
			tmp2 = tree2.searchWord(word2);
			english_copy[english_count] = tmp2;
			list[count] = 'e';
			count++;
			if (tmp2 != NULL) {
				//printf("%s %s\n", tmp->key.meaning, tmp->key.word);
			}
			else {
				result_english[english_count] = word2;
				//printf("%s UNKNOWN ENTRY\n", result_english[english_count]);
			}
			english_count++;
			break;

		case 'p':
			//printf("K-E Dictionary");
			//tree.printAllWords(); 
			//printf("K-E Dictionary");
			//tree2.printAllWords();
			//printf("\n");
			list[count] = 'p';
			count++;
			break;
		}

	} while (command != 'q');

	if (command == 'q') {
		for (int a = 0; a < count; a++) {
			if (list[a] == 'k') {
				//printf("token for k\n");
				for (int b = 0; b < korean_count; b++) {
					if (korean_copy[b] != NULL) {
						printf("%s %s\n", korean_copy[b]->getData(), korean_copy[b]->getMeaning());
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
						printf("%s %s\n", english_copy[c]->getData(), english_copy[c]->getMeaning());
					}
					else {
						printf("%s UNKNOWN ENTRY\n", result_english[c]);
					}
				}
			}
			else if (list[a] == 'p') {
				if (tree.hasData() == true && tree2.hasData() == true) {
					printf("K-E dictionary:\n");
					tree.printAllWords();
					printf("E-K dictionary:\n");
					tree2.printAllWords();
				}
			}
			else { continue; }
		}
	}

	return 0;
}
