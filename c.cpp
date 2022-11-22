#include<iostream>
#include<string>
#include<queue>

struct cell {
    int x;
    int y;
    int dist;
    cell() {}
    cell(int x_, int y_, int dist_) : x(x_), y(y_), dist(dist_) {}
};

std::vector<std::vector<cell> > path(30, std::vector<cell> (30));

bool check(int x, int y, size_t n) {
    return 0 < x && x <= n && 0 < y && y <= n;
}

int bfs(int knightPosX, int knightPosY, int targetPosX, int targetPosY, size_t n) {

    std::queue<cell> q;
    q.push(cell(knightPosX, knightPosY, 0));

    std::vector<std::vector<bool> > used(n + 1, std::vector<bool> (n + 1, 0));

    used[knightPosX][knightPosY] = 1;

    int dx[] = { -2, -1, 1, 2, -2, -1, 1, 2 };
    int dy[] = { -1, -2, -2, -1, 1, 2, 2, 1 };

    while(!q.empty()) {
        cell currCell = q.front();
        q.pop();
        if (currCell.x == targetPosX && currCell.y == targetPosY) {
            return currCell.dist;
        }
        for(size_t i = 0; i < 8; ++i) {
            int x = currCell.x + dx[i];
            int y = currCell.y + dy[i];
            if (check(x, y, n) && !used[x][y]) {
                used[x][y] = 1;
                path[x][y] = currCell;
                q.push({x, y, currCell.dist + 1});
            }
        }
    }
    return 0;
}

int main() {
    size_t n;
    std::string knightPos, targetPos;
    std::cin >> n >> knightPos >> targetPos;

    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int knightPosX = alphabet.find(knightPos[0]) + 1;

    int knightPosY = knightPos[1] - '0';
    if (knightPos.size() > 2) {
        knightPosY = knightPosY * 10 + knightPos[2] - '0';
    }
    int targetPosX = alphabet.find(targetPos[0]) + 1;
    int targetPosY = targetPos[1] - '0';
    if (targetPos.size() > 2) {
        targetPosY = targetPosY * 10 + targetPos[2] - '0';
    }

    std::cout << bfs(knightPosX, knightPosY, targetPosX, targetPosY, n) << '\n';

    std::vector<std::pair<char, int> > finalPath;
    int localX = targetPosX;
    int localY = targetPosY;
    while(localX != knightPosX || localY != knightPosY) {
        finalPath.push_back({alphabet[localX - 1], localY});
        int localX_copy = localX;
        localX = path[localX_copy][localY].x;
        localY = path[localX_copy][localY].y;
    }
    for(int i = finalPath.size() - 1; i >= 0; --i) {
        std::cout << finalPath[i].first << finalPath[i].second << '\n';
    }
    std::cout << '\n';
    return 0;
}