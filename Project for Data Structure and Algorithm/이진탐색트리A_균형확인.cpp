#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <algorithm>
#include <climits> //INT_MAX, INT_MIN�� ����ϱ� ���� ���
using namespace std;
#define MAX_QUEUE_SIZE 100

inline void error(const char* str) {
	fprintf(stderr, "%s\n", str);
	exit(1);
}

class BinaryNode {
protected:
	int data; //Ʈ���� ������ ������
	BinaryNode* left; //���� �ڽ� ����� ������
	BinaryNode* right; //������ �ڽ� ����� ������

public:
	BinaryNode(int val = 0, BinaryNode* l = NULL, BinaryNode* r = NULL)
		: data(val), left(l), right(r) { }

	//Ű ������ ��带 Ž���ϴ� �Լ�(��� Ŭ�������� ��ȯ���� ����)
	BinaryNode* search(int key) {
		if (key == data)
			return this;

		else if (key < data && left != NULL)
			return left->search(key);

		else if (key > data && right != NULL)
			return right->search(key);

		else
			return NULL;
	}

	void setData(int val) { data = val; }
	void setLeft(BinaryNode* l) { left = l; }
	void setRight(BinaryNode* r) { right = r; }

	int getData() { return data; } //��尪 ��ȯ
	BinaryNode* getLeft() { return left; } //���� ��尪 ��ȯ
	BinaryNode* getRight() { return right; } //������ ��尪 ��ȯ

	bool isLeaf() { return left == NULL && right == NULL; } //�� ��� ���� Ȯ��
};

class CircularQueue {
	int front;
	int rear;
	BinaryNode* data[MAX_QUEUE_SIZE];

public:
	CircularQueue() { front = rear = 0; }
	bool isEmpty() { return front == rear; }
	bool isFull() { return ((rear + 1) % MAX_QUEUE_SIZE) == front; }
	void enqueue(BinaryNode* n) {
		if (isFull()) { error("  Error: ť�� ��ȭ�����Դϴ�.\n"); }
		else {
			rear = (rear + 1) % MAX_QUEUE_SIZE;
			data[rear] = n;
		}
	}
	BinaryNode* dequeue() {
		if (isEmpty()) { error("  Error: ť�� ��������Դϴ�.\n"); }
		else {
			front = (front + 1) % MAX_QUEUE_SIZE;
			return data[front];
		}
	}
};

class BinaryTree {

public:

	BinaryNode* root; //��Ʈ ������

	//=====================================================================================
	// �ڷᱸ�� ������ ���� �Լ� �� bool isBalanced() �߰�
	//=====================================================================================
	//������ �����ִ����� �˻��ϴ� �Լ� - ���� ����Ʈ���� ������ ����Ʈ���� ������ ���̰� 2���� �������� �˻�
	//O(n)�� �ð� ���⵵�� ���� - ��͸� ���ְ�, ������ �̿��Ͽ� �ݺ������� ����
	bool isBalanced() {
		if (root == NULL)
			return true; // ���� Ʈ���� ���� �����ִٰ� ����

		stack<BinaryNode*> nodes; //��带 ���� ����
		stack<int> heights; //���̸� ���� ����
		nodes.push(root);
		heights.push(1); //������ �ʱⰪ�� 1
		int minimum_height = INT_MAX; //������ ū ��(����)
		int maximum_height = INT_MIN; //������ ���� ��(����)

		while (!nodes.empty()) {
			//���ÿ��� ���Ҹ� �̾� ��
			BinaryNode* current_state = nodes.top();
			int height = heights.top();
			nodes.pop();
			heights.pop();

			if (current_state->isLeaf()) {
				// �� ����� ��� �ּ� ���̿� �ִ� ���� ����
				minimum_height = min(minimum_height, height);
				maximum_height = max(maximum_height, height);
				//�� ������ ���� ������ ���̿� ���� ��ϵ� �ּ�/�ִ� ���� �� �ּ�/�ִ��� ���� ���� ����!
			}
			else {
				// ���� �ڽ� ��尡 �ִ� ��� ���ÿ� �߰�
				if (current_state->getLeft() != NULL) {
					nodes.push(current_state->getLeft());
					heights.push(height + 1); //���� ������ 1 �߰�
				}

				// ������ �ڽ� ��尡 �ִ� ��� ���ÿ� �߰�
				if (current_state->getRight() != NULL) {
					nodes.push(current_state->getRight());
					heights.push(height + 1); //���� ������ 1 �߰�
				}
			}
		}
		return (maximum_height - minimum_height) <= 1;
	}

