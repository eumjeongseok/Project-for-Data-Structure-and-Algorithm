#pragma once
#include <cstdio>
#include <stdio.h>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

#define MAX_CHAR_PER_LINE 1000
#pragma warning(disable:4996)
string editorcopy[MAX_CHAR_PER_LINE]; //���ο� �Էµ� ���� �����ϴ� ���ڿ� �迭
int stringcount = 0; //ī���� ����

class Line {
	char data[MAX_CHAR_PER_LINE]; //����� 1000�ڱ��� ����(������ �ʵ�)

public:
	Line(const char* line = " ") { strcpy(data, line); }

	//���
	void print(FILE* fp = stdout, int i = 0) {
		//fprintf(fp, "%s", data);
		editorcopy[i].append(data);
	}

	//��
	bool hasData(char* str) { return strcmp(str, data) == 0; }
	//(1) str1 < data �� ��쿡�� ���� ��ȯ
	//(2) str1 > data �� ��쿡�� ��� ��ȯ
	//(3) str == data �� ��쿡�� 0�� ��ȯ �մϴ�.

};

class Node : public Line {
	Node* link; //��ũ �ʵ�

public:
	Node(const char* str = " ") : Line(str), link(NULL) { }

	void setLink(Node* p) { link = p; } //���� ��ũ ����

	Node* getLink() { return link; } //��ũ �� ��ȯ

	void insertNext(Node* p) { //�ڽ� ������ p �߰�
		if (p != NULL) {
			p->link = link;
			link = p;
		}
	}

	Node* removeNext() { //�ڽ� ������ ��� ����
		Node* removed = link;
		if (removed != NULL) {
			link = removed->link;
		}
		return removed;
	}
};

class LinkedList {

	Node org; //��� ���(��� ������ X)

public:
	LinkedList() : org("") { }
	~LinkedList() { clear(); }

	LinkedList(const LinkedList& origin) : org(origin.org) { }
	//���Ӱ� �޸� �Ҵ�

	void clear() { while (!isEmpty()) delete remove(0); }

	Node* getHead() { return org.getLink(); } // ��� ����� ��

	bool isEmpty() { return getHead() == NULL; }

	//pos��° �׸� ��ȯ
	Node* getEntry(int pos) {
		Node* n = &org;
		for (int i = -1; i < pos; i++, n = n->getLink()) {
			//-1���� �����ϴ� ����: ��� ����� �ּҰ� ��ȯ�ǵ��� ����
			if (n == NULL) break;
		}
		return n;
	}

	//����Ʈ�� pos ��ġ�� �׸� �߰�
	void insert(int pos, Node* n) {
		Node* prev = getEntry(pos - 1);
		if (prev != NULL) {
			prev->insertNext(n);
		}
	}

	//����Ʈ�� pos ��ġ�� �׸� ����
	Node* remove(int pos) {
		Node* prev = getEntry(pos - 1);
		return prev->removeNext();
	}

	//Ž��
	Node* find(char* val) {
		for (Node* p = getHead(); p != NULL; p = p->getLink()) {
			if (p->hasData(val)) return p;
		}
		return NULL;
	}

	//pos��° ��带 �ٸ� ���� ��ü
	void replace(int pos, Node* n) {
		Node* prev = getEntry(pos - 1);
		if (prev != NULL) {
			delete prev->removeNext();
			prev->insertNext(n);
		}
	}

	//pos��° val�� find + replace �� n ��ȯ(�ڷᱸ������ ���Ӱ� �䱸�ϴ� �Լ�) 
	Node* find_and_replace_number_return(int pos, char* val, Node* n) {

		for (Node* p = getHead(); p != NULL; p = p->getLink()) {
			if (p->hasData(val) == true) {
				Node* prev = getEntry(pos - 1);

				if (prev != NULL) {
					delete prev->removeNext();
					prev->insertNext(n);
					return prev;
				}
			}
		}
		return NULL;
	}

	//val�� find + replace �� n ��ȯ
	Node* find_and_replace_number_return2(char* val, Node* n) {
		Node* p = getHead(); //��� ���
		Node* prev = &org; //��� ����� �ּҸ� ����Ŵ
		while (p != NULL) {
			if (p->hasData(val)) { //val ���� ���� ��
				prev->setLink(n); //prev�� n�� ����Ų��.
				n->setLink(p->getLink()); // n�� p�� ���� ��ũ�� ����Ų��.
				delete p; // p�� �����Ѵ�.
				return n;
			}
			prev = p;
			p = p->getLink(); //���� ��ũ���� ������.
		}
		return NULL;
	}


	//����Ʈ �׸� ���� ��ȯ
	int size() {
		int count = 0;
		for (Node* p = getHead(); p != NULL; p = p->getLink()) {
			count++;
		}
		return count;
	}
};

