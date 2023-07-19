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

    int tmp = (int)mat[0].size(); //형 변환

    if (i < 0 || j >= tmp) {
        return INT_MAX;
        //행렬 바깥에 있음. 이 경우는 확인 불가하므로 초기값으로 설정
        //즉, 경계 밖을 따로 인식하기 위한 것
    }
    if (i == 0 && j == tmp - 1) {
        return mat[i][j]; //처음 위치
    }
    if (memo[i][j] != 0) {
        return memo[i][j]; //Memoize가 되지 않은 값을 -1로 설정
    }
    else {
        memo[i][j] = mat[i][j] + min(matrix_path_minimum(mat, i - 1, j, memo),
            min(matrix_path_minimum(mat, i, j + 1, memo), matrix_path_minimum(mat, i - 1, j + 1, memo)));

        //이 부분이 Memoize의 과정, 이 부분이 없으면 Momization이 동작하지 않음
        return memo[i][j];
        //최소 비용도 메모지에 적었을 테니 그것을 제출하자!
    }

}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    //속도 증가

    int n; //행렬의 크기
    cin >> n;

    vector<vector<int>> mat(n, vector<int>(n)); //행렬 생성
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }

    vector<vector<int>> memo(mat.size(), vector<int>(mat[0].size(), 0));
    //행렬을 Memoize하는 벡터(배열), 각 칸의 값을 -1로 초기화

    cout << matrix_path_minimum(mat, mat.size() - 1, 0, memo) << "\n";
    return 0;
}
