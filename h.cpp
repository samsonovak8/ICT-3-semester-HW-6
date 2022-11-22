#include<algorithm>
#include<iostream>
#include<vector>

std::vector<std::vector<int> > g(20005);
std::vector<bool> used(20005, 0);
std::vector<int> tin(20005), up(20005);
std::vector<int> cutpoint(20005, 0);
int timer = 0;

void dfs(int v, int pred = -1) {
    used[v] = 1;
    tin[v]  = timer;
    up[v]   = timer++;
    int leaves = 0;
    for(int i : g[v]) {
        if (i != pred) {
            
            if (used[i] == 0) {
                dfs(i, v);
                up[v] = std::min(up[i], up[v]);
                if (up[i] >= tin[v] && pred != -1) {
                    cutpoint[v] = 1;
                }
                ++leaves;
            }
            else {
                up[v] = std::min(up[v], tin[i]);
            }
        }
    }
    if (pred == -1 && leaves > 1) {
        cutpoint[v] = 1;
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

    for(size_t i = 0; i < n; ++i) {

        if (!used[i]) {

            dfs(i);
        }
    }

    int k = 0;
    for(size_t i = 0; i < n; ++i) {
        k += cutpoint[i];
    }

    std::cout << k << '\n';

    for(size_t i = 0; i < n; ++i) {
        if (cutpoint[i]) {
            std::cout << i + 1 << " ";
        }
    }

    return 0;
}