#include <iostream>
#include <string>
#include <sstream>
#include <deque>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main() {

    //�Է�
    string input;
    getline(std::cin, input);

    //���ڿ� �Ľ�
    stringstream ss(input);

    //���� ��(�غ��� ����) ��ü ����
    deque<char> circularDeque;
    deque<char> undoStack;
    deque<char> redoStack;
    deque<char> circularDequeCopy;
    deque<char> redoStackCopy;

    //�Ľ��� ���ڸ� ���� ����
    char c;

    //�Ľ��� ���ڸ� �ν��ϴ� ����
    while (ss >> c) {
        if (c == 'U') {
            if (undoStack.empty()) {
                cout << "ERROR" << endl;
                return 0;
            }
            if (!undoStack.empty()) {
                char undoChar = circularDeque.back();
                undoStack.pop_back();
                redoStack.push_back(undoChar);
                circularDeque.pop_back();
            }
        }
        else if (c == 'R') {
            if (redoStack.empty()) {
                cout << "ERROR" << endl;
                return 0;
            }
            if (!redoStack.empty()) {
                char redoChar = redoStack.back();
                redoStack.pop_back();
                undoStack.push_back(redoChar);
                circularDeque.push_back(redoChar);
            }
        }
        else {
            if (circularDeque.size() == 10) {
                circularDeque.pop_front();
            }
            if (redoStack.size() == 10) {
                redoStack.pop_front();
            }
            circularDeque.push_back(c);
            undoStack.push_back(c);
            redoStack.clear();
        }
    }

    //���
    circularDequeCopy = circularDeque;
    redoStackCopy = redoStack;
    while (!circularDeque.empty() || !redoStack.empty()) {
        while (!circularDequeCopy.empty()) {
            cout << circularDequeCopy.back() << ' ';
            circularDequeCopy.pop_back();
        }

        if (!circularDeque.empty()) {
            std::cout << '\n';
        }
        break;
    }

    if (circularDeque.empty()) {
        cout << "EMPTY" << endl;
    }

    while (!redoStackCopy.empty()) {
        cout << redoStackCopy.back() << ' ';
        redoStackCopy.pop_back();
    }

    if (redoStack.empty()) {
        cout << "EMPTY" << endl;
    }


    return 0;
}
