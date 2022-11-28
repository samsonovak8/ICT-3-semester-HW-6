#include<iostream>
#include<vector>
#include<set>

std::vector<std::vector<int> > g(20005), g_inv(20005);
std::vector<int> used(20005, 0);
std::vector<int> color(20005, -1);
std::vector<int> order;

void dfs1(int v) {
    used[v] = 1;
    for(int i : g[v]) {
        if (!used[i]) {
            dfs1(i);
        }
    }
    order.push_back(v);
}

void dfs2(int v, int color_) {
    color[v] = color_;
    for(int i : g_inv[v]) {
        if (color[i] == -1) {
            dfs2(i, color_);
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
        g_inv[y].push_back(x);
    }

    for(size_t i = 0; i < n; ++i) {
        if(!used[i]) {
            dfs1(i);
        }
    }

    size_t color_ = 0;
    for(int i = order.size() - 1; i >= 0; --i) {
        if (color[order[i]] == -1) {
            dfs2(order[i], color_++);
        }
    }

    std::set<std::pair<int, int> > edge;
    for(int i = 0; i < n; ++i) {
        for(size_t j = 0; j < g[i].size(); ++j) {
            if (color[i] != color[g[i][j]]) {
                edge.insert({std::min(color[i], color[g[i][j]]), std::max(color[i], color[g[i][j]])});
            }
        }
    }
    std::cout << edge.size() << '\n';
    return 0;
}