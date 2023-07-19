//이중 해싱법(double hashing, rehashing)?
//오버플로우가 발생하여 항목을 저장할 다음 위치 결정 시, 원래 해시 함수와 다른 별개의 해시 함수를 이용하는 방법

//조사 간격 결정
//step = C-(kmodC) = i+kmodC => [1~C] 사이의 값 생성
// C: M보다 약간 작은 소수
//충돌 발생 시 조사되는 위치: h(k), h(k)+step, h(k)+2*step, h(k)+3*step, ..., modM

//체이닝(chaining): 하나의 버켓에 여러 개의 레코드를 저장하도록, 연결 리스트로 해시 테이블을 구현하는 방식

//해싱의 성능 alpha = 저장된 항목의 개수 / 해싱 테이블의 버켓의 개수 = n/M
//선형 조사법: 가득찬 경우 alpha = 1
//체이닝: n>M일 수 있으므로, alpha는 최댓값을 가지지 않음


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define KEY_SIZE 64
#define VALUE_SIZE 64
#define TABLE_SIZE 13 //해싱 테이블 크기의 예: 소수 13 사용

//문자열로 된 탐색키를 숫자로 변환: 간단한 덧셈 방식
inline int transform(const char* key) { //string이 아니라 char형이므로, 글자 하나씩 읽어나감
	int number = 0;
	while (*key) { number += (*key++); }
	return number;
}

//해싱 함수: 제산 함수 사용
inline int hashFunction(const char* key) {
	return transform(key) % TABLE_SIZE;
}

//해시 맵을 위한 Keyed Record 클래스
class Record {
	char key[KEY_SIZE];
	char value[VALUE_SIZE];

public:
	Record(const char* k = "", const char* v = "") { set(k, v); }
	const char* getKey() { return key; } //교재에서 빠진 부분
	void set(const char* k, const char* v) { strcpy(key, k); strcpy(value, v); }
	void reset() { set("", ""); }
	bool isEmpty() { return key[0] == '\0'; }
	bool equal(const char* k) { return strcmp(k, key) == 0; }
	void display() { printf("%20s = %s\n", key, value); }
};

class Node : public Record {
	Node* link; //다음 링크를 가리키는 포인터 변수
public:
	Node(const char* key, const char* val) : Record(key, val), link(NULL) { };
	Node* getlink() { return link; }
	void setLink(Node* next) { link = next; }
};

class HashChainMap {
	Node* table[TABLE_SIZE];
public:
	HashChainMap() { for (int i = 0; i < TABLE_SIZE; i++) { table[i] = NULL; } }

	void display() {
		for (int i = 0; i < TABLE_SIZE; i++) {
			printf("[%2d]", i);
			if (table[i] != NULL) {
				Node* p = table[i];
				while (p != NULL) {
					printf("%10s", p->getKey());
					p = p->getlink();
				}
			}
			printf("\n");
		}
	}

	//체인법을 이용하여 테이블에 키를 입력
	void addRecord(Node* n) {
		int hashValue = hashFunction(n->getKey());
		for (Node* p = table[hashValue]; p != NULL; p = p->getlink()) {
			if (p->equal(n->getKey())) {
				printf("이미 탐색키가 저장되어 있습니다.\n");
				delete n;
				return;
			}
		}
		n->setLink(table[hashValue]);
		table[hashValue] = n;
	}

	//체인법을 이용하여 테이블에 저장된 키를 탐색
	void searchRecord(const char* key) {
		int hashValue = hashFunction(key);
		Node* p = table[hashValue];
		while (p != NULL) {
			if (p->equal(key)) {
				printf("탐색 성공: ");
				p->display();
				return;
			}
			p = p->getlink();
		}
		printf("탐색 실패: %s\n", key);
	}
};

int main() {
	HashChainMap hash;
	hash.addRecord(new Node("do", "반복"));
	hash.addRecord(new Node("for", "반복"));
	hash.addRecord(new Node("if", "분기"));
	hash.addRecord(new Node("case", "분기"));
	hash.addRecord(new Node("else", "분기"));
	hash.addRecord(new Node("return", "반환"));
	hash.addRecord(new Node("function", "함수"));
	hash.display();
	hash.searchRecord("return"); //탐색 성공
	hash.searchRecord("class"); //탐색 실패
	hash.searchRecord("function"); //탐색 성공
	return 0;
}