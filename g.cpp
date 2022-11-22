#include<iostream>
#include<vector>

std::vector<std::vector<int> > g(26);
std::vector<int> used(26, 0);
std::vector<int> topSort;

void dfs(int v) {
    used[v] = 1;
    for(int i:g[v]) {
        if (!used[i]) {
            dfs(i);
        }
    }
    topSort.push_back(v);
}

int main() {

    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> s(m);
    for(size_t i = 0; i < m; ++i) {
        std::cin >> s[i];
    }

    for(size_t i = 0; i < m - 1; ++i) {
        size_t len1 = s[i].size();
        size_t len2 = s[i + 1].size(); 
        for(size_t j = 0; j < std::min(len1, len2); ++j) {
            if (s[i][j] != s[i + 1][j]) {
                int u = s[i][j] - 'A';
                int v = s[i + 1][j] - 'A';
                g[u].push_back(v);
                break;
            }
        }
    }


    for(size_t i = 0; i < n; ++i) {
        if(!used[i]) {
            dfs(i);
        }
    }
    std::string a = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i = topSort.size() - 1; i >= 0; --i) {
        std::cout << a[topSort[i]];
    }
    return 0;
}