//최대한 의사코드와 가깝게 변경, 빠진 내용 추가

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
//INF는 원래 무한대수이나, 여기서는 충분히 큰 수로 대체
//왜? 무한대수는 C++로 구현 불가하므로...

int V, E; //정점 개수, 간선 개수
int u, v, w; //시작 노드, 끝 노드, 가중치
int r; //출발 노드
long long c[MAX]; //출발 노드에서 각 노드(index)까지의 거리
bool cycle;
vector<pair<int, int>> G[MAX];
//(int, int) 형 벡터: struct로 구현 가능하나 그러기엔 코드가 복잡해진다...

void bellman_ford(vector<pair<int, int>> G[], int r) {
	//초기화 단계
	for (int i = 1; i <= V; i++) {
		c[i] = INF; // 모든 노드를 INF로 세팅
	}
	c[r] = 0; // 시작점 0으로 초기화

	//Bellman-Ford 알고리즘
	for (int i = 1; i <= V; i++) { //사이클 검사
		for (int j = 1; j <= V; j++) { //모든 정점 방문
			for (int k = 0; k < G[j].size(); k++) { //모든 리스트 내용 방문

				//만약 Struct로 저장하면 시작 노드도 복사해야 하나
				//vector형은 인접 리스트 꼴로 저장
				//따라서 굳이 시작 노드를 만들 필요 없음
				int next = G[j][k].first; //pair의 전자 int(끝 노드)
				int d = G[j][k].second; //pair의 후자 int(가중치)

				if (c[j] == INF) { continue; }
				if (c[j] != INF && c[next] > c[j] + d) {
					c[next] = c[j] + d; // *Relaxation(이완)
					if (i == V) { cycle = true; }
				}
			}
		}
	}

	if (cycle == true) { cout << -1 << "\n"; }
	// 음수 사이클이 있으면 -1 출력(상황에 따라 -1 대신 문자 출력 가능)
	else {
		for (int i = 1; i <= V; i++) {
			cout << (c[i] != INF ? c[i] : -1) << "\n";
			// 시작점(1)과의 최단 거리 출력, 갈 수 없는 경우 -1 출력
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	//실행 속도 증가

	//입력
	cin >> V >> E;
	for (int i = 0; i < E; i++){
		cin >> u >> v >> w;
		G[u].push_back({ v,w });
		//정점 A에는 끝 노드 B와 그에 대한 가중치 C가 존재
		//이말은 곧 A에 대한 연결 리스트 형태로 그래프를 표현했다는 뜻
	}
	cin >> r;

	//알고리즘 실행 및 출력
	bellman_ford(G, r);

	return 0;
}