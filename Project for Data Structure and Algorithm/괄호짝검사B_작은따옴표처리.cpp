#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
const int MAX_STACK_SIZE = 20;


//���� ó�� �Լ�
inline void error(const char* message)
{
    printf("%s\n", message);
    exit(1);
}

class ArrayStack
{
    int top;
    char data[MAX_STACK_SIZE] = { };

public:
    ArrayStack() { top = -1; } //���� ������: create()
    ~ArrayStack() {} //���� �Ҹ���

    bool isEmpty() { return top == -1; }

    bool isFull() { return top == MAX_STACK_SIZE - 1; }

    void push(int e)
    {
        if (isFull()) { error("���� ��ȭ ����"); }
        data[++top] = e;
    }

    int pop()
    {
        if (isEmpty()) { error("���� ���� ����"); }
        return data[top--];
    }

    int peek() //�������� �ʰ� ��� ��ȯ
    {
        if (isEmpty()) { error("���� ���� ����"); }
        return data[top];
    }

    void display()
    {
        printf("[���� �׸��� �� = %2d] ==> ", top + 1);
        for (int i = 0; i <= top; i++)
        {
            printf("<%2d>", data[i]);
        }
        printf("\n");
    }
};


bool checkMatching(const char* filename)
{
    int fp = strlen(filename);

    if (fp == 0)
    {
        error("Error: ���� �������� �ʽ��ϴ�.\n");
    }

    int nLine = 0;
    int nChar = 0;

    ArrayStack stack;
    char ch;
    bool s_q = false; //��������ǥ
    //bool b_q = false; //ū����ǥ

    for (int i = 0; i < fp; i++)
    {
        ch = filename[i];

        if (ch == '\n')
        {
            nLine++;
        }

        if (ch == '\'' && s_q == false)
        {
            s_q = true;
            stack.push(ch);
        }
        else if (ch == '\'')
        {
            s_q = false;
            stack.pop();
            if (ch != '\'')
            {
                break;
            }
            nChar++;
        }
    }


    if (!stack.isEmpty())
    {
        printf("Error, Line_count : %d, quotes_count : %d\n\n", nLine, nChar);
    }
    else
    {
        printf("OK, Line_count : %d, quotes_count : %d\n\n", nLine, nChar);
    }
    return stack.isEmpty();
}

int main() {
    std::string Str, temp;
    while (true) {
        std::getline(std::cin, temp);
        if (temp == "EOF")break;
        Str.append(temp);
        Str.append("\n");
        std::cin.clear();
    }
    checkMatching(Str.data());
    return 0;
}