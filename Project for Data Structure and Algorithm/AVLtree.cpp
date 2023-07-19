//AVL 트리?
//왼쪽 서브트리의 높이와 오른쪽 서브트리의 높이 차이가 1 이하인 이진 탐색 트리
//탐색 시간: O(logn)
//AVL 트리에서 균형이 깨지는 경우: 삽입 연산, 삭제 연산

//균형이 깨지는 타입
//LL 타입: N이 A의 왼쪽 서브트리의 왼쪽 서브트리에 입력
//LR 타입: N이 A의 왼쪽 서브트리의 오른쪽 서브트리에 입력
//RR 타입: N이 A의 오른쪽 서브트리의 오른쪽 서브트리에 입력
//RL 타입: N이 A의 오른쪽 서브트리의 왼쪽 서브트리에 입력

//균형을 잡는 방법
// 1. 단순 회전(single rotation): 한 번만 회전
//LL 회전: A부터 N까지의 경로상의 노드들을 오른쪽으로 회전
//RR 회전: A부터 N까지의 경로상의 노드들을 왼쪽으로 회전

// 2. 이중 회전(double rotation): 두 번 회전
//LR 회전: A부터 N까지의 경로상의 노드들을 왼쪽-오른쪽으로 회전
//RL 회전: A부터 N까지의 경로상의 노드들을 오른쪽-왼쪽으로 회전


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
	int data; //트리에 저장할 데이터
	BinaryNode* left; //왼쪽 자식 노드의 포인터
	BinaryNode* right; //오른쪽 자식 노드의 포인터

public:
	BinaryNode(int val = 0, BinaryNode* l = NULL, BinaryNode* r = NULL)
		: data(val), left(l), right(r) { }

	//키 값으로 노드를 탐색하는 함수(노드 클래스에서 순환으로 구현)
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

	int getData() { return data; } //노드값 반환
	BinaryNode* getLeft() { return left; } //왼쪽 노드값 반환
	BinaryNode* getRight() { return right; } //오른쪽 노드값 반환

	bool isLeaf() { return left == NULL && right == NULL; } //잎 노드 여부 확인
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
		if (isFull()) { error("  Error: 큐가 포화상태입니다.\n"); }
		else {
			rear = (rear + 1) % MAX_QUEUE_SIZE;
			data[rear] = n;
		}
	}
	BinaryNode* dequeue() {
		if (isEmpty()) { error("  Error: 큐가 공백상태입니다.\n"); }
		else {
			front = (front + 1) % MAX_QUEUE_SIZE;
			return data[front];
		}
	}
};

class BinaryTree {

public:

	BinaryNode* root; //루트 포인터

