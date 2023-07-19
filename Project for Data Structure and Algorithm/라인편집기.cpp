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
string editorcopy[MAX_CHAR_PER_LINE]; //라인에 입력된 내용 저장하는 문자열 배열
int stringcount = 0; //카운팅 변수

class Line {
	char data[MAX_CHAR_PER_LINE]; //개행당 1000자까지 저장(데이터 필드)

public:
	Line(const char* line = " ") { strcpy(data, line); }

	//출력
	void print(FILE* fp = stdout, int i = 0) {
		//fprintf(fp, "%s", data);
		editorcopy[i].append(data);
	}

	//비교
	bool hasData(char* str) { return strcmp(str, data) == 0; }
	//(1) str1 < data 인 경우에는 음수 반환
	//(2) str1 > data 인 경우에는 양수 반환
	//(3) str == data 인 경우에는 0을 반환 합니다.

};

class Node : public Line {
	Node* link; //링크 필드

public:
	Node(const char* str = " ") : Line(str), link(NULL) { }

	void setLink(Node* p) { link = p; } //다음 링크 설정

	Node* getLink() { return link; } //링크 값 반환

	void insertNext(Node* p) { //자신 다음에 p 추가
		if (p != NULL) {
			p->link = link;
			link = p;
		}
	}

	Node* removeNext() { //자신 다음의 요소 삭제
		Node* removed = link;
		if (removed != NULL) {
			link = removed->link;
		}
		return removed;
	}
};

class LinkedList {

	Node org; //헤드 노드(헤드 포인터 X)

public:
	LinkedList() : org("") { }
	~LinkedList() { clear(); }

	LinkedList(const LinkedList& origin) : org(origin.org) { }
	//새롭게 메모리 할당

	void clear() { while (!isEmpty()) delete remove(0); }

	Node* getHead() { return org.getLink(); } // 헤드 노드의 값

	bool isEmpty() { return getHead() == NULL; }

	//pos번째 항목 반환
	Node* getEntry(int pos) {
		Node* n = &org;
		for (int i = -1; i < pos; i++, n = n->getLink()) {
			//-1부터 시작하는 이유: 헤드 노드의 주소가 반환되도록 설계
			if (n == NULL) break;
		}
		return n;
	}

	//리스트의 pos 위치에 항목 추가
	void insert(int pos, Node* n) {
		Node* prev = getEntry(pos - 1);
		if (prev != NULL) {
			prev->insertNext(n);
		}
	}

	//리스트의 pos 위치에 항목 삭제
	Node* remove(int pos) {
		Node* prev = getEntry(pos - 1);
		return prev->removeNext();
	}

	//탐색
	Node* find(char* val) {
		for (Node* p = getHead(); p != NULL; p = p->getLink()) {
			if (p->hasData(val)) return p;
		}
		return NULL;
	}

	//pos번째 노드를 다른 노드로 교체
	void replace(int pos, Node* n) {
		Node* prev = getEntry(pos - 1);
		if (prev != NULL) {
			delete prev->removeNext();
			prev->insertNext(n);
		}
	}

	//pos번째 val을 find + replace 후 n 반환(자료구조에서 새롭게 요구하는 함수) 
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

	//val을 find + replace 후 n 반환
	Node* find_and_replace_number_return2(char* val, Node* n) {
		Node* p = getHead(); //헤드 노드
		Node* prev = &org; //헤드 노드의 주소를 가리킴
		while (p != NULL) {
			if (p->hasData(val)) { //val 값이 있을 때
				prev->setLink(n); //prev는 n을 가리킨다.
				n->setLink(p->getLink()); // n은 p의 다음 링크를 가리킨다.
				delete p; // p를 삭제한다.
				return n;
			}
			prev = p;
			p = p->getLink(); //다음 링크값을 따란다.
		}
		return NULL;
	}


	//리스트 항목 개수 반환
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

