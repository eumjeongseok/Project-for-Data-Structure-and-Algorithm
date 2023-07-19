#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// �Լ� get_prefix: ���ڿ��� ���λ縦 ��ȯ�մϴ�.
string get_prefix(string str, int len) {
    return str.substr(0, len); //substr(a, b): a���� b������ �κ� ���ڿ� ��ȯ
}

// �Լ� get_suffix: ���ڿ��� ���̻縦 ��ȯ�մϴ�.
string get_suffix(string str, int len) {
    return str.substr(str.length() - len, len);
}

// �Լ� get_next_state: ���� ���¸� ��ȯ�մϴ�.
int get_next_state(string P, int s, char x) {
    int m = P.length();
    if (s < m && P[s] == x) { //P�� index�� 0���� ����
        return s + 1;
    } else {
        string X = P.substr(0, s) + x;
        for (int len = s; len >= 1; len--) {
            string p_prime = get_prefix(X, len);
            string s_prime = get_suffix(X, len);
            if (p_prime == s_prime) {
                return len;
            }
        }
    }
    return 0;
}

// �Լ� construct_automata: Automata ���̺��� �����մϴ�.
vector<vector<int>> construct_automata(string P) {
    int m = P.length();
    unordered_set<char> Sigma; //�ؽ��� �̿��� ������(����)
    for (char c : P) {
        Sigma.insert(c); //P�� �ִ� ��� ���� ���ڵ��� Sigma�� �Է�
    }
    vector<vector<int>> T(m + 1, vector<int>(256, 0));
    //256���� ��? => ASCII ���� ������ ������ ����.
    for (int s = 0; s <= m; s++) {
        for (char x : Sigma){ //��� ���¿� �󺧿� ���Ͽ� ���� ���� ����
            T[s][x] = get_next_state(P, s, x);
        }
    }
    return T;
}

// �Լ� automata_search: �־��� �ؽ�Ʈ���� ������ �˻��մϴ�.
void automata_search(string A, vector<vector<int>> T, string P) {
    int n = A.length();
    int m = P.length();
    int s = 0; // ����

    for (int i = 0; i < n; i++) {
        char c = A[i];
        if (T[s][c] == m) {
            cout << "There is a matching at A[" << i - m + 1 << "]" << endl;
        }
        s = T[s][c];
    }
}

int main() {
    string A = "tcabcdabcdabcwz";
    string P = "abcdabcwz";

    vector<vector<int>> T = construct_automata(P);
    automata_search(A, T, P);

    return 0;
}