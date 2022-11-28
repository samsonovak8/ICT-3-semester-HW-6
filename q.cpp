#include<iostream>
#include<vector>
#include <limits.h>

const int INF = UINT32_MAX;

template<typename T>
struct Kunnnnn {
    T n;
    bool* used;
    std::vector<T>* g;
    T* pair;

    Kunnnnn (const T n) : n(n), used(new bool[n]()), g(new std::vector<T>[n]()), pair(new T[n]()) {
        for(T i = 0; i < n; ++i) {
            pair[i] = INF;
        }
    }

    ~Kunnnnn() {
        delete[] used;
        delete[] g;
        delete[] pair;
    }

    bool KunAlgo(const T v) {
        if (used[v]) {
            return 0;
        }
        used[v] = 1;
        for(auto i : g[v]) {
            if (pair[i] == INF || KunAlgo(pair[i])) {
                pair[i] = v;
                pair[v] = i;
                return 1;
            }
        }
        return 0;
    }
    void dfs(const T v) {
        used[v] = 1;
        for(auto& i : g[v]) {
            if(!used[i]) {
                if (pair[v] == INF) {
                    pair[v] = i;
                    pair[i] = v;
                }
                this->dfs(i);
            }
        }
    }
    void fillUsed() {
        for(T i = 0; i < n; ++i) {
            used[i] = 0;
        }
    }


};

int main() {
    size_t n, m;
    std::cin >> n >> m;
    Kunnnnn<size_t> k(n << 1);
    for(size_t i = 0; i < m; ++i) {
        size_t x, y;
        std::cin >> x >> y;
        --x; --y;
        k.g[x].push_back(n + y);
    }
    for(size_t i = 0; i < n; ++i) {
        if (!k.used[i]) {
            k.dfs(i);
        }
    }

    for(size_t i = 0; i < n; ++i) {
        if (k.pair[i] == INF) {
            k.fillUsed();
            k.KunAlgo(i);
        }
    }

    size_t cntIsolatedV = 0;
    for (size_t i = 0; i < (n << 1); ++i) {
        if(k.pair[i] == INF) {
            ++cntIsolatedV;
        }
    }
    std::cout << (cntIsolatedV >> 1) << '\n';
    return 0;
}
