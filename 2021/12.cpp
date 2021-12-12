#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "split.h"

using namespace std;

int paths(unordered_map<string, vector<string> > &edges, unordered_set<string> &vis, string node, bool sec) {
  if(node == "end")
    return 1;
  int ans = 0;
  for(string s: edges[node]) {
    if(!vis.count(s) || !sec && s != "start") {
      bool secN = false;
      if(!sec && vis.count(s)) {
        sec = true;
        secN = true;
      }
      if(islower(s[0]))
        vis.insert(s);
      ans += paths(edges, vis, s, sec);
      if(!secN)
        vis.erase(s);
      else
        sec = false;
    }
  }
  return ans;
}

int main() {
  string input;
  unordered_map<string, vector<string> > edges;
  while(getline(cin, input)) {
    vector<string> v = split_str(input, {"-"});
    edges[v[0]].push_back(v[1]);
    edges[v[1]].push_back(v[0]);
  }

  unordered_set<string> vis = {"start"};
  cout << paths(edges, vis, "start", true) << endl;
  cout << paths(edges, vis, "start", false) << endl;

  return 0;
}

