#include<iostream>
#include<vector>
#include<string>
#include<queue>

std::vector<std::vector<bool> > used(2005, std::vector<bool>(2005, 0));
std::vector<std::string> s(2005);

void dfs(int x, int y, size_t n, size_t m) {

    std::queue<int> q;
    q.push(x);
    q.push(y);
    used[x][y] = 1;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        int v = q.front();
        q.pop();
        if (u && !used[u - 1][v] && s[u - 1][v] == '+') {
            q.push(u - 1);
            q.push(v);
            used[u - 1][v] = 1;
        }
        if(v && !used[u][v - 1] && s[u][v - 1] == '+') {
            q.push(u);
            q.push(v - 1);
            used[u][v - 1] = 1;
        }
        if (u + 1 < n && !used[u + 1][v] && s[u + 1][v] == '+') {
            q.push(u + 1);
            q.push(v);
            used[u + 1][v] = 1;
        }
        if (v + 1 < m && !used[u][v + 1] && s[u][v + 1] == '+') {
            q.push(u);
            q.push(v + 1);
            used[u][v + 1] = 1;
        }
    }
    return;
}

int main() {

    size_t n, m;
    std::cin >> n >> m;

    for(size_t i = 0; i < n; ++i) {
        std::cin >> s[i];
    }

    int cnt = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if (s[i][j] == '+' && !used[i][j]) {
                ++cnt;
                dfs(i, j, n, m);
            }
        }
    }   

    std::cout << cnt << "\n";

    return 0;
}