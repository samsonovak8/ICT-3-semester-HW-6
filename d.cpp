#include<iostream>
#include<vector>

std::vector<std::vector<int> > g(20000);
std::vector<int> color(20000, 0);
std::vector<bool> used(20000, 0);


void dfs(int v, int cnt) {

    color[v] = cnt;
    used[v]  = 1;

    for(size_t i = 0; i < g[v].size(); ++i) {

        if (!used[g[v][i]]) {

            dfs(g[v][i], cnt);
        }
    }
}

int main() {

    int n, m;
    std::cin >> n >> m;

    for(size_t i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        --x; --y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    int cnt = 1;
    for(size_t i = 0; i < n; ++i) {
        if(!used[i]) {
            
            dfs(i, cnt++);
        }
    }

    std::cout << cnt - 1 << "\n";

    for(size_t i = 0; i < n; ++i) {
        std::cout << color[i] << " ";
    }

    return 0;
}