	//(1)번 함수
	bool isFull() {
		//이진트리가 완전 이진트리인지 검사하는 함수

		if (!isEmpty()) {
			CircularQueue q;
			q.enqueue(root);

			while (!q.isEmpty()) {

				BinaryNode* n = q.dequeue();

				//말단노드가 아니고 왼쪽 오른쪽 자식 중 하나라도 없으면 완전이진트리 X

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


	//(2)번 함수
	//레벨을 구하는 연산
	int level(BinaryNode* node) {
		return level(root, node);
	}
	int level(BinaryNode* node1, BinaryNode* node2, int lev = 1) {
		//node2가 우리가 찾고자 하는 node
		if (node1 == NULL)
			return 0;

		if (node1 == node2)
			return lev;

		if (node1->getLeft() == NULL && node1->getRight() == NULL)
			return 0;

		//재귀
		int left = level(node1->getLeft(), node2, lev + 1); //왼쪽으로
		int right = level(node1->getRight(), node2, lev + 1); //오른쪽으로

		if (!left) //왼쪽 노드가 존재하지 않는다면
			return right; //오른쪽 노드 반환

		else //반대
			return left;
	}

	//(3)번 함수
	bool isBalanced() {
		//균형이 잡혀있는가?
		return isBalanced(root);
	}
	bool isBalanced(BinaryNode* node) {
		int leftHeight;
		int rightHeight;

		if (node == NULL)
			return true;

		leftHeight = getHeight(node->getLeft());
		rightHeight = getHeight(node->getRight());

		//왼쪽 서브트리와 오른쪽서브트리의 높이차가 2이상 나지 않고 둘 다 균형이 잡혀있을 경우 참
		if ((leftHeight - rightHeight) <= 1 && (leftHeight - rightHeight) >= -1 && isBalanced(node->getLeft()) && isBalanced(node->getRight()))
			return true;

		return false;
	}

	//경로의 길이
	int pathLength() {
		int sum = 0;

		if (!isEmpty()) {
			CircularQueue q;
			q.enqueue(root);

			while (!q.isEmpty()) {
				BinaryNode* n = q.dequeue();

				sum += level(n) - 1; //각 노드의 레벨-1만큼 더하면 총 경로

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


	//(4)번 함수
	 //뒤바꾼다
	bool reverse() {
		return reverse(root);
	}
	bool reverse(BinaryNode* node) {
		if (node == NULL)
			return false;
		else {
			//재귀
			reverse(node->getLeft());
			reverse(node->getRight());
			//leftNode와 rightNode를 서로 바꾼다
			BinaryNode* temp = node->getLeft();
			node->setLeft(node->getRight());
			node->setRight(temp);
		}
		return true;
	}




	BinaryTree() : root(NULL) { }
	void setRoot(BinaryNode* node) { root = node; }
	BinaryNode* getRoot() { return root; } //루트 노드값 반환

	bool isEmpty() { return root == NULL; } //빈 트리 여부 확인

	//이진트리의 순회 연산
	void inorder() { printf("\n   inorder: "); inorder(root); }
	void inorder(BinaryNode* node) {
		//중위 순회: LVR
		if (node != NULL) { //루트 노드가 0이 아닐 때
			inorder(node->getLeft()); //왼쪽 서브트리
			printf(" [%d] ", node->getData()); //루트 노드 처리
			inorder(node->getRight()); //오른쪽 서브트리
		}
	}

	void preorder() { printf("\n  preorder: "); preorder(root); }
	void preorder(BinaryNode* node) {
		//전위 순회: VLR
		if (node != NULL) { //루트 노드가 0이 아닐 때
			printf(" [%d] ", node->getData()); //루트 노드 처리
			preorder(node->getLeft()); //왼쪽 서브트리
			preorder(node->getRight()); //오른쪽 서브트리
		}
	}

	void postorder() { printf("\n postorder: "); postorder(root); }
	void postorder(BinaryNode* node) {
		//후위 순회: LRV
		if (node != NULL) { //루트 노드가 0이 아닐 때
			postorder(node->getLeft()); //왼쪽 서브트리
			postorder(node->getRight()); //오른쪽 서브트리
			printf(" [%d] ", node->getData()); //루트 노드 처리
		}
	}

	//레벨 순회(BFS: 깊이 우선 탐색)
	void levelorder() {
		printf("\nlevelorder: ");
		if (!isEmpty()) {
			CircularQueue q;
			q.enqueue(root);
			//먼저 루트를 큐에 넣는다.

			while (!q.isEmpty()) {
				BinaryNode* n = q.dequeue();
				//큐가 비어있지 않으면 큐에서 삭제

				if (n != NULL) {
					//n이 NULL이 아닐 때
					printf(" [%d] ", n->getData()); //n을 표시하고
					q.enqueue(n->getLeft());//왼쪽 노드를 큐에 넣는다.
					q.enqueue(n->getRight());//오른쪽 노드를 큐에 넣는다.
				}
				//공백 상태가 될 때까지 while문 반복
			}
		}
		printf("\n");
	}

	//이진트리의 추가 연산
	//트리의 노드 개수를 구하는 함수
	int getCount() { return isEmpty() ? 0 : getCount(root); }
	//순환 호출에 의해 node를 루트로 하는 서브트리의 노드 수 계산 함수
	int getCount(BinaryNode* node) {
		if (node == NULL) { return 0; }
		return (1 + getCount(node->getLeft()) + getCount(node->getRight()));
	}

	//트리의 높이를 구하는 함수
	int getHeight() { return isEmpty() ? 0 : getHeight(root); }
	int getHeight(BinaryNode* node) {
		if (node == NULL) { return 0; }
		int hLeft = getHeight(node->getLeft());
		int hRight = getHeight(node->getRight());
		return ((hLeft > hRight) ? hLeft + 1 : hRight + 1);
		//問: 왜 다른 곳과 달리, hLeft, hRight를 쓰는 것일까?
		//答: 편의상 하는 것, 굳이 없어도 return만 잘 구현하면 상관 없음
	}

	//트리의 잎 노드(단말노드) 개수를 구하는 함수
	int getLeafCount() { return isEmpty() ? 0 : getLeafCount(root); }
	//순환 호출에 의해 node를 루트로 하는 서브트리의 단말 노드 수 계산 함수
	int getLeafCount(BinaryNode* node) {
		if (node == NULL) { return 0; }
		if (node->isLeaf()) { return 1; } //잎 노드!
		else return (getLeafCount(node->getLeft()) + getLeafCount(node->getRight()));
	}

	int evaluate() { return evaluate(root); }
	//순환 호출에 의해 node를 루트로 하는 수식 트리의 계산 함수
	int evaluate(BinaryNode* node) {
		if (node == NULL) { return 0; }
		if (node->isLeaf()) { return node->getData(); }
		else {
			int op1 = evaluate(node->getLeft()); //왼쪽 노드 값
			int op2 = evaluate(node->getRight()); //오른쪽 노드 값
			switch (node->getData()) { //부모 노드는 연산자
			case '+': return (op1 + op2);
			case '-': return (op1 - op2);
			case '*': return (op1 * op2);
			case '/': return (op1 / op2);
			}
			return 0;
		}
	}

	//디렉터리 용량 계산 함수
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

	//이진 탐색 트리의 탐색 연산
	BinaryNode* search(int key) {
		BinaryNode* node = searchRecur(root, key);
		if (node != NULL) {
			printf("탐색 성공: 키값이 %d인 노드 = 0x%x\n", node->getData(), node);
		}
		else {
			printf("키값이 %d인 노드 없음\n", key);
		}
		return node;
	}
	//키 값으로 노드를 탐색하는 함수(순환적 방법)
	//일반 함수로 구현(BinSrchTree의 멤버 함수로 넣어도 됨)
	BinaryNode* searchRecur(BinaryNode* n, int key) {
		if (n == NULL) { return NULL; } //못 찾았다.
		if (key == n->getData()) { return n; }
		else if (key < n->getData()) { return searchRecur(n->getLeft(), key); }
		else return searchRecur(n->getRight(), key);
	}

	//키 값으로 노드를 탐색하는 함수(반복적인 방법)
	//일반 함수로 구현(BinSrchTree의 멤버 함수로 넣어도 됨)
	BinaryNode* SearchIter(BinaryNode* n, int key) {
		while (n != NULL) {
			if (key == n->getData()) { return n; }
			else if (key < n->getData()) { n = n->getLeft(); }
			else { n = n->getRight(); }
		}
		return n;
	}
	//=============================================================


	//이진 탐색 트리의 삽입 연산
	void insert(BinaryNode* n) {
		if (n == NULL) { return; }
		if (isEmpty()) { root = n; }
		else { insertRucur(root, n); }

	}
	//이진 탐색 트리의 삼입 함수
	void insertRucur(BinaryNode* r, BinaryNode* n) {
		//root와 key가 같으면 return
		if (n->getData() == r->getData()) { return; }
		//root보다 key가 작을 때
		else if (n->getData() < r->getData()) {
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
	void remove(int key) {
		if (isEmpty()) { return; } //빈 트리이면 return

		//없앨 노드와 그 노드의 부모 노드를 찾는다.
		BinaryNode* parent = NULL; //부모 노드
		BinaryNode* node = root; //루트 노드
		while (node != NULL && node->getData() != key) {
			parent = node;
			node = (key < node->getData()) ? node->getLeft() : node->getRight();
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
			if (parent == NULL) { root = NULL; } //node == root이면 루트만 있는 상태
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
			node = succ;
		}
		delete node; //메모리 동적 해제
	}
};

//AVL 트리 클래스
class AVLTree : public BinSrchTree {
public:
	//노드의 균형 인수 반환
	int getHeightDiff(BinaryNode* node) {
		if (node == NULL) { return 0; }
		int hLeft = getHeight(node->getLeft());
		int hRight = getHeight(node->getRight());
		return hLeft - hRight;
	}

	//LL 회전 함수
	BinaryNode* rotateLL(BinaryNode* parent) {
		BinaryNode* child = parent->getLeft();
		parent->setLeft(child->getRight()); //child의 오른쪽 자식을 parent의 왼쪽 자식으로 만든다.
		child->setRight(parent); //parent를 child의 오른쪽 자식 노드로 만든다.
		printf("LL ");
		return child;
	}

	//RR 회전 함수
	BinaryNode* rotateRR(BinaryNode* parent) {
		BinaryNode* child = parent->getRight();
		parent->setRight(child->getLeft());
		child->setLeft(parent);
		printf("RR ");
		return child;
	}

	//RL 회전 함수
	BinaryNode* rotateRL(BinaryNode* parent) {
		BinaryNode* child = parent->getRight();
		printf("RL ");
		parent->setRight(rotateLL(child));
		return rotateRR(parent);
	}

	//LL 회전 함수
	BinaryNode* rotateLR(BinaryNode* parent) {
		BinaryNode* child = parent->getLeft();
		printf("LR ");
		parent->setLeft(rotateRR(child));
		return rotateLL(parent);
	}

	//트리를 균형트리로 만드는 작업
	BinaryNode* reBalance(BinaryNode* parent) {
		int hDiff = getHeightDiff(parent);
		if (hDiff > 1) {
			//만약 왼쪽 서브트리의 왼쪽 서브트리의 높이가 크면 LL, 그렇지 않으면 LR
			if (getHeightDiff(parent->getLeft()) > 0) { parent = rotateLL(parent); } //LL 타입 불균형
			else { parent = rotateLR(parent); } //LR 타입 불균형
		}
		else if (hDiff < -1) {
			//만약 오른쪽 서브트리의 오른쪽 서브트리의 높이가 작으면 RR, 그렇지 않으면 RL
			if (getHeightDiff(parent->getRight()) < 0) { parent = rotateRR(parent); }
			else { parent = rotateRL(parent); }
		}
		return parent;
	}

	//AVL 트리 삽입 연산
	void insert(int data) {
		if (isEmpty()) { root = new BinaryNode(data); }
		else root = insertAVL(root, data);
	}
	BinaryNode* insertAVL(BinaryNode* parent, int data) { //함수 오버로딩
		if (data < parent->getData()) { //parent가 왼쪽 자식으로 가야 하는 경우
			if (parent->getLeft() != NULL) { //왼쪽 자식이 없는 경우 바로 왼쪽 자식으로 설정
				parent->setLeft(insertAVL(parent->getLeft(), data));
			}
			else { //그렇지 않은 경우 왼쪽 자식 노드에게 입력 역할을 넘김
				parent->setLeft(new BinaryNode(data));
			}
			return reBalance(parent); //균형을 맞춘 후의 노드 반환
		}
		else if (data > parent->getData()) { //parent가 오른쪽 자식으로 가야 하는 경우
			if (parent->getRight() != NULL) { //오른쪽 자식이 없는 경우 바로 오른쪽 자식으로 설정 
				parent->setRight(insertAVL(parent->getRight(), data));
			}
			else { //그렇지 않은 경우 오른쪽 자식 노드에게 입력 역할을 넘김
				parent->setRight(new BinaryNode(data));
			}
			return reBalance(parent);
		}
		else {
			//parent가 현재 노드와 같은 값을 가지면 에러 출력 및 바로 반환
			printf("중복된 키 에러\n");
			return NULL;
		}
	}
};

int main() {
	AVLTree tree;
	//7, 8, 9, 2, 1, 5, 3, 6, 4 삽입
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