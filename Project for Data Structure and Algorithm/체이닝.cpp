//���� �ؽ̹�(double hashing, rehashing)?
//�����÷ο찡 �߻��Ͽ� �׸��� ������ ���� ��ġ ���� ��, ���� �ؽ� �Լ��� �ٸ� ������ �ؽ� �Լ��� �̿��ϴ� ���

//���� ���� ����
//step = C-(kmodC) = i+kmodC => [1~C] ������ �� ����
// C: M���� �ణ ���� �Ҽ�
//�浹 �߻� �� ����Ǵ� ��ġ: h(k), h(k)+step, h(k)+2*step, h(k)+3*step, ..., modM

//ü�̴�(chaining): �ϳ��� ���Ͽ� ���� ���� ���ڵ带 �����ϵ���, ���� ����Ʈ�� �ؽ� ���̺��� �����ϴ� ���

//�ؽ��� ���� alpha = ����� �׸��� ���� / �ؽ� ���̺��� ������ ���� = n/M
//���� �����: ������ ��� alpha = 1
//ü�̴�: n>M�� �� �����Ƿ�, alpha�� �ִ��� ������ ����


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

//�ؽ� ���� ���� Keyed Record Ŭ����
class Record {
	char key[KEY_SIZE];
	char value[VALUE_SIZE];

public:
	Record(const char* k = "", const char* v = "") { set(k, v); }
	const char* getKey() { return key; } //���翡�� ���� �κ�
	void set(const char* k, const char* v) { strcpy(key, k); strcpy(value, v); }
	void reset() { set("", ""); }
	bool isEmpty() { return key[0] == '\0'; }
	bool equal(const char* k) { return strcmp(k, key) == 0; }
	void display() { printf("%20s = %s\n", key, value); }
};

class Node : public Record {
	Node* link; //���� ��ũ�� ����Ű�� ������ ����
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

	//ü�ι��� �̿��Ͽ� ���̺� Ű�� �Է�
	void addRecord(Node* n) {
		int hashValue = hashFunction(n->getKey());
		for (Node* p = table[hashValue]; p != NULL; p = p->getlink()) {
			if (p->equal(n->getKey())) {
				printf("�̹� Ž��Ű�� ����Ǿ� �ֽ��ϴ�.\n");
				delete n;
				return;
			}
		}
		n->setLink(table[hashValue]);
		table[hashValue] = n;
	}

	//ü�ι��� �̿��Ͽ� ���̺� ����� Ű�� Ž��
	void searchRecord(const char* key) {
		int hashValue = hashFunction(key);
		Node* p = table[hashValue];
		while (p != NULL) {
			if (p->equal(key)) {
				printf("Ž�� ����: ");
				p->display();
				return;
			}
			p = p->getlink();
		}
		printf("Ž�� ����: %s\n", key);
	}
};

int main() {
	HashChainMap hash;
	hash.addRecord(new Node("do", "�ݺ�"));
	hash.addRecord(new Node("for", "�ݺ�"));
	hash.addRecord(new Node("if", "�б�"));
	hash.addRecord(new Node("case", "�б�"));
	hash.addRecord(new Node("else", "�б�"));
	hash.addRecord(new Node("return", "��ȯ"));
	hash.addRecord(new Node("function", "�Լ�"));
	hash.display();
	hash.searchRecord("return"); //Ž�� ����
	hash.searchRecord("class"); //Ž�� ����
	hash.searchRecord("function"); //Ž�� ����
	return 0;
}