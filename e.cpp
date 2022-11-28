#include<iostream>
#include<vector>
#include<string>
#include<queue>

struct Graph {
    std::vector<std::vector<bool> > used = std::vector<std::vector<bool> >(2005, std::vector<bool>(2005, 0));
    std::vector<std::string> s = std::vector<std::string>(2005);

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
};

int main() {

    size_t n, m;
    std::cin >> n >> m;

    Graph graph;

    for(size_t i = 0; i < n; ++i) {
        std::cin >> graph.s[i];
    }

    int cnt = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if (graph.s[i][j] == '+' && !graph.used[i][j]) {
                ++cnt;
                graph.dfs(i, j, n, m);
            }
        }
    }   

    std::cout << cnt << "\n";

    return 0;
}
