#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <tuple>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <gmpxx.h>

#include "split.h"

using namespace std;

int main() {
  mpz_class ans = 0;

  string input;
  vector<vector<int> > grid;
  while(getline(cin, input)) {
    grid.push_back({});
    for(char c: input) {
      grid.back().push_back(c-'0');
    }
  }
  int H = grid.size();
  int HN = H*5;
  int W = grid.front().size();
  int WN = W*5;

  vector<vector<int> > risks = vector<vector<int> >(HN, vector<int>(WN, -1));
  risks[0][0] = 0;
  queue<pair<int, int> > q;
  q.push({0,0});
  while(!q.empty()) {
    int y = q.front().first;
    int x = q.front().second;
    q.pop();
    for(int dy = -1; dy <= 1; dy++) {
      for(int dx = -1; dx <= 1; dx++) {
        if(dy != 0 && dx != 0)
          continue;
        int yn = y+dy;
        int xn = x+dx;
        if(xn < 0 || yn < 0 || xn >= WN || yn >= HN)
          continue;
        int g = (grid[yn%H][xn%W]+yn/H+xn/W-1) % 9 + 1;
        if(risks[yn][xn] == -1 || risks[y][x] + g < risks[yn][xn]) {
          risks[yn][xn] = risks[y][x] + g;
          q.push({yn,xn});
        }
      }
    }
  }

  cout << risks[H-1][W-1] << endl;
  cout << risks[HN-1][WN-1] << endl;
  return 0;
}

