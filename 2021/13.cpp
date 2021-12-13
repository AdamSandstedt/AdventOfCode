#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "split.h"

using namespace std;

int main() {
  int ans = 0;

  string input;
  getline(cin, input);
  set<pair<int, int> > ps;
  do {
    vector<int> ints = split_int(input, {","});
    ps.insert({ints[0],ints[1]});
    getline(cin, input);
  } while(input.size() > 1);

  cin.clear();
  bool first = true;
  while(cin >> input) {
    cin >> input;
    char c;
    int i;
    cin >> c;
    char d = c;
    cin >> c >> i;

    set<pair<int, int> > psN;
    for(auto p: ps) {
      if(d == 'x') {
        if(p.first == i)
          continue;
        if(p.first > i)
          p.first = 2*i-p.first;
      } else {
        if(p.second == i)
          continue;
        if(p.second > i)
          p.second = 2*i-p.second;
      }
      psN.insert({p.first, p.second});
    }
    ps = psN;
    if(first) {
      cout << ps.size() << endl;
      first = false;
    }
  }

  int xm = 0, ym = 0;
  for(auto p: ps) {
    xm = p.first > xm ? p.first : xm;
    ym = p.second > ym ? p.second : ym;
  }

  for(int y = 0; y <= ym; y++) {
    for(int x = 0; x <= xm; x++) {
      if(ps.count({x,y}))
        cout << 'O';
      else
        cout << ' ';
    }
    cout << endl;
  }

  return 0;
}

