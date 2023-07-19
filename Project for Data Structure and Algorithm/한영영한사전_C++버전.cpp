#define _CRT_SECURE_NO_WARNINGS //strcpy 때문에 있어야 합니다.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <conio.h> //getche()를 쓰기 위한 헤더
#include <iostream>
using namespace std;
#define MAX_WORD_SIZE 40
#define MAX_MEANING_SIZE 200
#define MAX_QUEUE_SIZE 100

//사전을 위한 레코드 클래스
class Record {

public:
	char word[MAX_WORD_SIZE];
	char meaning[MAX_MEANING_SIZE];

	Record(const char* w = "", const char* m = "") { set(w, m); } //""이 들어가니 변수 유형 오류 발생!
	void set(const char* w, const char* m) {
		strcpy(word, w);
		strcpy(meaning, m);
	}

	//현재 레코드의 word 필드와 문자열 w 비교
	int compare(Record* n) { return compare(n->word); }
	int compare(char* w) { return strcmp(w, word); }

	//의미를 이용한 검색
	int compareMeaning(char* m) { return strcmp(meaning, m); }

	//출력: "단어 : 의미"
	void display() {
		printf("%s %s\n", word, meaning);
	}

	//레코드 n의 내용을 자신에 복사
	void copy(Record* n) { set(n->word, n->meaning); }
};

class BinaryNode : public Record {
	BinaryNode* left;
	BinaryNode* right;

public:
	BinaryNode(const char* w, const char* m) : Record(w, m), left(NULL), right(NULL) {}

	//왼쪽 자식, 오른쪽 자식 설정
	void setData(char* val) { strcpy(word, val); } //빠진 부분 추가!
	void setLeft(BinaryNode* l) { left = l; }
	void setRight(BinaryNode* r) { right = r; }

	//왼쪽 자식, 오른쪽 자식 반환
	char* getData() { return word; } //노드값 반환, 빠진 부분 추가!
	char* getMeaning() { return meaning; }
	BinaryNode* getLeft() { return left; }
	BinaryNode* getRight() { return right; }

	//잎 노드(단말 노드) 반환: 왼쪽 자식과 오른쪽 자식 모두 없을 때 true
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
		if (isFull()) { printf("  Error: 큐가 포화상태입니다.\n"); }
		else {
			rear = (rear + 1) % MAX_QUEUE_SIZE;
			data[rear] = n;
		}
	}
	BinaryNode* dequeue() {
		if (isEmpty()) { printf("  Error: 큐가 공백상태입니다.\n"); }
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

	bool isEmpty() { return root == NULL; } //루트만 있는 트리인지의 여부 확인

	//이진트리의 순회 연산
	void inorder(BinaryNode* node) {
		//중위 순회: LVR
		if (node != NULL) { //루트 노드가 0이 아닐 때
			inorder(node->getLeft()); //왼쪽 서브트리
			node->display(); //루트 노드 처리
			inorder(node->getRight()); //오른쪽 서브트리
		}
	}
};

class BinSrchTree : public BinaryTree {
public:
	//이진 탐색 트리의 탐색 연산
	BinaryNode* search(char* key) { return searchRecur(root, key); }
	//키 값으로 노드를 탐색하는 함수(순환적 방법)
	//일반 함수로 구현(BinSrchTree의 멤버 함수로 넣어도 됨)
	BinaryNode* searchRecur(BinaryNode* n, char* key) {
		if (n == NULL) { return NULL; }
		if (n->compare(key) == 0) { return n; }
		else if (n->compare(key) < 0) { return searchRecur(n->getLeft(), key); }
		else return searchRecur(n->getRight(), key);
	}

	//루트 노드가 있는가의 여부
	bool hasData() { return getRoot(); }

	//이진 탐색 트리의 삽입 연산
	void insert(BinaryNode* n) {
		if (n == NULL) { return; }
		if (isEmpty()) { root = n; }
		else { insertRucur(root, n); }

	}
	//이진 탐색 트리의 삼입 함수
	void insertRucur(BinaryNode* r, BinaryNode* n) {
		//root와 key가 같으면 return
		if (n->compare(r) == 0) { return; }
		//root보다 key가 작을 때
		else if (n->compare(r) > 0) {
			if (r->getLeft() == NULL) { r->setLeft(n); } //root의 왼쪽 자식이 없으면 n이 왼쪽 자식
			else { insertRucur(r->getLeft(), n); } //root에 왼쪽 자식이 있으면 순환 호출
		}
		//root보다 key가 클 때
		else {
			if (r->getRight() == NULL) { r->setRight(n); } //root의 오른쪽 자식이 없으면 n이 오른쪽 자식
			else { insertRucur(r->getRight(), n); } //root에 오른쪽 자식이 있으면 순환 호출
		}
	}


	//=============================================================

