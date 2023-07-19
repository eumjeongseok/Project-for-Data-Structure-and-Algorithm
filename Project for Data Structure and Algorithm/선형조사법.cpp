//해싱을 이용하는 방법: O(1) => 충돌이 나타나지 않을 때에만, 실제로는 O(1)보다 느리게 연산
//해싱(hashing): 탐색키에 산술적인 연산을 적용하여, 항목이 저장되어 있는 위치(인덱스)를 직접 계산하는 방식
//해시 테이블(hash table): 키값의 연산에 의해 직접 접근이 가능한 구조

//해시 함수(hash function): 각 탐색키를 작은 정수로 사상(mapping)시키는 것
//해시 함수는 탐색키를 입력받아 해시 주소(hash address)를 계산
//하나의 버켓(bucket)에는 각각 레코드를 저장할 수 있는 여러 개의 슬롯(slot)을 가짐
//(슬롯이 여러 개인 이유? => 탐색키가 동일한 해시 주소로 변환될 수 있음. 그러나 구현의 편의상 일단 이 코드에서는 슬롯이 하나라고 가정)

//충돌(collision): 버켓의 수가 제한적인 점 때문에, k1과 k2가 해시 함수에 의해 같은 주소(h(k1)==h(k2))로 계산되는 상황
//동의어(synonym): 충돌이 발생하는 두 탐색키
//오버플로우(overflow): 충돌 수가 슬롯 수보다 더 많이 발생할 때 => 더 이상 항목 저장 불가

//좋은 해시 함수의 조건
//1. 충돌이 적어야 한다.
//2. 해시 함수 값이 해시 테이블의 주소 영역 내에서 고르게 분포되어야 한다.
// 예)영어사전을 첫 문자로만 해시 테이블을 만들면, 균일하게 분포되지 않는다.
// =>제산 함수: h(k)=k mod(%) M : 균일한 분포를 위해 M은 소수(1과 자기 자신만 약수로 가지는 숫자) 사용
//3. 계산이 빨라야 한다.

//폴딩(folding): 탐색키를 몇 개의 부분으로 나누어 이를 더하거나 비트별로 부울 연산을 하는 것
//hash_index=(short)(key ^ (key>>16))
//이동 폴딩(shift folding): 탐색키를 여러 부분으로 나눈 값들을 더하여 해시 주소를 얻는 방식
//경계 폴딩(boundary folding): 이웃한 부분을 거꾸로 더해 해시 주소를 얻는 방식
//예)
//탐색키: 12320324111220
//이동 폴딩: 123+203+241+112+20=699
//경계 폴딩: 123+302+241+211+20=897

//문자열 탐색키의 정수 변환 및 해시 함수
//a부터 z까지를 1~26으로 할당하거나, 문자의 ASCII 코드를 그대로 사용 가능


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

//선형 조사법(linear probing): 해싱 함수로 구한 버켓에 빈 슬롯이 없으면 그 다음 버켓에서 빈 슬롯이 있는지를 찾는 방법
//조사(probing): 비어 있는 공간을 찾는 과정

//해시 맵을 위한 Keyed Record 클래스
class Record {
	char key[KEY_SIZE];
	char value[VALUE_SIZE];

public:
	Record(const char* k = "", const char* v = "") { set(k, v); }
	void set(const char* k, const char* v) { strcpy(key, k); strcpy(value, v); }
	void reset() { set("", ""); }
	bool isEmpty() { return key[0] == '\0'; }
	bool equal(const char* k) { return strcmp(k, key) == 0; }
	void display() { printf("%20s = %s\n", key, value); }
};

//해시 맵 클래스
class HashMap {
	Record table[TABLE_SIZE];

public:
	HashMap() { reset(); }
	void reset() { //모든 버켓을 비움
		for (int i = 0; i < TABLE_SIZE; i++) {
			table[i].reset(); //recursion 아닙니다! Record 클래스 내의 함수입니다.
		}
	}
	//맵의 전체 내용을 출력
	void display() {
		for (int i = 0; i < TABLE_SIZE; i++) {
			printf("[%2d]", i);
			table[i].display(); //recursion 아닙니다! Record 클래스 내의 함수입니다.
		}
	}

	//선형 조사법을 이용한 입력
	void addLinearProb(const char* key, const char* value) {
		int i, hashValue;
		hashValue = i = hashFunction(key);
		while (table[i].isEmpty() == false) {
			if (table[i].equal(key)) {
				printf("[%s] 탐색키가 중복되었습니다.\n", key);
				return;
			}
			i = (i + 1) % TABLE_SIZE;
			if (i == hashValue) {
				printf("[%s] 테이블이 가득찼습니다.\n", key);
				return;
			}
		}
		table[i].set(key, value);
	}

	//선형 조사법을 이용한 탐색
	Record* searchLinearProb(const char* key) {
		int i, hashValue;
		hashValue = i = hashFunction(key);
		while (table[i].isEmpty() == false) {
			if (table[i].equal(key)) {
				printf("[%s] 탐색성공 [%d]", key, i);
				table[i].display();
				return (table + i);
			}
			i = (i + 1) % TABLE_SIZE;
			if (i == hashValue) break;
		}
		printf("[%s] 탐색 실패: 찾는 값이 테이블에 없음\n", key);
		return NULL;
	}
};

int main() {
	HashMap hash;
	hash.addLinearProb("do", "반복");
	hash.addLinearProb("for", "반복");
	hash.addLinearProb("if", "분기");
	hash.addLinearProb("case", "분기");
	hash.addLinearProb("else", "분기");
	hash.addLinearProb("return", "반환");
	hash.addLinearProb("function", "함수");
	hash.display();
	hash.searchLinearProb("return"); //탐색 성공
	hash.searchLinearProb("class"); //탐색 실패
	hash.searchLinearProb("function"); //탐색 성공
	return 0;
}