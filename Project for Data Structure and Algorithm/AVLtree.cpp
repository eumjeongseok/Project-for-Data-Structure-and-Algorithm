//AVL Ʈ��?
//���� ����Ʈ���� ���̿� ������ ����Ʈ���� ���� ���̰� 1 ������ ���� Ž�� Ʈ��
//Ž�� �ð�: O(logn)
//AVL Ʈ������ ������ ������ ���: ���� ����, ���� ����

//������ ������ Ÿ��
//LL Ÿ��: N�� A�� ���� ����Ʈ���� ���� ����Ʈ���� �Է�
//LR Ÿ��: N�� A�� ���� ����Ʈ���� ������ ����Ʈ���� �Է�
//RR Ÿ��: N�� A�� ������ ����Ʈ���� ������ ����Ʈ���� �Է�
//RL Ÿ��: N�� A�� ������ ����Ʈ���� ���� ����Ʈ���� �Է�

//������ ��� ���
// 1. �ܼ� ȸ��(single rotation): �� ���� ȸ��
//LL ȸ��: A���� N������ ��λ��� ������ ���������� ȸ��
//RR ȸ��: A���� N������ ��λ��� ������ �������� ȸ��

// 2. ���� ȸ��(double rotation): �� �� ȸ��
//LR ȸ��: A���� N������ ��λ��� ������ ����-���������� ȸ��
//RL ȸ��: A���� N������ ��λ��� ������ ������-�������� ȸ��


#include <cstdio>
#include <cstdlib>
#include <iostream>
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

	//(1)�� �Լ�
	bool isFull() {
		//����Ʈ���� ���� ����Ʈ������ �˻��ϴ� �Լ�

		if (!isEmpty()) {
			CircularQueue q;
			q.enqueue(root);

			while (!q.isEmpty()) {

				BinaryNode* n = q.dequeue();

				//���ܳ�尡 �ƴϰ� ���� ������ �ڽ� �� �ϳ��� ������ ��������Ʈ�� X

				if (!(n->isLeaf()) && n->getLeft() == NULL && n->getRight() != NULL)
					return false;

				else if (!(n->isLeaf()) && n->getLeft() != NULL && n->getRight() == NULL)
					return false;

				if (n != NULL) {
					if (n->getLeft())
						q.enqueue(n->getLeft());

					if (n->getRight())
						q.enqueue(n->getRight());
				}
			}
			return true;
		}
	}


	//(2)�� �Լ�
	//������ ���ϴ� ����
	int level(BinaryNode* node) {
		return level(root, node);
	}
	int level(BinaryNode* node1, BinaryNode* node2, int lev = 1) {
		//node2�� �츮�� ã���� �ϴ� node
		if (node1 == NULL)
			return 0;

		if (node1 == node2)
			return lev;

		if (node1->getLeft() == NULL && node1->getRight() == NULL)
			return 0;

		//���
		int left = level(node1->getLeft(), node2, lev + 1); //��������
		int right = level(node1->getRight(), node2, lev + 1); //����������

		if (!left) //���� ��尡 �������� �ʴ´ٸ�
			return right; //������ ��� ��ȯ

		else //�ݴ�
			return left;
	}

	//(3)�� �Լ�
	bool isBalanced() {
		//������ �����ִ°�?
		return isBalanced(root);
	}
	bool isBalanced(BinaryNode* node) {
		int leftHeight;
		int rightHeight;

		if (node == NULL)
			return true;

		leftHeight = getHeight(node->getLeft());
		rightHeight = getHeight(node->getRight());

		//���� ����Ʈ���� �����ʼ���Ʈ���� �������� 2�̻� ���� �ʰ� �� �� ������ �������� ��� ��
		if ((leftHeight - rightHeight) <= 1 && (leftHeight - rightHeight) >= -1 && isBalanced(node->getLeft()) && isBalanced(node->getRight()))
			return true;

		return false;
	}

	//����� ����
	int pathLength() {
		int sum = 0;

		if (!isEmpty()) {
			CircularQueue q;
			q.enqueue(root);

			while (!q.isEmpty()) {
				BinaryNode* n = q.dequeue();

				sum += level(n) - 1; //�� ����� ����-1��ŭ ���ϸ� �� ���

				if (n != NULL) {
					if (n->getLeft())
						q.enqueue(n->getLeft());

					if (n->getRight())
						q.enqueue(n->getRight());
				}
			}
		}
		return sum;
	}


	//(4)�� �Լ�
	 //�ڹٲ۴�
	bool reverse() {
		return reverse(root);
	}
	bool reverse(BinaryNode* node) {
		if (node == NULL)
			return false;
		else {
			//���
			reverse(node->getLeft());
			reverse(node->getRight());
			//leftNode�� rightNode�� ���� �ٲ۴�
			BinaryNode* temp = node->getLeft();
			node->setLeft(node->getRight());
			node->setRight(temp);
		}
		return true;
	}




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

	int evaluate() { return evaluate(root); }
	//��ȯ ȣ�⿡ ���� node�� ��Ʈ�� �ϴ� ���� Ʈ���� ��� �Լ�
	int evaluate(BinaryNode* node) {
		if (node == NULL) { return 0; }
		if (node->isLeaf()) { return node->getData(); }
		else {
			int op1 = evaluate(node->getLeft()); //���� ��� ��
			int op2 = evaluate(node->getRight()); //������ ��� ��
			switch (node->getData()) { //�θ� ���� ������
			case '+': return (op1 + op2);
			case '-': return (op1 - op2);
			case '*': return (op1 * op2);
			case '/': return (op1 / op2);
			}
			return 0;
		}
	}

	//���͸� �뷮 ��� �Լ�
	int calcSize() { return calcSize(root); }
	int calcSize(BinaryNode* node) {
		if (node == NULL) { return 0; }
		return (node->getData() + calcSize(node->getLeft()) + calcSize(node->getRight()));
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
			node = succ;
		}
		delete node; //�޸� ���� ����
	}
};

