#include<iostream>
#include<vector>

std::vector<std::vector<int> > g(100500);
std::vector<int> used(100500, 0);
std::vector<int> pred(100500, 0);

int cycle_start;
int cycle_end;

bool dfs(int v) {

    used[v] = 1;

    for(int i : g[v]) {

        if (used[i] == 0) {
            
            pred[i] = v;
            if (dfs(i)) {
                return 1;
            }
        }
        else if(used[i] == 1) {
            cycle_start = i;
            cycle_end = v;
            return 1;
        }
    }
    
    used[v] = 2;
    return 0;
}

int main() {

    int n, m;
    std::cin >> n >> m;

    for(size_t i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        --x; --y;
        g[x].push_back(y);
    }

    bool flag = 0;

    for(size_t i = 0; i < n && !flag; ++i) {

        if (!used[i]) {

           flag = dfs(i); 
        }
    }

    if (flag) {
        std::cout << "YES\n";

        std::vector<int> cycle;
        cycle.push_back(cycle_start);
        int v = cycle_end;
        while(v != cycle_start) {
            cycle.push_back(v);
            v = pred[v];
        }

        for(int i = cycle.size() - 1; i >= 0; --i) {
            std::cout << cycle[i] + 1 << " ";
        }
    }
    else {
        std::cout << "NO";
    }

    return 0;
}