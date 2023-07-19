#pragma once
#include <cstdio>
#include <cstdlib>

//오류 처리 함수
//VS 2022부터는 어째서인지 char를 인식하지 못함
//원래 준수모드를 '아니오'로 바꾸어야 하지만, 이 기능이 이상하게도 사라짐

inline void error(const char* message)
{
	printf("%s\n", message);
	exit(1);
}

const int MAX_STACK_SIZE = 20;

class ArrayStack
{
	int top;
	int data[MAX_STACK_SIZE] = {0, 0, };

public:
	ArrayStack() { top = -1; } //스택 생성자: create()
	~ArrayStack() {} //스택 소멸자

	bool isEmpty() { return top == -1; }

	bool isFull() { return top == MAX_STACK_SIZE - 1; }

	void push(int e)
	{
		if (isFull()) { error("스택 포화 에러"); }
		data[++top] = e;
	}

	int pop()
	{
		if (isEmpty()) { error("스택 공백 에러"); }
		return data[top--];
	}

	int peek() //삭제하지 않고 요소 반환
	{
		if (isEmpty()) { error("스택 공백 에러"); }
		return data[top];
	}

	void display()
	{
		printf("[스택 항목의 수 = %2d] ==> ", top + 1);
		for (int i = 0; i <= top; i++)
		{
			printf("<%2d>", data[i]);
		}
		printf("\n");
	}
};

void main()
{
	ArrayStack stack;
	for (int i = 0; i < 20; i++)
	{
		stack.push(i);
	}

	stack.display();

	for (int i = 0; i < 21; i++)
	{
		stack.pop();
	}

	stack.display();
}