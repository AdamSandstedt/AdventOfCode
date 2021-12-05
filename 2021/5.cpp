#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "split.h"

using namespace std;

int main() {
  int ans1 = 0;
  int ans2 = 0;

  string input;
  map<vector<int>, int> counts1;
  map<vector<int>, int> counts2;
  while(getline(cin, input)) {
    vector<string> s1 = split_strip(input, {" -> "});
    vector<int> p1 = split_int(s1[0], {","});
    vector<int> p2 = split_int(s1[1], {","});
    if(p1[0] == p2[0]) {
      int y1 = min(p1[1], p2[1]);
      int y2 = max(p1[1], p2[1]);
      for(int y = y1; y <= y2; y++) {
        counts1[{p1[0], y}]++;
        counts2[{p1[0], y}]++;
      }
    } else if(p1[1] == p2[1]) {
      int x1 = min(p1[0], p2[0]);
      int x2 = max(p1[0], p2[0]);
      for(int x = x1; x <= x2; x++) {
        counts1[{x, p1[1]}]++;
        counts2[{x, p1[1]}]++;
      }
    } else {
      int x1, x2, y1, y2;
      if(p1[0] < p2[0]) {
        x1 = p1[0];
        x2 = p2[0];
        y1 = p1[1];
        y2 = p2[1];
      } else {
        x1 = p2[0];
        x2 = p1[0];
        y1 = p2[1];
        y2 = p1[1];
      }
      int dy;
      if(y1 < y2)
        dy = 1;
      else
        dy = -1;
      int x = x1, y = y1;
      for(; x <= x2;) {
        counts2[{x, y}]++;
        x++;
        y += dy;
      }
    }
  }

  for(auto p: counts1)
    if(p.second > 1)
      ans1++;
  for(auto p: counts2)
    if(p.second > 1)
      ans2++;

  cout << ans1 << endl;
  cout << ans2 << endl;
  return 0;
}

