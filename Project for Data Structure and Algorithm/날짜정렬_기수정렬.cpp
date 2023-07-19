#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#define MAX_SIZE 500000
using namespace std;

void radix_for_date(vector<int>& arr) {
    int n = arr.size();
    vector<int> temp(n); //임시 배열(벡터) 형성
    int m = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > m) {
            m = arr[i];
        }
    } //일련번호 중 가장 큰 값 -> 가장 큰 자리수

    for (int exp = 1; m / exp > 0; exp *= 10) {
        //자릿수를 가리키는 배열(카운트 배열)
        //0, 1, 2, 3, 4, 5, 6, 7, 8, 9
        vector<int> bucket(10, 0);

        for (int i = 0; i < n; i++) {
            bucket[(arr[i] / exp) % 10]++; //자릿수마다 카운트 배열에 넣기
        }

        for (int i = 1; i < 10; i++) {
            bucket[i] += bucket[i - 1]; //카운터 배열을 오른쪽으로 밀기
        }

        for (int i = n - 1; i >= 0; i--) {
            temp[bucket[(arr[i] / exp) % 10] - 1] = arr[i];
            bucket[(arr[i] / exp) % 10]--;
            //카운터 배열의 기수에 배열 값을 넣고, 카운터 배열을 다시 비우기
        }

        for (int i = 0; i < n; i++) {
            arr[i] = temp[i]; //정렬된 값을 다시 복사
        }
    }
}

// day, month, year를 하나의 일련번호로 만들기
//예)8 11 2014 ->20140000 + 1100 + 8 = 20141108
int convert_date(int day, int month, int year) {
    return (year * 10000) + (month * 100) + day;
}

int main()
{
    int n;
    cin >> n;
    vector<int> dates(n); //자동으로 메모리 할당
    for (int i = 0; i < n; i++) {
        int day, month, year;
        cin >> day >> month >> year;
        dates[i] = convert_date(day, month, year);
    }

    radix_for_date(dates);

    for (int i = 0; i < n; i++) {
        int date = dates[i];
        int year = date / 10000;
        int month = (date / 100) % 100;
        int day = date % 100;
        cout << day << " " << month << " " << year << endl;
    }
    return 0;
}