	//=====================================================================================
	// �ڷᱸ�� ������ ���� �Լ� ��
	//=====================================================================================

	BinaryTree() : root(NULL) { }
	void setRoot(BinaryNode* node) { root = node; }
	BinaryNode* getRoot() { return root; } //��Ʈ ��尪 ��ȯ

	bool isEmpty() { return root == NULL; } //�� Ʈ�� ���� Ȯ��

	//����Ʈ���� ��ȸ ����
	void inorder() { printf("\n   inorder: "); inorder(root); }
	void inorder(BinaryNode* node) {
		//���� ��ȸ: LVR
		if (node != NULL) { //��Ʈ ��尡 0�� �ƴ� ��
			inorder(node->getLeft()); //���� ����Ʈ��
			printf(" [%d] ", node->getData()); //��Ʈ ��� ó��
			inorder(node->getRight()); //������ ����Ʈ��
		}
	}

	void preorder() { printf("\n  preorder: "); preorder(root); }
	void preorder(BinaryNode* node) {
		//���� ��ȸ: VLR
		if (node != NULL) { //��Ʈ ��尡 0�� �ƴ� ��
			printf(" [%d] ", node->getData()); //��Ʈ ��� ó��
			preorder(node->getLeft()); //���� ����Ʈ��
			preorder(node->getRight()); //������ ����Ʈ��
		}
	}

	void postorder() { printf("\n postorder: "); postorder(root); }
	void postorder(BinaryNode* node) {
		//���� ��ȸ: LRV
		if (node != NULL) { //��Ʈ ��尡 0�� �ƴ� ��
			postorder(node->getLeft()); //���� ����Ʈ��
			postorder(node->getRight()); //������ ����Ʈ��
			printf(" [%d] ", node->getData()); //��Ʈ ��� ó��
		}
	}

	//���� ��ȸ(BFS: ���� �켱 Ž��)
	void levelorder() {
		printf("\nlevelorder: ");
		if (!isEmpty()) {
			CircularQueue q;
			q.enqueue(root);
			//���� ��Ʈ�� ť�� �ִ´�.

			while (!q.isEmpty()) {
				BinaryNode* n = q.dequeue();
				//ť�� ������� ������ ť���� ����

				if (n != NULL) {
					//n�� NULL�� �ƴ� ��
					printf(" [%d] ", n->getData()); //n�� ǥ���ϰ�
					q.enqueue(n->getLeft());//���� ��带 ť�� �ִ´�.
					q.enqueue(n->getRight());//������ ��带 ť�� �ִ´�.
				}
				//���� ���°� �� ������ while�� �ݺ�
			}
		}
		printf("\n");
	}

	//����Ʈ���� �߰� ����
	//Ʈ���� ��� ������ ���ϴ� �Լ�
	int getCount() { return isEmpty() ? 0 : getCount(root); }
	//��ȯ ȣ�⿡ ���� node�� ��Ʈ�� �ϴ� ����Ʈ���� ��� �� ��� �Լ�
	int getCount(BinaryNode* node) {
		if (node == NULL) { return 0; }
		return (1 + getCount(node->getLeft()) + getCount(node->getRight()));
	}

	//Ʈ���� ���̸� ���ϴ� �Լ�
	int getHeight() { return isEmpty() ? 0 : getHeight(root); }
	int getHeight(BinaryNode* node) {
		if (node == NULL) { return 0; }
		int hLeft = getHeight(node->getLeft());
		int hRight = getHeight(node->getRight());
		return ((hLeft > hRight) ? hLeft + 1 : hRight + 1);
		//��: �� �ٸ� ���� �޸�, hLeft, hRight�� ���� ���ϱ�?
		//��: ���ǻ� �ϴ� ��, ���� ��� return�� �� �����ϸ� ��� ����
	}

