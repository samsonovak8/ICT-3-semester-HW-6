#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<algorithm>
#include<queue>

int bfs(int n, std::string start, std::string end) {
    std::queue<std::string> q1;
    std::queue<std::string> q2;
    std::unordered_set<std::string> used1;
    std::unordered_set<std::string> used2;

    q1.push(start);
    q2.push(end);

    used1.insert(start);
    used2.insert(end);

    int timer = 0;


    while(true) {
        if (q1.size() > q2.size()) {
            std::swap(q1, q2);
            std::swap(used1, used2);
        }
        size_t size = q1.size();
        for(size_t i = 0; i < size; ++i) {
            std::string v1 = q1.front();
            q1.pop();
            for(size_t left = 0; left < n - 1; ++left) {
                for(size_t right = left + 1; right < n; ++right) {
                    std::string v2 = v1;
                    std::reverse(v2.begin() + left, v2.begin() + right + 1);
                    if (used1.find(v2) != used1.end()) {
                        continue;
                    }
                    if (used2.find(v2) != used2.end()) {
                        return timer + 1;
                    }
                    q1.push(v2);
                    used1.insert(v2);
                }
            }
        }
        ++timer;
    }
    return 0;
}

int main() {
    int n;
    std::cin >> n;
    std::string start(n, ' '), end(n, ' ');
    for(size_t i = 0; i < n; ++i) {
        int x;
        std::cin>>x;
        start[i] = '0' + x - 1;
    }
    for(size_t i = 0; i < n; ++i) {
        int x;
        std::cin>>x;
        end[i] = '0' + x - 1;
    }
    bool flag = 1;
    for(size_t i = 0; i < n && flag; ++i) {
        if (start[i] != end[i]) {
            flag = 0;
        }
    }
    if (flag) {
        std::cout<<"0";
    }
    else {
        std::cout<<bfs(n, start, end);
    }
    return 0;
}