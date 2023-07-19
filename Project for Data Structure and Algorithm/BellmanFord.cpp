//�ִ��� �ǻ��ڵ�� ������ ����, ���� ���� �߰�

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <deque>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define MAX 1000
#define INF 987654321
//INF�� ���� ���Ѵ���̳�, ���⼭�� ����� ū ���� ��ü
//��? ���Ѵ���� C++�� ���� �Ұ��ϹǷ�...

int V, E; //���� ����, ���� ����
int u, v, w; //���� ���, �� ���, ����ġ
int r; //��� ���
long long c[MAX]; //��� ��忡�� �� ���(index)������ �Ÿ�
bool cycle;
vector<pair<int, int>> G[MAX];
//(int, int) �� ����: struct�� ���� �����ϳ� �׷��⿣ �ڵ尡 ����������...

void bellman_ford(vector<pair<int, int>> G[], int r) {
	//�ʱ�ȭ �ܰ�
	for (int i = 1; i <= V; i++) {
		c[i] = INF; // ��� ��带 INF�� ����
	}
	c[r] = 0; // ������ 0���� �ʱ�ȭ

	//Bellman-Ford �˰���
	for (int i = 1; i <= V; i++) { //����Ŭ �˻�
		for (int j = 1; j <= V; j++) { //��� ���� �湮
			for (int k = 0; k < G[j].size(); k++) { //��� ����Ʈ ���� �湮

				//���� Struct�� �����ϸ� ���� ��嵵 �����ؾ� �ϳ�
				//vector���� ���� ����Ʈ �÷� ����
				//���� ���� ���� ��带 ���� �ʿ� ����
				int next = G[j][k].first; //pair�� ���� int(�� ���)
				int d = G[j][k].second; //pair�� ���� int(����ġ)

				if (c[j] == INF) { continue; }
				if (c[j] != INF && c[next] > c[j] + d) {
					c[next] = c[j] + d; // *Relaxation(�̿�)
					if (i == V) { cycle = true; }
				}
			}
		}
	}

	if (cycle == true) { cout << -1 << "\n"; }
	// ���� ����Ŭ�� ������ -1 ���(��Ȳ�� ���� -1 ��� ���� ��� ����)
	else {
		for (int i = 1; i <= V; i++) {
			cout << (c[i] != INF ? c[i] : -1) << "\n";
			// ������(1)���� �ִ� �Ÿ� ���, �� �� ���� ��� -1 ���
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	//���� �ӵ� ����

	//�Է�
	cin >> V >> E;
	for (int i = 0; i < E; i++){
		cin >> u >> v >> w;
		G[u].push_back({ v,w });
		//���� A���� �� ��� B�� �׿� ���� ����ġ C�� ����
		//�̸��� �� A�� ���� ���� ����Ʈ ���·� �׷����� ǥ���ߴٴ� ��
	}
	cin >> r;

	//�˰��� ���� �� ���
	bellman_ford(G, r);

	return 0;
}