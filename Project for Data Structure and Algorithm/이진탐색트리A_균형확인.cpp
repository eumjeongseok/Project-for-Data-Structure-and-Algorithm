#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <algorithm>
#include <climits> //INT_MAX, INT_MIN을 사용하기 위한 헤더
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

	//=====================================================================================
	// 자료구조 과제를 위한 함수 중 bool isBalanced() 추가
	//=====================================================================================
	//균형이 잡혀있는지를 검사하는 함수 - 왼쪽 서브트리와 오른쪽 서브트리의 높이의 차이가 2보다 작은지를 검사
	//O(n)의 시간 복잡도를 수행 - 재귀를 없애고, 스택을 이용하여 반복적으로 수행
	bool isBalanced() {
		if (root == NULL)
			return true; // 공백 트리는 균형 잡혀있다고 간주

		stack<BinaryNode*> nodes; //노드를 위한 스택
		stack<int> heights; //높이를 위한 스택
		nodes.push(root);
		heights.push(1); //높이의 초기값은 1
		int minimum_height = INT_MAX; //무한히 큰 수(설정)
		int maximum_height = INT_MIN; //무한히 작은 수(설정)

		while (!nodes.empty()) {
			//스택에서 원소를 뽑아 옴
			BinaryNode* current_state = nodes.top();
			int height = heights.top();
			nodes.pop();
			heights.pop();

			if (current_state->isLeaf()) {
				// 잎 노드인 경우 최소 높이와 최대 높이 갱신
				minimum_height = min(minimum_height, height);
				maximum_height = max(maximum_height, height);
				//이 과정은 지금 현재의 높이와 현재 기록된 최소/최대 높이 중 최소/최대의 값을 고르는 과정!
			}
			else {
				// 왼쪽 자식 노드가 있는 경우 스택에 추가
				if (current_state->getLeft() != NULL) {
					nodes.push(current_state->getLeft());
					heights.push(height + 1); //뽑은 값에서 1 추가
				}

				// 오른쪽 자식 노드가 있는 경우 스택에 추가
				if (current_state->getRight() != NULL) {
					nodes.push(current_state->getRight());
					heights.push(height + 1); //뽑은 값에서 1 추가
				}
			}
		}
		return (maximum_height - minimum_height) <= 1;
	}

	//=====================================================================================
	// 자료구조 과제를 위한 함수 끝
	//=====================================================================================

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
			BinaryNode* succ = node->getRight(); //왼쪽부터 수행시 getLeft()

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
BinSrchTree tree; //객체 생성

void switchInput(string order, int key) {
	if (order == "I") { //삽입 연산
		tree.insert(new BinaryNode(key));
	}
	else if (order == "D") { //삭제 연산
		tree.remove(key);
	}
	else { return; }
}

int main() {

	int n; //작업의 수
	cin >> n;

	string order; //명령(I, D)
	int key; //key값
	for (int j = 0; j < n; j++) {
		cin >> order >> key;
		switchInput(order, key);
	}

	if (tree.isBalanced() == true) { printf("Balanced"); }
	else { printf("Unbalanced");; }

	return 0;
}