class LineEditor : public LinkedList {

public:

	LineEditor() { }
	~LineEditor() { }

	//���Ӱ� �޸� �Ҵ�
	LineEditor(const LineEditor& origin) : LinkedList(origin) {	}


	//���
	void Display(FILE* fp = stdout) {
		int i = 0;
		for (Node* p = getHead(); p != NULL; p = p->getLink(), i++) {
			//fprintf(stderr, "%3d ", i);
			p->print(fp, stringcount);
			stringcount++;
		}
		editorcopy[stringcount] = "EOF";
		stringcount++;
	}

	//�� ���� �Է� ó��
	void InsertLine() {
		int position;
		char line[MAX_CHAR_PER_LINE];
		//printf("  �Է��� ��ȣ: ");
		//scanf("%d", &position);
		cin >> position;
		//printf("  �Է��� ����: ");
		while (getchar() != '\n');
		//����Ű ó��
		//����� �Է��� ó������ ���� �� �Է� ���۸� �����ֱ� ���� ����ϴ� �Լ�

		fgets(line, MAX_CHAR_PER_LINE, stdin);
		//Ű���� ǥ������¿��� MAX_CHAR_PER_LINE�� ���̸�ŭ line�� ���ڿ��� �ְ�, �װ��� ��ȯ
		insert(position, new Node(line));
	}

	void DeleteLine() { //�� ���� ���� ó��
		//printf("  ������ ��ȣ: ");
		int position;
		//scanf("%d", &position);
		cin >> position;
		delete remove(position);
	}

	void ReplaceLine() { //�� ���� ���� ó��
		int position;
		char line[MAX_CHAR_PER_LINE];
		//printf("  ������ ��ȣ: ");
		//scanf("%d", &position);
		cin >> position;

		//printf("  ������ ����: ");
		while (getchar() != '\n');
		//����Ű ó��
		//����� �Է��� ó������ ���� �� �Է� ���۸� �����ֱ� ���� ����ϴ� �Լ�

		fgets(line, MAX_CHAR_PER_LINE, stdin);

		replace(position, new Node(line));
		//fflush(stdin); -> ���ʿ��� �۾�
	}

	void LoadFile(const char* fname) {
		FILE* fp = fopen(fname, "r"); //fname�� �б� �������� ���ϴ�.
		if (fp != NULL) {
			char line[MAX_CHAR_PER_LINE];
			while (fgets(line, MAX_CHAR_PER_LINE, fp)) {
				insert(size(), new Node(line));
			}
		}
		fclose(fp);
	}

	void StoreFile(const char* fname) {
		FILE* fp = fopen(fname, "w"); //fname�� ���� �������� ���ϴ�.
		if (fp != NULL) {
			Display(fp);
			fclose(fp);
		}
		printf("\n");
	}

	void Findreplace() {

		char finding[MAX_CHAR_PER_LINE]; //ã�� ���ڿ�
		char line[MAX_CHAR_PER_LINE]; //�ٲ� ���ڿ� ����
		//char line[MAX_CHAR_PER_LINE]; //�ٲ� ���ڿ�

		//printf("  ã�� ����: ");
		while (getchar() != '\n');
		fgets(finding, MAX_CHAR_PER_LINE, stdin);

		//printf("  �ٲ� ����: ");
		fgets(line, MAX_CHAR_PER_LINE, stdin);

		find_and_replace_number_return2(finding, new Node(line));
	}

};

void Usage() {
	//printf("[�޴�����] i-�Է�, d-����, r-����, p-���, l-�����б�, s-����, q-����, f-ã�� �ٲٱ�=> ");
}

int main() {

	char command = NULL; //���� �ʱ�ȭ
	LineEditor editor; //�Է°��� ��� ��ü

	do {
		command = NULL;

		if (command != 'r') { //�ӽù���
			Usage();
		}

		cin >> command;
		//command = getchar();, ����� ���, getchar ���� Usage�� �� �� ����

		switch (command) {
		case 'd': editor.DeleteLine(); break;
		case 'i': editor.InsertLine(); break;
		case 'r': editor.ReplaceLine(); break;
		case 'l': editor.LoadFile("c:\\Users\\jeong\\Desktop\\Test.txt"); break;
		case 's': editor.StoreFile("c:\\Users\\jeong\\Desktop\\Test.txt"); break;
		case 'p': editor.Display(); break;
		case 'f': editor.Findreplace(); break;
		}
		//fflush(stdin); //�Է� ���� ����
	} while (command != 'q');

	if (command == 'q') {
		int sum = 0;
		for (int i = 0; i < stringcount; i++) {
			if (editorcopy[i] == "EOF") {
				cout << editorcopy[i] << "\n";
				sum = 0;
			}
			else {
				cout << sum << ": " << editorcopy[i];
				sum++;
			}
		}
	}

	return 0;
}