#include <iostream>
#include <vector>
using namespace std;

vector<int> KMP_failure_array(string P) {
    int m = P.length();
    vector<int> pi(m + 5, NULL);
    int j = 0, k = -1;
    pi[0] = -1;

    while (j < m) {
        if (k == -1 || P[j] == P[k]) { //initial case & Match case
            j++;
            k++;
            pi[j] = k;
        }
        else { //Failure case
            k = pi[k];
        }
    }
    return pi;
}

void KMP_search(string A, string P, vector<int>& pi) {
    int n = A.length(); //length of A(document string)
    int m = P.length(); //length of P(pattern string)

    int i = 0; //pointing to A
    int j = 0; //pointing to P

    while (i < n) {
        if (j == -1 || A[i] == P[j]) { //Initial case & Match case
            i++;
            j++;
        }
        else { //Failure case
            j = pi[j];
        }

        if (j == m) { //Final case
            cout << "There is a match at A[" << i - m << "]" << endl;
            j = pi[j - 1];
        }
    }
}

int main() {
    string A = "tacabababacaopt";
    string P = "ababaca";

    vector<int> pi(P.length() + 5, NULL);
    pi = KMP_failure_array(P);

    KMP_search(A, P, pi);

    return 0;
}