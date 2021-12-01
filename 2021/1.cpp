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
  int ans1 = 0;
  int ans2 = 0;

  int x;
  vector<int> xs;
  while(cin >> x) {
    xs.push_back(x);
  }
  for(int i = 0; i < xs.size()-1; i++) {
    if(xs[i] < xs[i+1])
      ans1++;
  }
  for(int i = 0; i < xs.size()-3; i++) {
    if(xs[i]+xs[i+1]+xs[i+2] < xs[i+1]+xs[i+2]+xs[i+3])
      ans2++;
  }

  cout << ans1 << endl;
  cout << ans2 << endl;
  return 0;
}

