#include <cstdio>
#include <cstdlib>

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

	void setData(int val) { data = val; }
	void setLeft(BinaryNode* l) { left = l; }
	void setRight(BinaryNode* r) { right = r; }

	int getData() { return data; } //��尪 ��ȯ
	BinaryNode* getLeft() { return left; } //���� ��尪 ��ȯ
	BinaryNode* getRight() { return right; } //������ ��尪 ��ȯ

	bool isLeaf() { return left == NULL && right == NULL; } //�� ��� ���� Ȯ��
	bool isnonLeaf() { return left != NULL || right != NULL; }
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
	BinaryNode* root; //��Ʈ ������

public:

	//=====================================================================================
	// �ڷᱸ�� ������ ���� �Լ� 3�� �߰�
	//=====================================================================================
	//(1)��: ����Ʈ���� ��ȭ����Ʈ������ �˻��ϴ� �Լ�
	bool isFull() {
		if (!isEmpty()) {
			CircularQueue q;
			q.enqueue(root); //��Ʈ�� ť�� �߰�

			while (!q.isEmpty()) {
				BinaryNode* n = q.dequeue();
				//���ܳ�尡 �ƴϰ� ���� Ʈ���� ���� �ڽĸ� ������ ��ȭ����Ʈ�� X
				if (!(n->isLeaf())
					&& n->getLeft() == NULL
					&& n->getRight() != NULL) {
					return false;
				}
				else if (!(n->isLeaf())
					&& n->getLeft() != NULL
					&& n->getRight() == NULL) {
					return false;
				}

				//�� ��尡 �ƴϸ� �ڽ� ��带 ���󰡰�, �ڽ� ��带 ť�� �߰�
				if (n != NULL) {
					if (n->getLeft())
						q.enqueue(n->getLeft());
					if (n->getRight())
						q.enqueue(n->getRight());
				}
			}
			return true;
			//�� ���� ������ false�� ������ ������ true�� ��ȯ
		}
	}

	//(2)��: ������ �����ִ����� �˻��ϴ� �Լ� - ���� ����Ʈ���� ������ ����Ʈ���� ������ ���̰� 2���� �������� �˻�
	bool isBalanced() { return isBalanced(root); }
	bool isBalanced(BinaryNode* node) {
		int leftHeight;
		int rightHeight;

		if (node == NULL) { return true; } //���� Ʈ���� ��
		if (node->isLeaf()) { return true; } //�� ����� ��

		leftHeight = getHeight(node->getLeft());
		rightHeight = getHeight(node->getRight());

		//���� ����Ʈ���� �����ʼ���Ʈ���� �������� 2�̻� ���� �ʰ�
		//�� �� ������ �������� ���
		//true ��ȯ
		if ((leftHeight - rightHeight) <= 1
			&& (leftHeight - rightHeight) >= -1
			&& isBalanced(node->getLeft())
			&& isBalanced(node->getRight())) {
			return true;
		}

		return false;
	}

	//(3)��: �¿� ����Ʈ���� ��ü�ϴ� �Լ�(�¿� ��Ī) - �Լ� �����ε�
	void reverse() { reverse(root); }
	void reverse(BinaryNode* node) {
		if (node == NULL) { return; }
		else {
			//���
			reverse(node->getLeft());
			reverse(node->getRight());
			//leftNode�� rightNode�� ���� �ٲ۴�
			BinaryNode* temp = node->getLeft();
			node->setLeft(node->getRight());
			node->setRight(temp);
		}
	}
	//=====================================================================================
	// �ڷᱸ�� ������ ���� �Լ� 3�� ��
	//=====================================================================================

	BinaryTree() : root(NULL) { }
	void setRoot(BinaryNode* node) { root = node; }
	BinaryNode* getRoot() { return root; } //��Ʈ ��尪 ��ȯ

	bool isEmpty() { return root == NULL; } //�� Ʈ�� ���� Ȯ��

	//����Ʈ���� ��ȸ ����
	void inorder() { printf("inorder: "); inorder(root); }
	void inorder(BinaryNode* node) {
		//���� ��ȸ: LVR
		if (node != NULL) { //��Ʈ ��尡 0�� �ƴ� ��
			inorder(node->getLeft()); //���� ����Ʈ��
			printf(" [%c] ", node->getData()); //��Ʈ ��� ó��
			inorder(node->getRight()); //������ ����Ʈ��
		}
	}

	void preorder() { printf("\n  preorder: "); preorder(root); }
	void preorder(BinaryNode* node) {
		//���� ��ȸ: VLR
		if (node != NULL) { //��Ʈ ��尡 0�� �ƴ� ��
			printf(" [%c] ", node->getData()); //��Ʈ ��� ó��
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
			printf(" [%c] ", node->getData()); //��Ʈ ��� ó��
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
					printf(" [%c] ", n->getData()); //n�� ǥ���ϰ�
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



int main() {
	BinaryTree tree;

	//�� �׽�Ʈ ���̽��� ���� �ʹٸ� �� �ּ� ����
	//�� �׽�Ʈ ���̽��� ���� ���� �ʴٸ� �� �ּ����� ���α�
	//��, �� ���� �ϳ��� ����(���� ���ڰ� �־� �����ǵǱ� ����)


	/*
	//===========================================================================================
	// �׽�Ʈ ���̽� 1
	// �˻��ϴ� �Լ�: �������� ��ȭ ����Ʈ�� (Ʈ���� ���̰� 3)
	//                  A
	//            B            C
	//          D   E        F   G
	//===========================================================================================
	BinaryNode* d = new BinaryNode('D', NULL, NULL);
	BinaryNode* e = new BinaryNode('E', NULL, NULL);
	BinaryNode* f = new BinaryNode('F', NULL, NULL);
	BinaryNode* g = new BinaryNode('G', NULL, NULL);
	BinaryNode* b = new BinaryNode('B', d, e);
	BinaryNode* c = new BinaryNode('C', f, g);
	BinaryNode* a = new BinaryNode('A', b, c);
	tree.setRoot(a);

	printf("===================================================================================\n");
	printf("�׽�Ʈ ���̽� 1: �������� ��ȭ ����Ʈ�� =>");
	tree.inorder(); //���� ��ȸ
	//tree.preorder();
	//tree.postorder();
	//tree.levelorder();
	printf("\n\n");

	//��ȭ ����Ʈ�� ����
	if (tree.isFull()) { printf("�� Ʈ���� ��ȭ ����Ʈ���Դϴ�.\n"); }
	else { printf("�� Ʈ���� ��ȭ ����Ʈ���� �ƴմϴ�.\n"); }
	printf("\n");

	//������ ���� ����Ʈ�� ����
	if (tree.isBalanced()) { printf("�� Ʈ���� ������ �����ֽ��ϴ�.\n"); }
	else { printf("�� Ʈ���� ������ �������� �ʽ��ϴ�.\n");; }
	printf("\n");

	//�ڹٲٱ� ����
	tree.reverse();
	printf("�¿� ��Ī ���. =>"); tree.inorder();
	printf("\n");
	printf("===================================================================================\n");
	printf("\n");
	//===========================================================================================
	*/

	/*
	//===========================================================================================
	// �׽�Ʈ ���̽� 2
	// �˻��ϴ� �Լ�: �������� ��ȭ ����Ʈ�� (Ʈ���� ���̰� 4)
	//                  A
	//            B            C
	//         D     E      F     G
	//       H  I   J  K  L   M N   O
	//===========================================================================================
	BinaryNode* h = new BinaryNode('H', NULL, NULL);
	BinaryNode* i = new BinaryNode('I', NULL, NULL);
	BinaryNode* j = new BinaryNode('J', NULL, NULL);
	BinaryNode* k = new BinaryNode('K', NULL, NULL);
	BinaryNode* l = new BinaryNode('L', NULL, NULL);
	BinaryNode* m = new BinaryNode('M', NULL, NULL);
	BinaryNode* n = new BinaryNode('N', NULL, NULL);
	BinaryNode* o = new BinaryNode('O', NULL, NULL);
	BinaryNode* d = new BinaryNode('D', h, i);
	BinaryNode* e = new BinaryNode('E', j, k);
	BinaryNode* f = new BinaryNode('F', l, m);
	BinaryNode* g = new BinaryNode('G', n, o);
	BinaryNode* b = new BinaryNode('B', d, e);
	BinaryNode* c = new BinaryNode('C', f, g);
	BinaryNode* a = new BinaryNode('A', b, c);
	tree.setRoot(a);

	printf("===================================================================================\n");
	printf("�׽�Ʈ ���̽� 2: �������� ��ȭ ����Ʈ�� =>");
	tree.inorder(); //���� ��ȸ
	//tree.preorder();
	//tree.postorder();
	//tree.levelorder();
	printf("\n\n");

	//��ȭ ����Ʈ�� ����
	if (tree.isFull()) { printf("�� Ʈ���� ��ȭ ����Ʈ���Դϴ�.\n"); }
	else { printf("�� Ʈ���� ��ȭ ����Ʈ���� �ƴմϴ�.\n"); }
	printf("\n");

	//������ ���� ����Ʈ�� ����
	if (tree.isBalanced()) { printf("�� Ʈ���� ������ �����ֽ��ϴ�.\n"); }
	else { printf("�� Ʈ���� ������ �������� �ʽ��ϴ�.\n");; }
	printf("\n");

	//�ڹٲٱ� ����
	tree.reverse();
	printf("�¿� ��Ī ���. =>"); tree.inorder();
	printf("\n");
	printf("===================================================================================\n");
	printf("\n");
	//===========================================================================================
	*/

	/*
	//===========================================================================================
	// �׽�Ʈ ���̽� 3
	// �˻��ϴ� �Լ�: �������� ���� ����Ʈ�� (Ʈ���� ���̰� 3)
	//                  A
	//            B            C
	//         D     E
	//===========================================================================================
	BinaryNode* d = new BinaryNode('D', NULL, NULL);
	BinaryNode* e = new BinaryNode('E', NULL, NULL);
	BinaryNode* b = new BinaryNode('B', d, e);
	BinaryNode* c = new BinaryNode('C', NULL, NULL);
	BinaryNode* a = new BinaryNode('A', b, c);
	tree.setRoot(a);

	printf("===================================================================================\n");
	printf("�׽�Ʈ ���̽� 3: �������� ���� ����Ʈ�� =>");
	tree.inorder(); //���� ��ȸ
	//tree.preorder();
	//tree.postorder();
	//tree.levelorder();
	printf("\n\n");

	//��ȭ ����Ʈ�� ����
	if (tree.isFull()) { printf("�� Ʈ���� ��ȭ ����Ʈ���Դϴ�.\n"); }
	else { printf("�� Ʈ���� ��ȭ ����Ʈ���� �ƴմϴ�.\n"); }
	printf("\n");

	//������ ���� ����Ʈ�� ����
	if (tree.isBalanced()) { printf("�� Ʈ���� ������ �����ֽ��ϴ�.\n"); }
	else { printf("�� Ʈ���� ������ �������� �ʽ��ϴ�.\n");; }
	printf("\n");

	//�ڹٲٱ� ����
	tree.reverse();
	printf("�¿� ��Ī ���. =>"); tree.inorder();
	printf("\n");
	printf("===================================================================================\n");
	printf("\n");
	//===========================================================================================
	*/

	/*
	//===========================================================================================
	// �׽�Ʈ ���̽� 4
	// �˻��ϴ� �Լ�: �������� ���� ����Ʈ�� (Ʈ���� ���̰� 4)
	//                  A
	//            B            C
	//         D     E      F      G
	//       H   I
	//===========================================================================================
	BinaryNode* h = new BinaryNode('H', NULL, NULL);
	BinaryNode* i = new BinaryNode('I', NULL, NULL);
	BinaryNode* d = new BinaryNode('D', h, i);
	BinaryNode* e = new BinaryNode('E', NULL, NULL);
	BinaryNode* f = new BinaryNode('F', NULL, NULL);
	BinaryNode* g = new BinaryNode('G', NULL, NULL);
	BinaryNode* b = new BinaryNode('B', d, e);
	BinaryNode* c = new BinaryNode('C', f, g);
	BinaryNode* a = new BinaryNode('A', b, c);
	tree.setRoot(a);

	printf("===================================================================================\n");
	printf("�׽�Ʈ ���̽� 4: �������� ���� ����Ʈ�� =>");
	tree.inorder(); //���� ��ȸ
	//tree.preorder();
	//tree.postorder();
	//tree.levelorder();
	printf("\n\n");

	//��ȭ ����Ʈ�� ����
	if (tree.isFull()) { printf("�� Ʈ���� ��ȭ ����Ʈ���Դϴ�.\n"); }
	else { printf("�� Ʈ���� ��ȭ ����Ʈ���� �ƴմϴ�.\n"); }
	printf("\n");

	//������ ���� ����Ʈ�� ����
	if (tree.isBalanced()) { printf("�� Ʈ���� ������ �����ֽ��ϴ�.\n"); }
	else { printf("�� Ʈ���� ������ �������� �ʽ��ϴ�.\n");; }
	printf("\n");

	//�ڹٲٱ� ����
	tree.reverse();
	printf("�¿� ��Ī ���. =>"); tree.inorder();
	printf("\n");
	printf("===================================================================================\n");
	printf("\n");
	//===========================================================================================
	*/

	/*
	//===========================================================================================
	// �׽�Ʈ ���̽� 5
	// �˻��ϴ� �Լ�: ���� 340p 1�� �׸�: ��ȭ ���� Ʈ�� X, ���� O, reverse ����
	//          A
	//      B        E
	//   C     D         F
	//===========================================================================================

	BinaryNode* c = new BinaryNode('C', NULL, NULL);
	BinaryNode* d = new BinaryNode('D', NULL, NULL);
	BinaryNode* b = new BinaryNode('B', c, d);
	BinaryNode* f = new BinaryNode('F', NULL, NULL);
	BinaryNode* e = new BinaryNode('E', NULL, f);
	BinaryNode* a = new BinaryNode('A', b, e);
	tree.setRoot(a);

	printf("===================================================================================\n");
	printf("�׽�Ʈ ���̽� 5: ���� 340p =>");
	tree.inorder(); //���� ��ȸ
	//tree.preorder();
	//tree.postorder();
	//tree.levelorder();
	printf("\n\n");

	//��ȭ ����Ʈ�� ����
	if (tree.isFull()) { printf("�� Ʈ���� ��ȭ ����Ʈ���Դϴ�.\n"); }
	else { printf("�� Ʈ���� ��ȭ ����Ʈ���� �ƴմϴ�.\n"); }
	printf("\n");

	//������ ���� ����Ʈ�� ����
	if (tree.isBalanced()) { printf("�� Ʈ���� ������ �����ֽ��ϴ�.\n");}
	else { printf("�� Ʈ���� ������ �������� �ʽ��ϴ�.\n");; }
	printf("\n");

	//�ڹٲٱ� ����
	tree.reverse();
	printf("�¿� ��Ī ���. =>"); tree.inorder();
	printf("\n");
	printf("===================================================================================\n");
	printf("\n");

	//===========================================================================================
	*/

	/*
	//===========================================================================================
	// �׽�Ʈ ���̽� 6
	// �˻��ϴ� �Լ�: ��Ʈ ��� ���忡���� ������������, ����Ʈ�������� ���������� ���� ���
	//                  A
	//            B            C
	//         D     E            G
	//                          H
	// A�� ����: ���� Ʈ�� ������ ���� 2, 3�̹Ƿ� ��������
	// B�� ����: ���� Ʈ�� ������ ���� 1, 1�̹Ƿ� ��������
	// C�� ����: ���� Ʈ�� ������ ���� 0, 2�̹Ƿ� ���������� ����
	//===========================================================================================
	BinaryNode* h = new BinaryNode('H', NULL, NULL);
	BinaryNode* d = new BinaryNode('D', NULL, NULL);
	BinaryNode* e = new BinaryNode('E', NULL, NULL);
	BinaryNode* g = new BinaryNode('G', h, NULL);
	BinaryNode* b = new BinaryNode('B', d, e);
	BinaryNode* c = new BinaryNode('C', NULL, g);
	BinaryNode* a = new BinaryNode('A', b, c);
	tree.setRoot(a);

	printf("===================================================================================\n");
	printf("�׽�Ʈ ���̽� 6: ����Ʈ�������� ���������� ���� ����Ʈ�� =>");
	tree.inorder(); //���� ��ȸ
	//tree.preorder();
	//tree.postorder();
	//tree.levelorder();
	printf("\n\n");

	//��ȭ ����Ʈ�� ����
	if (tree.isFull()) { printf("�� Ʈ���� ��ȭ ����Ʈ���Դϴ�.\n"); }
	else { printf("�� Ʈ���� ��ȭ ����Ʈ���� �ƴմϴ�.\n"); }
	printf("\n");

	//������ ���� ����Ʈ�� ����
	if (tree.isBalanced()) { printf("�� Ʈ���� ������ �����ֽ��ϴ�.\n"); }
	else { printf("�� Ʈ���� ������ �������� �ʽ��ϴ�.\n");; }
	printf("\n");

	//�ڹٲٱ� ����
	tree.reverse();
	printf("�¿� ��Ī ���. =>"); tree.inorder();
	printf("\n");
	printf("===================================================================================\n");
	printf("\n");
	//===========================================================================================
	*/

	/*
	//===========================================================================================
	// �׽�Ʈ ���̽� 7
	// �˻��ϴ� �Լ�: ���������� ���������� ���� ����Ʈ��
	//                  A
	//            B
	//         C     D
	//===========================================================================================
	BinaryNode* d = new BinaryNode('D', NULL, NULL);
	BinaryNode* c = new BinaryNode('C', NULL, NULL);
	BinaryNode* b = new BinaryNode('B', c, d);
	BinaryNode* a = new BinaryNode('A', b, NULL);
	tree.setRoot(a);

	printf("===================================================================================\n");
	printf("�׽�Ʈ ���̽� 7: ���������� ���������� ���� ����Ʈ�� =>");
	tree.inorder(); //���� ��ȸ
	//tree.preorder();
	//tree.postorder();
	//tree.levelorder();
	printf("\n\n");

	//��ȭ ����Ʈ�� ����
	if (tree.isFull()) { printf("�� Ʈ���� ��ȭ ����Ʈ���Դϴ�.\n"); }
	else { printf("�� Ʈ���� ��ȭ ����Ʈ���� �ƴմϴ�.\n"); }
	printf("\n");

	//������ ���� ����Ʈ�� ����
	if (tree.isBalanced()) { printf("�� Ʈ���� ������ �����ֽ��ϴ�.\n"); }
	else { printf("�� Ʈ���� ������ �������� �ʽ��ϴ�.\n");; }
	printf("\n");

	//�ڹٲٱ� ����
	tree.reverse();
	printf("�¿� ��Ī ���. =>"); tree.inorder();
	printf("\n");
	printf("===================================================================================\n");
	printf("\n");
	//===========================================================================================
	*/

	/*
	//===========================================================================================
	// �׽�Ʈ ���̽� 8
	// �˻��ϴ� �Լ�: ���������� ���������� ���� ����Ʈ��
	//                  A
	//            B           C
	//         D     E
	//                 F
	//===========================================================================================
	BinaryNode* f = new BinaryNode('F', NULL, NULL);
	BinaryNode* d = new BinaryNode('D', NULL, NULL);
	BinaryNode* e = new BinaryNode('E', NULL, f);
	BinaryNode* c = new BinaryNode('C', NULL, NULL);
	BinaryNode* b = new BinaryNode('B', d, e);
	BinaryNode* a = new BinaryNode('A', b, c);
	tree.setRoot(a);

	printf("===================================================================================\n");
	printf("�׽�Ʈ ���̽� 8: ���������� ���������� ���� ����Ʈ�� =>");
	tree.inorder(); //���� ��ȸ
	//tree.preorder();
	//tree.postorder();
	//tree.levelorder();
	printf("\n\n");

	//��ȭ ����Ʈ�� ����
	if (tree.isFull()) { printf("�� Ʈ���� ��ȭ ����Ʈ���Դϴ�.\n"); }
	else { printf("�� Ʈ���� ��ȭ ����Ʈ���� �ƴմϴ�.\n"); }
	printf("\n");

	//������ ���� ����Ʈ�� ����
	if (tree.isBalanced()) { printf("�� Ʈ���� ������ �����ֽ��ϴ�.\n"); }
	else { printf("�� Ʈ���� ������ �������� �ʽ��ϴ�.\n");; }
	printf("\n");

	//�ڹٲٱ� ����
	tree.reverse();
	printf("�¿� ��Ī ���. =>"); tree.inorder();
	printf("\n");
	printf("===================================================================================\n");
	printf("\n");
	//===========================================================================================
	*/

	/*
	//===========================================================================================
	// �׽�Ʈ ���̽� 9
	// �˻��ϴ� �Լ�: ��� ����Ʈ��(skewed binary tree)
	//                  A
	//            B
	//         C
	//      D
	//===========================================================================================

	BinaryNode* d = new BinaryNode('D', NULL, NULL);
	BinaryNode* c = new BinaryNode('C', d, NULL);
	BinaryNode* b = new BinaryNode('B', c, NULL);
	BinaryNode* a = new BinaryNode('A', b, NULL);
	tree.setRoot(a);

	printf("===================================================================================\n");
	printf("�׽�Ʈ ���̽� 9: ��� ����Ʈ�� =>");
	tree.inorder(); //���� ��ȸ
	//tree.preorder();
	//tree.postorder();
	//tree.levelorder();
	printf("\n\n");

	//��ȭ ����Ʈ�� ����
	if (tree.isFull()) { printf("�� Ʈ���� ��ȭ ����Ʈ���Դϴ�.\n"); }
	else { printf("�� Ʈ���� ��ȭ ����Ʈ���� �ƴմϴ�.\n"); }
	printf("\n");

	//������ ���� ����Ʈ�� ����
	if (tree.isBalanced()) { printf("�� Ʈ���� ������ �����ֽ��ϴ�.\n"); }
	else { printf("�� Ʈ���� ������ �������� �ʽ��ϴ�.\n");; }
	printf("\n");

	//�ڹٲٱ� ����
	tree.reverse();
	printf("�¿� ��Ī ���. =>"); tree.inorder();
	printf("\n");
	printf("===================================================================================\n");
	printf("\n");
	//===========================================================================================
	*/

	/*
	//===========================================================================================
	// �׽�Ʈ ���̽� 10
	// �˻��ϴ� �Լ�: ��� ����Ʈ��(skewed binary tree)
	//                  A
	//                      B
	//                          C
	//                             D
	//===========================================================================================

	BinaryNode* d = new BinaryNode('D', NULL, NULL);
	BinaryNode* c = new BinaryNode('C', NULL, d);
	BinaryNode* b = new BinaryNode('B', NULL, c);
	BinaryNode* a = new BinaryNode('A', NULL, b);
	tree.setRoot(a);

	printf("===================================================================================\n");
	printf("�׽�Ʈ ���̽� 10: ��� ����Ʈ�� =>");
	tree.inorder(); //���� ��ȸ
	//tree.preorder();
	//tree.postorder();
	//tree.levelorder();
	printf("\n\n");

	//��ȭ ����Ʈ�� ����
	if (tree.isFull()) { printf("�� Ʈ���� ��ȭ ����Ʈ���Դϴ�.\n"); }
	else { printf("�� Ʈ���� ��ȭ ����Ʈ���� �ƴմϴ�.\n"); }
	printf("\n");

	//������ ���� ����Ʈ�� ����
	if (tree.isBalanced()) { printf("�� Ʈ���� ������ �����ֽ��ϴ�.\n"); }
	else { printf("�� Ʈ���� ������ �������� �ʽ��ϴ�.\n");; }
	printf("\n");

	//�ڹٲٱ� ����
	tree.reverse();
	printf("�¿� ��Ī ���. =>"); tree.inorder();
	printf("\n");
	printf("===================================================================================\n");
	printf("\n");
	//===========================================================================================
	*/

	/*
	//===========================================================================================
	// �׽�Ʈ ���̽� 11
	// �˻��ϴ� �Լ�: ���� ����Ʈ��(degenerated binary tree)
	//                  A
	//              B
	//                 C
	//               D
	//===========================================================================================

	BinaryNode* d = new BinaryNode('D', NULL, NULL);
	BinaryNode* c = new BinaryNode('C', d, NULL);
	BinaryNode* b = new BinaryNode('B', NULL, c);
	BinaryNode* a = new BinaryNode('A', b, NULL);
	tree.setRoot(a);

	printf("===================================================================================\n");
	printf("�׽�Ʈ ���̽� 9: ��� ����Ʈ�� =>");
	tree.inorder(); //���� ��ȸ
	//tree.preorder();
	//tree.postorder();
	//tree.levelorder();
	printf("\n\n");

	//��ȭ ����Ʈ�� ����
	if (tree.isFull()) { printf("�� Ʈ���� ��ȭ ����Ʈ���Դϴ�.\n"); }
	else { printf("�� Ʈ���� ��ȭ ����Ʈ���� �ƴմϴ�.\n"); }
	printf("\n");

	//������ ���� ����Ʈ�� ����
	if (tree.isBalanced()) { printf("�� Ʈ���� ������ �����ֽ��ϴ�.\n"); }
	else { printf("�� Ʈ���� ������ �������� �ʽ��ϴ�.\n");; }
	printf("\n");

	//�ڹٲٱ� ����
	tree.reverse();
	printf("�¿� ��Ī ���. =>"); tree.inorder();
	printf("\n");
	printf("===================================================================================\n");
	printf("\n");
	//===========================================================================================
	*/


	//===========================================================================================
	// �׽�Ʈ ���̽� 12
	// �˻��ϴ� �Լ�: ���� Ʈ�� (��Ʈ �����Ͱ� NULL, �� ��� 1���� NULL�� �ִ� ���)
	// ���� Ʈ���� ���ǻ� ����Ʈ��
	//===========================================================================================
	BinaryNode* a = new BinaryNode(NULL, NULL, NULL);
	tree.setRoot(a);

	printf("===================================================================================\n");
	printf("�׽�Ʈ ���̽� 12: ���� Ʈ�� =>");
	tree.inorder(); //���� ��ȸ
	//tree.preorder();
	//tree.postorder();
	//tree.levelorder();
	printf("\n\n");

	//��ȭ ����Ʈ�� ����
	if (tree.isFull()) { printf("�� Ʈ���� ��ȭ ����Ʈ���Դϴ�.\n"); }
	else { printf("�� Ʈ���� ��ȭ ����Ʈ���� �ƴմϴ�.\n"); }
	printf("\n");

	//������ ���� ����Ʈ�� ����
	if (tree.isBalanced()) { printf("�� Ʈ���� ������ �����ֽ��ϴ�.\n"); }
	else { printf("�� Ʈ���� ������ �������� �ʽ��ϴ�.\n");; }
	printf("\n");

	//�ڹٲٱ� ����
	tree.reverse();
	printf("�¿� ��Ī ���. =>"); tree.inorder();
	printf("\n");
	printf("===================================================================================\n");
	printf("\n");
	//===========================================================================================

	return 0;
}
