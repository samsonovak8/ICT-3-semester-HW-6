#include<iostream>
#include<vector>
#include<set>

std::vector<std::vector<int> > g(20005);
std::vector<int> used(20005, 0);
std::vector<int> tin(20005), up(20005);
std::set<std::pair<int, int> > bridge;

int timer = 0;

void dfs(int v, int pred) {

    used[v] = 1;
    tin[v]  = timer;
    up[v]   = timer++;

    for(int i : g[v]) {
        if (i != pred) {
            if(!used[i]) {
                dfs(i, v);
                up[v] = std::min(up[v], up[i]);
                if (up[i] > tin[v]) {
                    bridge.insert({std::min(i, v), std::max(i, v)});
                }

            }
            else {
                up[v] = std::min(up[v], tin[i]);
            }
        }
    }
}


int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int> > edge;

    for(size_t i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        --x; --y;
        g[x].push_back(y);
        g[y].push_back(x);
        edge.push_back({std::min(x, y), std::max(x, y)});
    }

    for(size_t i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i, -1);
        }
    }

    int k = 0;
    for(size_t i = 0; i < m; ++i) {
        int x = edge[i].first;
        int y = edge[i].second;
        if (bridge.find({x, y}) != bridge.end()) {
            ++k;
        }
    }

    std::cout << k << '\n';

    for(size_t i = 0; i < m; ++i) {
        int x = edge[i].first;
        int y = edge[i].second;
        if (bridge.find({x, y}) != bridge.end()) {
            std::cout << i + 1 << '\n';
        }
    }
    return 0;
}