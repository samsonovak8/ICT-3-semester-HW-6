#include<iostream>
#include<vector>
#include<set>

std::vector<std::set<int> > g(1005);
std::vector<int> EulerPath;

void findEulerPath(int v) {

    while(!g[v].empty()) {
        int u = *g[v].begin();
        g[v].erase(g[v].begin());
        findEulerPath(u);
    }
    EulerPath.push_back(v);
}

int main() {

    size_t n, a;
    std::cin >> n >> a;
    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < n; ++j) {
            int flag;
            std::cin >> flag;
            if (i == j || flag) {
                continue;
            }
            g[i].insert(j);
        }
    }

    --a;

    findEulerPath(a);

    for(size_t i = EulerPath.size() - 1; i > 0; --i) {
        std::cout << EulerPath[i] + 1 << " " << EulerPath[i - 1] + 1 << '\n';
    }

    return 0;
}