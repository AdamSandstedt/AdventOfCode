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

typedef mpz_class mz;

int check(vector<int> &ints, int dx, int dy) {
  int x0 = ints[0], x1 = ints[1], y0 = ints[2], y1 = ints[3];
  int x = 0, y = 0;
  int ymax = 0;
  while(y > y0) {
    x += dx;
    y += dy;
    if(y > ymax)
      ymax = y;
    if(x <= x1 && x >= x0 && y <= y1 && y >= y0) {
      return ymax;
    }
    dx = max(0, dx-1);
    dy--;
  }
  return -1;
}

int main() {
  mz ans = 0;

  string input;
  getline(cin, input);
  vector<int> ints = split_int(input.substr(15), {"..", ", y="});
  int x0 = ints[0], x1 = ints[1], y0 = ints[2], y1 = ints[3];

  int ymax = 0;
  int count = 0;
  int dymax = 0;
  for(int dx = 0; dx <= x1; dx++) {
    for(int dy = y0; dy <= -2*y0; dy++) {
      int h = check(ints, dx, dy);
      if(h != -1) {
        if(h > ymax)
          ymax = h;
        count++;
      }
    }
  }

  cout << ymax << endl;
  cout << count << endl;
  return 0;
}

