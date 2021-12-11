#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int main() {
  int ans = 0;

  string input;
  vector<vector<int> > grid;
  while(getline(cin, input)) {
    grid.push_back({});
    for(char c: input)
      grid.back().push_back(c-'0');
  }

  int H = grid.size();
  int W = grid[0].size();
  for(int s = 0; s < 100000; s++) {
    queue<pair<int, int> > q;
    vector<pair<int, int> > f;
    for(int y = 0; y < H; y++) {
      for(int x = 0; x < W; x++) {
        grid[y][x]++;
        if(grid[y][x] == 10) {
          q.push({y,x});
          f.push_back({y,x});
        }
      }
    }
    while(!q.empty()) {
      auto p = q.front();
      q.pop();
      int y = p.first;
      int x = p.second;
      for(int dx = -1; dx < 2; dx++)
        for(int dy = -1; dy < 2; dy++) {
          int nx = x + dx;
          int ny = y + dy;
          if(dx == 0 && dy == 0 || nx < 0 || ny < 0 || nx >= W || ny >= H)
            continue;
          grid[ny][nx]++;
          if(grid[ny][nx] == 10) {
            q.push({ny,nx});
            f.push_back({ny,nx});
          }
        }
    }
    int c = 0;
    for(auto p: f) {
      grid[p.first][p.second] = 0;
      ans++;
      c++;
    }
    if(s == 99)
      cout << ans << endl;
    if(c == H*W) {
      cout << s+1 << endl;
      break;
    }
  }

  return 0;
}

