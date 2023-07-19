#include <iostream>
#include <string>
using namespace std;

void SAN_search(string A, string P) {
    int p = 0; // number of P
    int a1 = 0; // number of sub-string of A at index 1(in C++, index 0)

    int m = P.length();
    int n = A.length();

    for (int i = 0; i < m; i++) {
        p = P[i] - '0' + 10 * p;
        a1 = A[i] - '0' + 10 * a1;
    }

    for (int i = 0; i < n - m + 1; i++) {
        if (i > 0) {
            a1 = 10 * (a1 - (A[i - 1] - '0') * int(pow(10, m - 1))) + (A[i + m - 1] - '0');
            //pow(a, n): a^n
            //A[i - 1] - '0': 문자의 ASCII 값을 제하여 정수값을 얻는 방식
        }

        if (p == a1) {
            cout << "There is a matching at A[" << i << "]" << "\n";
        }
    }
}

int main() {
    // Test case
    string A = "1234567890";
    string P = "456";

    SAN_search(A, P);

    return 0;
}