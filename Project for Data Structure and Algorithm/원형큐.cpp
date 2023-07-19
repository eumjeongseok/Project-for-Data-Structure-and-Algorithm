#pragma once
//원형큐 구현

#include <cstdio>
#include <cstdlib>
#define MAX_QUEUE_SIZE 100

inline void error(const char* str) 
{
	printf("% s\n", str);
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

int main()
{
	CircularQueue que; //큐 객체 생성
	for (int i = 1; i < 10; i++)
	{
		que.enqueue(i); //1부터 9까지 정수 생성
	}
	que.display();
	que.dequeue();
	que.dequeue();
	que.dequeue();
	que.display();
}