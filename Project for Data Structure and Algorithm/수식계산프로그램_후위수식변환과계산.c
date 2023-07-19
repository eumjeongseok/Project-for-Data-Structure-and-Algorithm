#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100

double stack[MAX_SIZE];
int top = -1;

void push(double x) {
    if (top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack[++top] = x;
}

double pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack[top--];
}

int is_empty() {
    return top == -1;
}

int peek() {
    if (!is_empty()) {
        return stack[top];
    }
    else {
        return -1;
    }
}

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    else if (op == '^') {
        return 3;
    }
    else {
        return 0;
    }
}

void check_error(char postfix[])
{
    int len = strlen(postfix);

    // error:  연산자 후 0이 오면 예외처리
    for (int i = 0; i < len; i++)
    {
        if (strstr(postfix, "/0") != NULL || strstr(postfix, "/ 0") != NULL)
        {
            printf("Error : zero division error\n");
            exit(1);
        }
    }
}

void infix_to_postfix(char* infix, char* postfix) {

    // 입력받은 표기식 에러 검사
    check_error(infix);

    int i, j = 0;

    for (i = 0; i < strlen(infix); i++) {

        if (infix[i] == ' ')
        {
            continue;
        }

        // If the scanned character is an operand
        // add it to the postfix expression
        if (isdigit(infix[i]) || isalpha(infix[i])) {

            while (isdigit(infix[i]) || infix[i] == '.') {
                postfix[j++] = infix[i++];
            }
            if (infix[i + 1] == NULL)
            {
                infix[i++] = ' ';
            }
            postfix[j++] = ' ';
            i--;

            // If the scanned character is an opening parenthesis,
            // push it to the stack
        }
        else if (infix[i] == '(') {

            push(infix[i]);

            // If the scanned character is a closing parenthesis,
            // pop and output from the stack until an opening parenthesis is encountered
        }
        else if (infix[i] == ')') {

            while (!is_empty() && peek() != '(') {

                postfix[j++] = pop();
                postfix[j++] = ' ';

            }

            pop();

            // If an operator is scanned
        }
        else {

            while (!is_empty() && precedence(peek()) >= precedence(infix[i])) {

                postfix[j++] = pop();
                postfix[j++] = ' ';

            }

            push(infix[i]);

        }

    }

    while (!is_empty()) {

        postfix[j++] = pop();
        postfix[j++] = ' ';

    }

    postfix[--j] = '\0';

}


double evaluate_postfix(char* postfix) {

    int i;
    double op1, op2;

    for (i = 0; i < strlen(postfix); i++) {

        // If the scanned character is an operand
        // push it to the stack
        if (isdigit(postfix[i])) {

            char num[10];
            int j = 0;

            while (isdigit(postfix[i]) || postfix[i] == '.') {
                num[j++] = postfix[i++];
            }

            num[j] = '\0';
            push(atof(num));

            // If the scanned character is an operator,
            // pop two elements from the stack,
            // perform the operation and push the result back to the stack
        }
        else if (postfix[i] != ' ') {

            op2 = pop();
            op1 = pop();

            switch (postfix[i]) {
            case '+':
                push(op1 + op2);
                break;
            case '-':
                push(op1 - op2);
                break;
            case '*':
                push(op1 * op2);
                break;
            case '/':
                push(op1 / op2);
                break;
            default:
                printf("Invalid operator\n");
            }

        }

    }

    return pop();

}



int main() {

    char infix[MAX_SIZE], postfix[MAX_SIZE];

    fgets(infix, MAX_SIZE, stdin);
    infix[strlen(infix) - 1] = '\0';

    infix_to_postfix(infix, postfix);

    printf("%.2f\n", evaluate_postfix(postfix));

    return 0;

}