	//이진 탐색 트리의 삭제 연산
	void remove(char* key) {
		if (isEmpty()) { return; } //빈 트리이면 return

		//없앨 노드와 그 노드의 부모 노드를 찾는다.
		BinaryNode* parent = NULL;
		BinaryNode* node = root;
		while (node != NULL && node->compare(key) != 0) {
			parent = node;
			node = (node->compare(key) < 0) ? node->getLeft() : node->getRight();
		}
		//없앨 노드가 트리에 없음
		if (node == NULL) {
			printf("Error: 키가 트리에 없습니다.\n");
			return;
		}
		//없앨 노드가 트리에 있음
		else { remove(parent, node); }
	}
	void remove(BinaryNode* parent, BinaryNode* node) {
		//case 1: 삭제하려는 노드가 단말 노드인 경우 ->단말 노드의 링크를 끊는다.
		if (node->isLeaf()) {
			if (parent == NULL) { root = NULL; } //node == root이면 공백상태
			else { //node != root인 경우
				if (parent->getLeft() == node) {
					parent->setLeft(NULL);
				}
				else {
					parent->setRight(NULL);
				}
			}
		}
		//case 2: 삭제하려는 노드가 왼쪽이나 오른쪽 자식만 갖는 경우
		else if (node->getLeft() == NULL || node->getRight() == NULL) {
			//삭제할 노드의 유일한 자식 노드 => child
			BinaryNode* child = (node->getLeft() != NULL) ?
				node->getLeft() : node->getRight();
			//삭제할 노드가 루트이면 ==> child가 새로운 root가 됨
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
		//case 3: 삭제하려는 노드가 두 개의 자식이 모두 있는 경우
		else {
			//삭제하려는 노드의 오른쪽 서브트리에서 가장 작은 노드를 탐색
			//succp => 후계 노드의 부모 노드
			//succ => 후계 노드: 오른쪽 서브트리에서 가장 key가 작은 노드
			BinaryNode* succp = node;
			BinaryNode* succ = node->getRight();

			while (succ->getLeft() != NULL) { //후계 노드 탐색
				succp = succ; //후계 노드의 부모 노드
				succ = succ->getLeft(); //후계 노드
			}
			//후계 노드의 부모와 후계 노드의 오른쪽 자식을 직접 연결
			if (succp->getLeft() == succ) {
				succp->setLeft(succ->getRight());
			}
			else { //후계 노드가 삭제할 노드의 바로 오른쪽 자식인 경우
				succp->setRight(succ->getRight());
				//후계 노드 정보를 삭제할 노드에 복사
			}
			node->setData(succ->getData());
			//삭제할 노드를 후계 노드로 변경: 실제로는 후계 노드가 제거됨
			//word만 반환해도 괜찮을까? -> 일단 나중에 살펴보자...ㅠㅠ
			node = succ;
		}
		delete node; //메모리 동적 해제
	}
};

class Dictionary : public BinSrchTree {
public:
	//전위 순회하면서, 각 노드의 단어와 의미 출력
	void printAllWords() {
		//printf("     >> 나의 단어장:\n");
		if (!isEmpty()) { inorder(root); }
	}
	//단어에 의한 검색 연산
	BinaryNode* searchWord(char* word) {
		BinaryNode* node = search(word);
		if (node != NULL) {
			return node;
			//printf("     >> ");
			//node->display();
		}
		else {
			//printf("     >> 등록되지 않은 의미: %s\n", word); 
			return NULL;
		}
		return NULL;
	}
};

void help() {
	//printf("[사용법] i-추가, k-한국어 단어 검색, e-영어 단어 검색, p-출력, q-종료 =>");
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	char* result_korean[MAX_WORD_SIZE];
	char* result_english[MAX_WORD_SIZE];
	int korean_count = 0; //한국어 트리 배열 카운트
	int english_count = 0; //영어 트리 배열 카운트

	char list[MAX_WORD_SIZE]; //명령 리스트 확인
	int count = 0; //카운트 변수

	char command;

	char word[80]; //한영사전 한국어 단어
	char meaning[200]; //한영사전 영어 단어
	Dictionary tree; //한영사전

	char word2[80]; //영한사전 영어 단어
	char meaning2[200]; //영한사전 한국어 단어
	Dictionary tree2; //영한사전

	BinaryNode* tmp = NULL; //값을 나르는 임시 변수(한영사전)
	BinaryNode* tmp2 = NULL; //값을 나르는 임시 변수(영한사전)
	BinaryNode* korean_copy[MAX_WORD_SIZE];
	BinaryNode* english_copy[MAX_WORD_SIZE];

	do {
		help();
		cin >> command;
		while (getchar() != '\n');
		//command = _getche(); //키보드를 치는 것을 감지하여 엔터키 없이 바로 한 키보드 문자 입력, _getche()로 해야 빌드 오류 X
		//printf("\n");
		switch (command) {
		case 'i':
			//printf("   > 한국어 단어: "); 
			cin.getline(word, 80, '\n');//구형 gets 사용이 VS 2022에서 아예 인식 X
			strcpy(meaning2, word);
			//printf("   > 영어 단어: "); 
			cin.getline(meaning, 200, '\n');
			strcpy(word2, meaning);
			tree.insert(new BinaryNode(word, meaning));
			tree2.insert(new BinaryNode(word2, meaning2));
			break;

		case 'k':
			//printf("   > 검색 단어: "); 
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
			//printf("   > 검색 단어: "); 
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
