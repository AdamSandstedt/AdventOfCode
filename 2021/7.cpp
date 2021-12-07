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

#include "split.h"

using namespace std;

int main() {
  int ans = 0;

  string input;
  getline(cin, input);
  vector<int> ints = split_int(input, {","});

  map<int, int> counts;
  for(int x: ints) {
    counts[x]++;
  }
  int min = counts.begin()->first;
  int max = counts.rbegin()->first;
  cout << min << ", " << max << endl;

  int minFuel1 = 1 << 30;
  int minFuel2 = 1 << 30;
  for(int pos = min; pos <= max; pos++) {
    int fuel1 = 0;
    int fuel2 = 0;
    for(auto p: counts) {
      int dist = abs(p.first - pos);
      fuel1 += dist*p.second;
      fuel2 += dist*(dist+1)/2*p.second;
    }
    if(fuel1 < minFuel1)
      minFuel1 = fuel1;
    if(fuel2 < minFuel2)
      minFuel2 = fuel2;
  }

  cout << minFuel1 << endl;
  cout << minFuel2 << endl;
  return 0;
}

