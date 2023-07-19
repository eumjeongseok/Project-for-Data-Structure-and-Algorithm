#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 55;

int n, m;
int dist[MAXN][MAXN];
int maze[MAXN][MAXN];
bool visited[MAXN][MAXN];

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

struct Node {
    int x, y;
};

void bfs(int sx, int sy) {
    queue<Node> q;
    Node start = { sx, sy };
    q.push(start);
    visited[sx][sy] = true;
    dist[sx][sy] = 0;

    while (!q.empty()) {
        Node curr = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && maze[nx][ny] == 0 && !visited[nx][ny]) {
                visited[nx][ny] = true;
                dist[nx][ny] = dist[curr.x][curr.y] + 1;
                Node next = { nx, ny };
                q.push(next);
            }
        }
    }
}

int main() {
    cin >> n >> m;
    memset(dist, -1, sizeof(dist));

    int sx, sy, tx, ty;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            if (c == '0') {
                maze[i][j] = 0;
            }
            else if (c == '1') {
                maze[i][j] = 1;
            }
            else if (c == 'S') {
                maze[i][j] = 0;
                sx = i;
                sy = j;
            }
            else if (c == 'T') {
                maze[i][j] = 0;
                tx = i;
                ty = j;
            }
        }
    }

    bfs(sx, sy);

    cout << dist[tx][ty] + 1 << endl;

    return 0;
}
