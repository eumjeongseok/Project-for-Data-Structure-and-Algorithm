#include <iostream>
#include <string>
using namespace std;

int d = 10; // 십진수

void RK_search(string A, string P, int q) {
    int p = 0; // 패턴의 해시값
    int a1 = 0; // 텍스트의 해시값

    int m = P.length(); // 패턴의 길이
    int n = A.length(); // 텍스트의 길이

    // 패턴과 첫 번째 부분 문자열의 해시값 계산
    for (int i = 0; i < m; i++) {
        p = (P[i] + d * p) % q;
        a1 = (A[i] + d * a1) % q;
    }

    // 패턴과 부분 문자열 비교
    for (int i = 0; i <= n - m; i++) {
        if (i > 0) {
            // 다음 부분 문자열의 해시값 계산
            a1 = (d * (a1 - ((int)pow(d, m - 1) % q) * A[i - 1]) + A[i + m - 1]) % q;
            if (a1 < 0) {
                a1 += q; // 음수인 경우 양수로 변환
                //*참고: https://developer-mac.tistory.com/84
            }
        }

        // 패턴과 부분 문자열이 일치하는지 확인
        if (p == a1) {
            bool match = true; //p==a 여부 확인
            for (int j = 0; j < m; j++) {
                if (P[j] != A[i + j]) {
                    match = false;
                    break;
                }
            }

            if (match) {
                cout << "There is a matching at A[" << i << "]" << "\n";
            }
            else {
                cout << "Just fingerprints are matched, not their originals" << "\n";
            }
        }
    }
}

int main() {
    // Test case
    string A = "ABCDABCDABCE";
    string P = "ABC";
    int q = 13;

    RK_search(A, P, q);

    return 0;
}