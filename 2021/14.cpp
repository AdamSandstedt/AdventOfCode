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
  string str1, str2, templ;
  cin >> templ;

  unordered_map<string, string> pairs;
  while(cin >> str1) {
    cin >> str2;
    cin >> str2;
    pairs[str1] = str2;
  }

  unordered_map<string, mpz_class> tmpCounts;
  for(int i = 0; i < templ.size()-1; i++)
    tmpCounts[templ.substr(i,2)]++;

  for(int step = 1; step <= 40; step++) {
    unordered_map<string, mpz_class> orig = tmpCounts;
    for(auto p: orig) {
      if(pairs.count(p.first)) {
        tmpCounts[p.first.substr(0,1)+pairs[p.first]] += p.second;
        tmpCounts[pairs[p.first]+p.first.substr(1,1)] += p.second;
        tmpCounts[p.first] -= p.second;
      }
    }

    if(step == 10 || step == 40) {
      unordered_map<char, mpz_class> counts;
      counts[templ[0]]++;
      counts[templ[templ.size()-1]]++;
      for(auto p: tmpCounts) {
        counts[p.first[0]] += p.second;
        counts[p.first[1]] += p.second;
      }

      mpz_class max = 0;
      mpz_class min = 1L << 60;
      for(auto p: counts) {
        max = p.second > max ? p.second : max;
        min = p.second < min ? p.second : min;
      }

      cout << max/2 - min/2 << endl;
    }
  }
  return 0;
}

