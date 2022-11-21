#include<iostream>
#include<vector>

std::vector<std::vector<int> > g(20000);
std::vector<int> used(20000, 0);

void dfs(int v, int color, bool& ok) {
    used[v] = color;

    for(int i : g[v]) {

        if (used[i] == 0) {
            dfs(i, color == 1 ? 2:1, ok);
        }
        else if (used[i] == color) {
            ok = 0;
            return;
        }
    }
}

int main() {

    int n, m;
    std::cin >> n >> m;

    for(size_t i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    bool ok = 1;

    for(size_t i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i, 1, ok);
        }
    }

    if (ok) {
        std::cout << "YES\n";
    }
    else {
        std::cout << "NO\n";
    }
    return 0;
}