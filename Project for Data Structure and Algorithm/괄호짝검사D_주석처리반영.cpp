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


//오류 처리 함수
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


bool checkMatching(const char* filename)
{
    int fp = strlen(filename);

    if (fp == 0)
    {
        error("Error: 파일 존재하지 않습니다.\n");
    }

    int nLine = 0;
    int nChar = 0;


    ArrayStack stack;
    char ch;
    bool b_q = false;
    bool com_pre = false; //주석 준비
    bool com = false; //한줄주석
    bool com_star = false; //* 주석
    bool ex_com_star_pre = false; //* 주석 해제준비

    for (int i = 0; i < fp; i++)
    {
        ch = filename[i];

        //주석 체크
        if (com_pre == false && ch == '/' && b_q == false)
        {
            com_pre = true;
        }
        if (com_star == true && ch == '*')
        {
            ex_com_star_pre = true;
        }

        //주석인지 일반 문자인지 확인
        if (com_pre == true && ch == '/')
        {
            com = true;
        }
        else if (com_pre == true && ch == '*')
        {
            com_star = true;
        }
        else
        {
            com_pre = false;
        }

        //*별 주석 해제인지 일반 문자였는지 확인
        if (ex_com_star_pre == true && ch == '/')
        {
            com_star = false;
        }
        else
        {
            ex_com_star_pre = false;
        }


        if (ch == '\n')
        {
            if (b_q == true)
            {
                nLine++;
            }
            nLine++;
            com = false;
        }

        if (ch == '\"' && b_q == false)
        {
            b_q = true;
        }
        else if (ch == '\"')
        {
            b_q = false;
        }

        if (ch == '[' || ch == '(' || ch == '{')
        {
            if (b_q == false && com == false && com_star == false)
            {
                stack.push(ch);
            }
        }
        else if (ch == ']' || ch == ')' || ch == '}')
        {
            if (b_q == false && com == false && com_star == false)
            {
                char prev = stack.pop();
                if ((ch == ']' && prev != '[') || (ch == ')' && prev != '(') || (ch == '}' && prev != '{'))
                {
                    stack.push(ch);
                    break;
                }
                nChar++;
            }
        }
    }


    if (!stack.isEmpty())
    {
        printf("Error, Line_count : %d, bracket_count : %d\n\n", nLine, nChar);
    }
    else
    {
        printf("OK, Line_count : %d, bracket_count : %d\n\n", nLine, nChar);
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