	//새롭게 메모리 할당
	LineEditor(const LineEditor& origin) : LinkedList(origin) {	}


	//출력
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

	//한 라인 입력 처리
	void InsertLine() {
		int position;
		char line[MAX_CHAR_PER_LINE];
		//printf("  입력행 번호: ");
		//scanf("%d", &position);
		cin >> position;
		//printf("  입력행 내용: ");
		while (getchar() != '\n');
		//엔터키 처리
		//제대로 입력이 처리되지 않을 때 입력 버퍼를 지워주기 위해 사용하는 함수

		fgets(line, MAX_CHAR_PER_LINE, stdin);
		//키보드 표준입출력에서 MAX_CHAR_PER_LINE의 길이만큼 line에 문자열을 넣고, 그것을 반환
		insert(position, new Node(line));
	}

	void DeleteLine() { //한 라인 삭제 처리
		//printf("  삭제행 번호: ");
		int position;
		//scanf("%d", &position);
		cin >> position;
		delete remove(position);
	}

	void ReplaceLine() { //한 라인 변경 처리
		int position;
		char line[MAX_CHAR_PER_LINE];
		//printf("  변경행 번호: ");
		//scanf("%d", &position);
		cin >> position;

		//printf("  변경행 내용: ");
		while (getchar() != '\n');
		//엔터키 처리
		//제대로 입력이 처리되지 않을 때 입력 버퍼를 지워주기 위해 사용하는 함수

		fgets(line, MAX_CHAR_PER_LINE, stdin);

		replace(position, new Node(line));
		//fflush(stdin); -> 불필요한 작업
	}

	void LoadFile(const char* fname) {
		FILE* fp = fopen(fname, "r"); //fname을 읽기 전용으로 엽니다.
		if (fp != NULL) {
			char line[MAX_CHAR_PER_LINE];
			while (fgets(line, MAX_CHAR_PER_LINE, fp)) {
				insert(size(), new Node(line));
			}
		}
		fclose(fp);
	}

	void StoreFile(const char* fname) {
		FILE* fp = fopen(fname, "w"); //fname을 쓰기 전용으로 엽니다.
		if (fp != NULL) {
			Display(fp);
			fclose(fp);
		}
		printf("\n");
	}

	void Findreplace() {

		char finding[MAX_CHAR_PER_LINE]; //찾을 문자열
		char line[MAX_CHAR_PER_LINE]; //바꿀 문자열 복사
		//char line[MAX_CHAR_PER_LINE]; //바꿀 문자열

		//printf("  찾을 내용: ");
		while (getchar() != '\n');
		fgets(finding, MAX_CHAR_PER_LINE, stdin);

		//printf("  바꿀 내용: ");
		fgets(line, MAX_CHAR_PER_LINE, stdin);

		find_and_replace_number_return2(finding, new Node(line));
	}

};

void Usage() {
	//printf("[메뉴선택] i-입력, d-삭제, r-변경, p-출력, l-파일읽기, s-저장, q-종료, f-찾아 바꾸기=> ");
}

int main() {

	char command = NULL; //변수 초기화
	LineEditor editor; //입력값을 담는 객체

	do {
		command = NULL;

		if (command != 'r') { //임시방편
			Usage();
		}

		cin >> command;
		//command = getchar();, 디버깅 결과, getchar 쓰면 Usage가 두 번 돌음

		switch (command) {
		case 'd': editor.DeleteLine(); break;
		case 'i': editor.InsertLine(); break;
		case 'r': editor.ReplaceLine(); break;
		case 'l': editor.LoadFile("c:\\Users\\jeong\\Desktop\\Test.txt"); break;
		case 's': editor.StoreFile("c:\\Users\\jeong\\Desktop\\Test.txt"); break;
		case 'p': editor.Display(); break;
		case 'f': editor.Findreplace(); break;
		}
		//fflush(stdin); //입력 버퍼 비우기
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