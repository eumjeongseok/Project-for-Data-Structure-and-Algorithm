#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// 함수 get_prefix: 문자열의 접두사를 반환합니다.
string get_prefix(string str, int len) {
    return str.substr(0, len); //substr(a, b): a부터 b까지의 부분 문자열 반환
}

// 함수 get_suffix: 문자열의 접미사를 반환합니다.
string get_suffix(string str, int len) {
    return str.substr(str.length() - len, len);
}

// 함수 get_next_state: 다음 상태를 반환합니다.
int get_next_state(string P, int s, char x) {
    int m = P.length();
    if (s < m && P[s] == x) { //P의 index는 0부터 시작
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

// 함수 construct_automata: Automata 테이블을 구축합니다.
vector<vector<int>> construct_automata(string P) {
    int m = P.length();
    unordered_set<char> Sigma; //해싱을 이용한 Σ집합(버켓)
    for (char c : P) {
        Sigma.insert(c); //P에 있는 모든 단위 문자들을 Sigma에 입력
    }
    vector<vector<int>> T(m + 1, vector<int>(256, 0));
    //256개의 열? => ASCII 문자 집합의 포괄을 위함.
    for (int s = 0; s <= m; s++) {
        for (char x : Sigma){ //모든 상태와 라벨에 대하여 다음 상태 결정
            T[s][x] = get_next_state(P, s, x);
        }
    }
    return T;
}

// 함수 automata_search: 주어진 텍스트에서 패턴을 검색합니다.
void automata_search(string A, vector<vector<int>> T, string P) {
    int n = A.length();
    int m = P.length();
    int s = 0; // 상태

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