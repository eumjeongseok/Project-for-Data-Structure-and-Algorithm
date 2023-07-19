#include <climits>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

int matrix_path_minimum(vector<vector<int>>& mat, int i, int j, vector<vector<int>>& memo) {

    int tmp = (int)mat[0].size(); //�� ��ȯ

    if (i < 0 || j >= tmp) {
        return INT_MAX;
        //��� �ٱ��� ����. �� ���� Ȯ�� �Ұ��ϹǷ� �ʱⰪ���� ����
        //��, ��� ���� ���� �ν��ϱ� ���� ��
    }
    if (i == 0 && j == tmp - 1) {
        return mat[i][j]; //ó�� ��ġ
    }
    if (memo[i][j] != 0) {
        return memo[i][j]; //Memoize�� ���� ���� ���� -1�� ����
    }
    else {
        memo[i][j] = mat[i][j] + min(matrix_path_minimum(mat, i - 1, j, memo),
            min(matrix_path_minimum(mat, i, j + 1, memo), matrix_path_minimum(mat, i - 1, j + 1, memo)));

        //�� �κ��� Memoize�� ����, �� �κ��� ������ Momization�� �������� ����
        return memo[i][j];
        //�ּ� ��뵵 �޸����� ������ �״� �װ��� ��������!
    }

}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    //�ӵ� ����

    int n; //����� ũ��
    cin >> n;

    vector<vector<int>> mat(n, vector<int>(n)); //��� ����
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }

    vector<vector<int>> memo(mat.size(), vector<int>(mat[0].size(), 0));
    //����� Memoize�ϴ� ����(�迭), �� ĭ�� ���� -1�� �ʱ�ȭ

    cout << matrix_path_minimum(mat, mat.size() - 1, 0, memo) << "\n";
    return 0;
}
