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

    //입력
    string input;
    getline(std::cin, input);

    //문자열 파싱
    stringstream ss(input);

    //원형 덱(밑빠진 스택) 객체 생성
    deque<char> circularDeque;
    deque<char> undoStack;
    deque<char> redoStack;
    deque<char> circularDequeCopy;
    deque<char> redoStackCopy;

    //파싱한 문자를 담을 변수
    char c;

    //파싱한 문자를 인식하는 조건
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

    //출력
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
