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

  cout << ans << endl;
  return 0;
}

