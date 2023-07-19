//�ؽ��� �̿��ϴ� ���: O(1) => �浹�� ��Ÿ���� ���� ������, �����δ� O(1)���� ������ ����
//�ؽ�(hashing): Ž��Ű�� ������� ������ �����Ͽ�, �׸��� ����Ǿ� �ִ� ��ġ(�ε���)�� ���� ����ϴ� ���
//�ؽ� ���̺�(hash table): Ű���� ���꿡 ���� ���� ������ ������ ����

//�ؽ� �Լ�(hash function): �� Ž��Ű�� ���� ������ ���(mapping)��Ű�� ��
//�ؽ� �Լ��� Ž��Ű�� �Է¹޾� �ؽ� �ּ�(hash address)�� ���
//�ϳ��� ����(bucket)���� ���� ���ڵ带 ������ �� �ִ� ���� ���� ����(slot)�� ����
//(������ ���� ���� ����? => Ž��Ű�� ������ �ؽ� �ּҷ� ��ȯ�� �� ����. �׷��� ������ ���ǻ� �ϴ� �� �ڵ忡���� ������ �ϳ���� ����)

//�浹(collision): ������ ���� �������� �� ������, k1�� k2�� �ؽ� �Լ��� ���� ���� �ּ�(h(k1)==h(k2))�� ���Ǵ� ��Ȳ
//���Ǿ�(synonym): �浹�� �߻��ϴ� �� Ž��Ű
//�����÷ο�(overflow): �浹 ���� ���� ������ �� ���� �߻��� �� => �� �̻� �׸� ���� �Ұ�

//���� �ؽ� �Լ��� ����
//1. �浹�� ����� �Ѵ�.
//2. �ؽ� �Լ� ���� �ؽ� ���̺��� �ּ� ���� ������ ���� �����Ǿ�� �Ѵ�.
// ��)��������� ù ���ڷθ� �ؽ� ���̺��� �����, �����ϰ� �������� �ʴ´�.
// =>���� �Լ�: h(k)=k mod(%) M : ������ ������ ���� M�� �Ҽ�(1�� �ڱ� �ڽŸ� ����� ������ ����) ���
//3. ����� ����� �Ѵ�.

//����(folding): Ž��Ű�� �� ���� �κ����� ������ �̸� ���ϰų� ��Ʈ���� �ο� ������ �ϴ� ��
//hash_index=(short)(key ^ (key>>16))
//�̵� ����(shift folding): Ž��Ű�� ���� �κ����� ���� ������ ���Ͽ� �ؽ� �ּҸ� ��� ���
//��� ����(boundary folding): �̿��� �κ��� �Ųٷ� ���� �ؽ� �ּҸ� ��� ���
//��)
//Ž��Ű: 12320324111220
//�̵� ����: 123+203+241+112+20=699
//��� ����: 123+302+241+211+20=897

//���ڿ� Ž��Ű�� ���� ��ȯ �� �ؽ� �Լ�
//a���� z������ 1~26���� �Ҵ��ϰų�, ������ ASCII �ڵ带 �״�� ��� ����


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define KEY_SIZE 64
#define VALUE_SIZE 64
#define TABLE_SIZE 13 //�ؽ� ���̺� ũ���� ��: �Ҽ� 13 ���

//���ڿ��� �� Ž��Ű�� ���ڷ� ��ȯ: ������ ���� ���
inline int transform(const char* key) { //string�� �ƴ϶� char���̹Ƿ�, ���� �ϳ��� �о��
	int number = 0;
	while (*key) { number += (*key++); }
	return number;
}

//�ؽ� �Լ�: ���� �Լ� ���
inline int hashFunction(const char* key) {
	return transform(key) % TABLE_SIZE;
}

//���� �����(linear probing): �ؽ� �Լ��� ���� ���Ͽ� �� ������ ������ �� ���� ���Ͽ��� �� ������ �ִ����� ã�� ���
//����(probing): ��� �ִ� ������ ã�� ����

//�ؽ� ���� ���� Keyed Record Ŭ����
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

//�ؽ� �� Ŭ����
class HashMap {
	Record table[TABLE_SIZE];

public:
	HashMap() { reset(); }
	void reset() { //��� ������ ���
		for (int i = 0; i < TABLE_SIZE; i++) {
			table[i].reset(); //recursion �ƴմϴ�! Record Ŭ���� ���� �Լ��Դϴ�.
		}
	}
	//���� ��ü ������ ���
	void display() {
		for (int i = 0; i < TABLE_SIZE; i++) {
			printf("[%2d]", i);
			table[i].display(); //recursion �ƴմϴ�! Record Ŭ���� ���� �Լ��Դϴ�.
		}
	}

	//���� ������� �̿��� �Է�
	void addLinearProb(const char* key, const char* value) {
		int i, hashValue;
		hashValue = i = hashFunction(key);
		while (table[i].isEmpty() == false) {
			if (table[i].equal(key)) {
				printf("[%s] Ž��Ű�� �ߺ��Ǿ����ϴ�.\n", key);
				return;
			}
			i = (i + 1) % TABLE_SIZE;
			if (i == hashValue) {
				printf("[%s] ���̺��� ����á���ϴ�.\n", key);
				return;
			}
		}
		table[i].set(key, value);
	}

	//���� ������� �̿��� Ž��
	Record* searchLinearProb(const char* key) {
		int i, hashValue;
		hashValue = i = hashFunction(key);
		while (table[i].isEmpty() == false) {
			if (table[i].equal(key)) {
				printf("[%s] Ž������ [%d]", key, i);
				table[i].display();
				return (table + i);
			}
			i = (i + 1) % TABLE_SIZE;
			if (i == hashValue) break;
		}
		printf("[%s] Ž�� ����: ã�� ���� ���̺� ����\n", key);
		return NULL;
	}
};

int main() {
	HashMap hash;
	hash.addLinearProb("do", "�ݺ�");
	hash.addLinearProb("for", "�ݺ�");
	hash.addLinearProb("if", "�б�");
	hash.addLinearProb("case", "�б�");
	hash.addLinearProb("else", "�б�");
	hash.addLinearProb("return", "��ȯ");
	hash.addLinearProb("function", "�Լ�");
	hash.display();
	hash.searchLinearProb("return"); //Ž�� ����
	hash.searchLinearProb("class"); //Ž�� ����
	hash.searchLinearProb("function"); //Ž�� ����
	return 0;
}