#pragma once
//원형큐 구현

#include <cstdio>
#include <cstdlib>
#define MAX_QUEUE_SIZE 100

inline void error(const char* str)
{
	printf("%s\n", str);
	exit(1);
}

class CircularQueue //원형큐 클래스
{
protected:
	int front;
	int rear;
	int data[MAX_QUEUE_SIZE];

public:
	CircularQueue() { front = rear = 0; } //생성자, 초기 설정

	bool isEmpty() { return front == rear; } //공백 상태

	bool isFull() { return (rear + 1) % MAX_QUEUE_SIZE == front; } //포화 상태

	//클래스를 만들 때에는 초기 설정이 가장 중요하다!
	//클래스에서 초기 설정을 무시하면, 클래스 자체가 생성될 수 없음!!!!!!

	void enqueue(int val) //추가 연산
	{
		if (isFull())
		{
			error("error: Queue is Full.\n");
		}
		else
		{
			rear = (rear + 1) % MAX_QUEUE_SIZE;
			data[rear] = val;
		}
	}

	int dequeue() //삭제 연산
	{
		if (isEmpty())
		{
			error("error: Queue is Empty.\n");
		}
		else
		{
			front = (front + 1) % MAX_QUEUE_SIZE;
			return data[front];
		}
	}

	int peek() //최상단 반환
	{
		if (isEmpty())
		{
			error("error: No more element in Queue.\n");
		}
		else
		{
			return data[(front + 1) % MAX_QUEUE_SIZE];
		}
	}

	void display() //출력 연산
	{
		printf("In the Queue : ");
		int maxi = (front < rear) ? rear : rear + MAX_QUEUE_SIZE; //삼항 연산자 사용

		for (int i = front + 1; i <= maxi; i++)
		{
			printf("[%2d] ", data[i % MAX_QUEUE_SIZE]); //2칸만큼의 공백을 두고 값 출력
		}
		printf("\n");

	}
};

//원형 덱 클래스
class CircularDeque : public CircularQueue {
	//원형큐 클래스 상속

public:

	CircularDeque() { } // 생성자

	void addRear(int val) { enqueue(val); } //enqueue() 연산과 같음

	int deleteFront() { return dequeue(); } //dequeue() 연산과 같음

	int getFront() { return peek(); } //peek() 재사용

	void addFront(int val) //전단 추가 연산
	{
		if (isFull())
		{
			error("   error: Dequeue is Full. \n");
		}
		else
		{
			data[front] = val;
			front = (front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
			//modulo opration
			//modulo opration을 쓰는 이유는 인덱스를 가리키기 위함이다.
		}
	}

	int deleteRear() //후단 삭제 연산
	{
		if (isEmpty())
		{
			error("   error: Dequeue is Empty. \n");
		}
		else
		{
			int ret = data[rear];
			rear = (rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
			//modulo opration
			return ret;
		}
	}

	int getRear() //후단 반환 연산
	{
		if (isEmpty())
		{
			error("   error: Dequeue is Empty. \n");
		}
		else
		{
			return data[rear];
		}
	}

	void display() //출력
	{
		printf("In the Dequeue: ");

		int maxi = (front < rear) ? rear : rear + MAX_QUEUE_SIZE;
		
		for (int i = front + 1; i <= maxi; i++)
		{
			printf("[%2d] ", data[i % MAX_QUEUE_SIZE]); 
		}
		printf("\n");
	}

}; 

int main()
{
	CircularDeque deq; //덱 객체 생성

	//홀수는 전단을 통해, 짝수는 후단을 통해 삽입
	for (int i = 1; i < 10; i++)
	{
		if (i % 2 == 1) {
			deq.addFront(i);
		}
		else {
			deq.addRear(i);
		}
	}
	//問: 왜 i % 2 == 1 이라고 정의하지 않는가?
	//어째서 i % 2라고만 정의해도 되는가?

	deq.display();
	deq.deleteFront();
	deq.deleteRear();
	deq.deleteFront();
	deq.display();
}