//AVL Ʈ�� Ŭ����
class AVLTree : public BinSrchTree {
public:
	//����� ���� �μ� ��ȯ
	int getHeightDiff(BinaryNode* node) {
		if (node == NULL) { return 0; }
		int hLeft = getHeight(node->getLeft());
		int hRight = getHeight(node->getRight());
		return hLeft - hRight;
	}

	//LL ȸ�� �Լ�
	BinaryNode* rotateLL(BinaryNode* parent) {
		BinaryNode* child = parent->getLeft();
		parent->setLeft(child->getRight()); //child�� ������ �ڽ��� parent�� ���� �ڽ����� �����.
		child->setRight(parent); //parent�� child�� ������ �ڽ� ���� �����.
		printf("LL ");
		return child;
	}

	//RR ȸ�� �Լ�
	BinaryNode* rotateRR(BinaryNode* parent) {
		BinaryNode* child = parent->getRight();
		parent->setRight(child->getLeft());
		child->setLeft(parent);
		printf("RR ");
		return child;
	}

	//RL ȸ�� �Լ�
	BinaryNode* rotateRL(BinaryNode* parent) {
		BinaryNode* child = parent->getRight();
		printf("RL ");
		parent->setRight(rotateLL(child));
		return rotateRR(parent);
	}

	//LL ȸ�� �Լ�
	BinaryNode* rotateLR(BinaryNode* parent) {
		BinaryNode* child = parent->getLeft();
		printf("LR ");
		parent->setLeft(rotateRR(child));
		return rotateLL(parent);
	}

	//Ʈ���� ����Ʈ���� ����� �۾�
	BinaryNode* reBalance(BinaryNode* parent) {
		int hDiff = getHeightDiff(parent);
		if (hDiff > 1) {
			//���� ���� ����Ʈ���� ���� ����Ʈ���� ���̰� ũ�� LL, �׷��� ������ LR
			if (getHeightDiff(parent->getLeft()) > 0) { parent = rotateLL(parent); } //LL Ÿ�� �ұ���
			else { parent = rotateLR(parent); } //LR Ÿ�� �ұ���
		}
		else if (hDiff < -1) {
			//���� ������ ����Ʈ���� ������ ����Ʈ���� ���̰� ������ RR, �׷��� ������ RL
			if (getHeightDiff(parent->getRight()) < 0) { parent = rotateRR(parent); }
			else { parent = rotateRL(parent); }
		}
		return parent;
	}

	//AVL Ʈ�� ���� ����
	void insert(int data) {
		if (isEmpty()) { root = new BinaryNode(data); }
		else root = insertAVL(root, data);
	}
	BinaryNode* insertAVL(BinaryNode* parent, int data) { //�Լ� �����ε�
		if (data < parent->getData()) { //parent�� ���� �ڽ����� ���� �ϴ� ���
			if (parent->getLeft() != NULL) { //���� �ڽ��� ���� ��� �ٷ� ���� �ڽ����� ����
				parent->setLeft(insertAVL(parent->getLeft(), data));
			}
			else { //�׷��� ���� ��� ���� �ڽ� ��忡�� �Է� ������ �ѱ�
				parent->setLeft(new BinaryNode(data));
			}
			return reBalance(parent); //������ ���� ���� ��� ��ȯ
		}
		else if (data > parent->getData()) { //parent�� ������ �ڽ����� ���� �ϴ� ���
			if (parent->getRight() != NULL) { //������ �ڽ��� ���� ��� �ٷ� ������ �ڽ����� ���� 
				parent->setRight(insertAVL(parent->getRight(), data));
			}
			else { //�׷��� ���� ��� ������ �ڽ� ��忡�� �Է� ������ �ѱ�
				parent->setRight(new BinaryNode(data));
			}
			return reBalance(parent);
		}
		else {
			//parent�� ���� ���� ���� ���� ������ ���� ��� �� �ٷ� ��ȯ
			printf("�ߺ��� Ű ����\n");
			return NULL;
		}
	}
};

int main() {
	AVLTree tree;
	//7, 8, 9, 2, 1, 5, 3, 6, 4 ����
	tree.insert(7); tree.levelorder();
	tree.insert(8); tree.levelorder();
	tree.insert(9); tree.levelorder();
	tree.insert(2); tree.levelorder();
	tree.insert(1); tree.levelorder();
	tree.insert(5); tree.levelorder();
	tree.insert(3); tree.levelorder();
	tree.insert(6); tree.levelorder();
	tree.insert(4); tree.levelorder();

	return 0;
}