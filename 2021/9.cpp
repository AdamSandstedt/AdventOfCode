#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int main() {
  int ans = 0;

  string input;
  vector<vector<int> > hs;
  while(getline(cin, input)) {
    hs.push_back({});
    for(char c: input)
      hs.back().push_back(c-'0');
  }

  int H = hs.size();
  int W = hs.front().size();
  vector<pair<int, int> > adj = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
  int c = 0;
  vector<vector<int> > basin(H, vector<int>(W, -1));
  queue<pair<int, int> > q;
  for(int y = 0; y < H; y++) {
    for(int x = 0; x < W; x++) {
      bool lowest = true;
      for(auto p: adj) {
        int x1 = x+p.first;
        int y1 = y+p.second;
        if(x1 >= 0 && x1 < W && y1 >= 0 && y1 < H)
          if(hs[y1][x1] <= hs[y][x]) {
            lowest = false;
            break;
          }
      }
      if(lowest) {
        ans += hs[y][x]+1;
        basin[y][x] = c;
        c++;
        q.push({y, x});
      }
    }
  }

  vector<int> sizes(c, 1);
  while(!q.empty()) {
    auto f = q.front();
    q.pop();
    int y = f.first;
    int x = f.second;
    for(auto p: adj) {
      int x1 = x+p.first;
      int y1 = y+p.second;
      if(x1 >= 0 && x1 < W && y1 >= 0 && y1 < H) {
        if(basin[y1][x1] == -1 && hs[y1][x1] != 9) {
          q.push({y1, x1});
          basin[y1][x1] = basin[y][x];
          sizes[basin[y][x]]++;
        }
      }
    }
  }

  cout << ans << endl;

  ans = 1;
  sort(sizes.begin(), sizes.end());

  auto it = sizes.rbegin();
  ans *= *it;
  it++;
  ans *= *it;
  it++;
  ans *= *it;
  cout << ans << endl;
  return 0;
}

