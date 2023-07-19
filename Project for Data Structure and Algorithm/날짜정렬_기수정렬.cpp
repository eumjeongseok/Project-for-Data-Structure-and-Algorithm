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
    vector<int> temp(n); //�ӽ� �迭(����) ����
    int m = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > m) {
            m = arr[i];
        }
    } //�Ϸù�ȣ �� ���� ū �� -> ���� ū �ڸ���

    for (int exp = 1; m / exp > 0; exp *= 10) {
        //�ڸ����� ����Ű�� �迭(ī��Ʈ �迭)
        //0, 1, 2, 3, 4, 5, 6, 7, 8, 9
        vector<int> bucket(10, 0);

        for (int i = 0; i < n; i++) {
            bucket[(arr[i] / exp) % 10]++; //�ڸ������� ī��Ʈ �迭�� �ֱ�
        }

        for (int i = 1; i < 10; i++) {
            bucket[i] += bucket[i - 1]; //ī���� �迭�� ���������� �б�
        }

        for (int i = n - 1; i >= 0; i--) {
            temp[bucket[(arr[i] / exp) % 10] - 1] = arr[i];
            bucket[(arr[i] / exp) % 10]--;
            //ī���� �迭�� ����� �迭 ���� �ְ�, ī���� �迭�� �ٽ� ����
        }

        for (int i = 0; i < n; i++) {
            arr[i] = temp[i]; //���ĵ� ���� �ٽ� ����
        }
    }
}

// day, month, year�� �ϳ��� �Ϸù�ȣ�� �����
//��)8 11 2014 ->20140000 + 1100 + 8 = 20141108
int convert_date(int day, int month, int year) {
    return (year * 10000) + (month * 100) + day;
}

int main()
{
    int n;
    cin >> n;
    vector<int> dates(n); //�ڵ����� �޸� �Ҵ�
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
