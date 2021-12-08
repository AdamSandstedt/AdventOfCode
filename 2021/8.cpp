#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <vector>
#include <set>

#include "split.h"

using namespace std;

int main() {
  int ans = 0;
  int ans2 = 0;

  string input;
  while(getline(cin, input)) {
    vector<string> inOut = split_strip(input, {"|"});
    vector<string> ins = split_str(inOut[0], {" "});
    vector<string> outs = split_str(inOut[1], {" "});
    int x = 0;
    for(int i = outs.size()-1; i >= 0; i--) {
      string s = outs[i];
      int l = s.size();
      if(l == 2 || l == 3 || l == 4 || l == 7)
        ans++;
    }
    vector<set<char> > digits(10, {});
    vector<set<char> > sets(10, {});
    for(int i = 0; i < 10; i++) {
      for(char c: ins[i])
        sets[i].insert(c);
    }
    for(auto s: sets) {
      if(s.size() == 2)
          digits[1] = s;
      else if(s.size() == 3)
          digits[7] = s;
      else if(s.size() == 4)
          digits[4] = s;
      else if(s.size() == 7)
          digits[8] = s;
    }
    set<char> d = digits[4];
    for(char c: digits[1])
      d.erase(c);
    for(auto s: sets) {
      if(s.size() == 5) {
        auto it = d.begin();
        if(s.count(*it)) {
          it++;
          if(s.count(*it))
            digits[5] = s;
        }
      }
    }
    d = digits[8];
    for(char c: digits[5])
      d.erase(c);
    for(auto s: sets) {
      if(s.size() == 5) {
        auto it = d.begin();
        if(s.count(*it)) {
          it++;
          if(s.count(*it))
            digits[2] = s;
        }
      }
      if(s.size() == 6) {
        auto it = d.begin();
        if(s.count(*it)) {
          it++;
          if(s.count(*it))
            digits[0] = s;
        }
      }
    }
    for(char c: digits[1])
      d.erase(c);
    for(auto s: sets) {
      if(s.size() == 5) {
        if(s != digits[2] && s != digits[5])
          digits[3] = s;
      }
      if(s.size() == 6) {
        auto it = d.begin();
        if(s != digits[0]) {
          if(s.count(*it))
            digits[6] = s;
          else
            digits[9] = s;
        }
      }
    }
    for(int i = 0; i < outs.size(); i++) {
      string s = outs[i];
      d.clear();
      for(char c: s)
        d.insert(c);
      for(int i = 0; i < 10; i++)
        if(digits[i] == d)
          x = x*10 + i;
    }
    ans2 += x;
  }

  cout << ans << endl;
  cout << ans2 << endl;
  return 0;
}

