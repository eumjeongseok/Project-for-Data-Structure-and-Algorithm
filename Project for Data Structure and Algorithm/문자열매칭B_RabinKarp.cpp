#include <iostream>
#include <string>
using namespace std;

int d = 10; // ������

void RK_search(string A, string P, int q) {
    int p = 0; // ������ �ؽð�
    int a1 = 0; // �ؽ�Ʈ�� �ؽð�

    int m = P.length(); // ������ ����
    int n = A.length(); // �ؽ�Ʈ�� ����

    // ���ϰ� ù ��° �κ� ���ڿ��� �ؽð� ���
    for (int i = 0; i < m; i++) {
        p = (P[i] + d * p) % q;
        a1 = (A[i] + d * a1) % q;
    }

    // ���ϰ� �κ� ���ڿ� ��
    for (int i = 0; i <= n - m; i++) {
        if (i > 0) {
            // ���� �κ� ���ڿ��� �ؽð� ���
            a1 = (d * (a1 - ((int)pow(d, m - 1) % q) * A[i - 1]) + A[i + m - 1]) % q;
            if (a1 < 0) {
                a1 += q; // ������ ��� ����� ��ȯ
                //*����: https://developer-mac.tistory.com/84
            }
        }

        // ���ϰ� �κ� ���ڿ��� ��ġ�ϴ��� Ȯ��
        if (p == a1) {
            bool match = true; //p==a ���� Ȯ��
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