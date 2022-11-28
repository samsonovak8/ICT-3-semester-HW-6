#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>
#include <unordered_set>
#include <algorithm>
#include<limits.h>

bool isSolvable(int* matrix) {
    int cnt = 0;
    for(size_t i = 0; i < 8; ++i) {
        for(size_t j = i + 1; j < 9; ++j) {
            if (matrix[i] && matrix[j] && matrix[i] > matrix[j]) {
                ++cnt;
            }
        }
    }
    return cnt % 2 == 0;
}

void checkCondition(std::string s1, std::string s2, std::unordered_map<std::string, int>& dist, std::unordered_map<std::string, bool>& used, std::queue<std::string>& q, int shift, int& ans) {

    if (s1[9] + shift < 10) {

    std::swap(s2[s1[9]], s2[s1[9] + shift]);
    s2[9] += shift;

    if (used.find(s2) == used.end()) {
        q.push(s2);
        int newDist = 0;
        auto it = dist.find(s1);
        if (it != dist.end()) {
            newDist = it->second;
        }
        ++newDist;
        dist.insert({s2, newDist});
        if (s2 == "123456789\b") {
            ans = std::min(ans, newDist);
        }
        used.insert({s2, 1});
    }

    s2[9] -= shift;
    std::swap(s2[s1[9]], s2[s1[9] + shift]);
    }
    return;
}

int bfs(std::string state) {
    std::unordered_map<std::string, int> dist;
    std::unordered_map<std::string, bool> used;
    std::queue<std::string> q;
    q.push(state);

    int ans = INT_MAX;
    while(!q.empty()) {
        if(ans != INT_MAX) {
            return ans;
        }
        std::string v1 = q.front();
        q.pop();
        used.insert({v1, 1});
        std::string v2 = v1;
        
        if (v1[9] >= 3) {
            checkCondition(v1, v2, dist, used, q, -3, ans);
        }

        if (v1[9] < 6) {
            checkCondition(v1, v2, dist, used, q, 3, ans);
        }

        if ((v1[9] % 3) > 0) {
            checkCondition(v1, v2, dist, used, q, -1, ans);
        }

        if ((v1[9] % 3) < 2) {
            checkCondition(v1, v2, dist, used, q, 1, ans);
        }
    }
    return ans;
}

int main() {
    std::string state(10, '9');
    int start[3][3];
    for(size_t i = 0; i < 3; ++i) {
        std::string s;
        std::getline(std::cin, s);
        for(size_t j = 0; j < 3; ++j) {
            if (s[j] != ' ') {
                state[i * 3 + j] = s[j];
                start[i][j] = s[j] - '0';
            } 
            else {
                start[i][j] = 0;
                state[i * 3 + j] = '9';
                state[9] = i * 3 + j;
            }
        }
    }
    //std::cout<<"1";
    if (isSolvable((int*) start)) {
        std::cout << bfs(state);
    }
    else {
        std::cout << -1 << '\n';
    }
    return 0;
}