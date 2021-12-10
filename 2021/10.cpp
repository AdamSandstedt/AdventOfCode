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
  vector<string> lines;
  set<char> open = {'{', '(', '<', '['};
  map<char, char> close = {{'}','{'}, {')','('}, {'>','<'}, {']','['}};
  map<char, int> scores = {{'}',1197}, {')',3}, {'>',25137}, {']',57}};
  map<char, int> scores2 = {{'{',3}, {'(',1}, {'<',4}, {'[',2}};
  while(getline(cin, input)) {
    lines.push_back(input);
  }

  vector<long> ans2;
  for(string str: lines) {
    // if(input[0] == close[input[input.size()-1]])
    stack<char> s;
    char cor = ' ';
    for(char c: str) {
      if(open.count(c))
        s.push(c);
      else {
        if(close[c] == s.top()) {
          s.pop();
        } else {
          if(cor == ' ') {
            cor = c;
            s.pop();
          } else {
            cor = 'x';
            break;
          }
        }
      }
    }
    long a = 0;
    if(cor != 'x' && cor != ' ') {
      ans += scores[cor];
    } else {
      while(!s.empty()) {
        a = a*5 + scores2[s.top()];
        s.pop();
      }
    }
    if(a != 0) {
      ans2.push_back(a);
    }
  }
  sort(ans2.begin(), ans2.end());

  cout << ans << endl;
  cout << ans2[ans2.size()/2] << endl;
  return 0;
}

