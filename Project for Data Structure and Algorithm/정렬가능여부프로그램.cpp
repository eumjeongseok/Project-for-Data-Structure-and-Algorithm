#include <iostream>
#include <stack>
#include <queue>
using namespace std;

int main() {
    int n;
    char order;
    cin >> n >> order;

    queue<int> input_queue;
    queue<int> output_queue;
    stack<int> stack;

    // �Է� ť �ʱ�ȭ
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        input_queue.push(num);
    }

    // ������ �̿��� ��� ť�� ����
    while (!input_queue.empty()) {
        int num = input_queue.front();
        input_queue.pop();
        if (stack.empty()) {
            stack.push(num);
        }
        else {
            if (order == 'a') {
                while (!stack.empty() && stack.top() < num) {  // ������ �κ�
                    int temp = stack.top();
                    stack.pop();
                    output_queue.push(temp);
                }
            }
            else { // order == 'd'
                while (!stack.empty() && stack.top() > num) {  // ������ �κ�
                    int temp = stack.top();
                    stack.pop();
                    output_queue.push(temp);
                }
            }
            stack.push(num);
        }
    }
    while (!stack.empty()) {
        int temp = stack.top();
        stack.pop();
        output_queue.push(temp);
    }

    // ��� ť�� ���ĵ� ���ڵ��� ���� �������� Ȯ��
    bool is_possible = true;
    int prev_num = output_queue.front();
    output_queue.pop();
    while (!output_queue.empty()) {
        int num = output_queue.front();
        output_queue.pop();
        if (order == 'a') {
            if (prev_num > num) {
                is_possible = false;
                break;
            }
        }
        else { // order == 'd'
            if (prev_num < num) {
                is_possible = false;
                break;
            }
        }
        prev_num = num;
    }

    // ��� ���
    if (is_possible) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }

    return 0;
}