	//Ʈ���� �� ���(�ܸ����) ������ ���ϴ� �Լ�
	int getLeafCount() { return isEmpty() ? 0 : getLeafCount(root); }
	//��ȯ ȣ�⿡ ���� node�� ��Ʈ�� �ϴ� ����Ʈ���� �ܸ� ��� �� ��� �Լ�
	int getLeafCount(BinaryNode* node) {
		if (node == NULL) { return 0; }
		if (node->isLeaf()) { return 1; } //�� ���!
		else return (getLeafCount(node->getLeft()) + getLeafCount(node->getRight()));
	}
};

class BinSrchTree : public BinaryTree {
public:
	BinSrchTree(void) { }
	~BinSrchTree(void) { }

	//���� Ž�� Ʈ���� Ž�� ����
	BinaryNode* search(int key) {
		BinaryNode* node = searchRecur(root, key);
		if (node != NULL) {
			printf("Ž�� ����: Ű���� %d�� ��� = 0x%x\n", node->getData(), node);
		}
		else {
			printf("Ű���� %d�� ��� ����\n", key);
		}
		return node;
	}
	//Ű ������ ��带 Ž���ϴ� �Լ�(��ȯ�� ���)
	//�Ϲ� �Լ��� ����(BinSrchTree�� ��� �Լ��� �־ ��)
	BinaryNode* searchRecur(BinaryNode* n, int key) {
		if (n == NULL) { return NULL; } //�� ã�Ҵ�.
		if (key == n->getData()) { return n; }
		else if (key < n->getData()) { return searchRecur(n->getLeft(), key); }
		else return searchRecur(n->getRight(), key);
	}

	//Ű ������ ��带 Ž���ϴ� �Լ�(�ݺ����� ���)
	//�Ϲ� �Լ��� ����(BinSrchTree�� ��� �Լ��� �־ ��)
	BinaryNode* SearchIter(BinaryNode* n, int key) {
		while (n != NULL) {
			if (key == n->getData()) { return n; }
			else if (key < n->getData()) { n = n->getLeft(); }
			else { n = n->getRight(); }
		}
		return n;
	}
	//=============================================================


	//���� Ž�� Ʈ���� ���� ����
	void insert(BinaryNode* n) {
		if (n == NULL) { return; }
		if (isEmpty()) { root = n; }
		else { insertRucur(root, n); }

	}
	//���� Ž�� Ʈ���� ���� �Լ�
	void insertRucur(BinaryNode* r, BinaryNode* n) {
		//root�� key�� ������ return
		if (n->getData() == r->getData()) { return; }
		//root���� key�� ���� ��
		else if (n->getData() < r->getData()) {
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
	void remove(int key) {
		if (isEmpty()) { return; } //�� Ʈ���̸� return

		//���� ���� �� ����� �θ� ��带 ã�´�.
		BinaryNode* parent = NULL; //�θ� ���
		BinaryNode* node = root; //��Ʈ ���
		while (node != NULL && node->getData() != key) {
			parent = node;
			node = (key < node->getData()) ? node->getLeft() : node->getRight();
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
			if (parent == NULL) { root = NULL; } //node == root�̸� ��Ʈ�� �ִ� ����
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
			BinaryNode* succ = node->getRight(); //���ʺ��� ����� getLeft()

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
			node = succ;
		}
		delete node; //�޸� ���� ����
	}
};
BinSrchTree tree; //��ü ����

void switchInput(string order, int key) {
	if (order == "I") { //���� ����
		tree.insert(new BinaryNode(key));
	}
	else if (order == "D") { //���� ����
		tree.remove(key);
	}
	else { return; }
}

int main() {

	int n; //�۾��� ��
	cin >> n;

	string order; //���(I, D)
	int key; //key��
	for (int j = 0; j < n; j++) {
		cin >> order >> key;
		switchInput(order, key);
	}

	if (tree.isBalanced() == true) { printf("Balanced"); }
	else { printf("Unbalanced");; }

	return 0;
}
