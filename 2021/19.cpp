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
#include <map>
#include <unordered_map>
#include <gmpxx.h>
#include <boost/unordered_set.hpp>
using boost::unordered_set;

#include "split.h"

using namespace std;

typedef mpz_class mz;

void rotate(unordered_set<vector<int> > &scan, int axis) {
  int c1 = (axis+1)%3;
  int c2 = (axis+2)%3;
  unordered_set<vector<int> > orig = scan;
  scan.clear();
  for(auto p: orig) {
    int tmp = p[c1];
    p[c1] = p[c2];
    p[c2] = -1*tmp;
    scan.insert(p);
  }
}

void nextRotation(unordered_set<vector<int> > &scan, int rot) {
  if(rot % 4 == 0) {
    rotate(scan, (rot/4+2)%3);
  }
  rotate(scan, (rot/4+1)%3);
}

vector<int> overlap(unordered_set<vector<int> > &scan0, unordered_set<vector<int> > &scan1) {
  for(auto p0: scan0) {
    for(auto p1: scan1) {
      int count = 0;
      int failed = 0;
      int max = scan0.size();
      for(auto p2: scan0) {
        if(scan1.count({p2[0]-p0[0]+p1[0],p2[1]-p0[1]+p1[1],p2[2]-p0[2]+p1[2]}))
          count++;
        else
          failed++;
        if(max-failed+count < 12)
          break;
      }
      if(count >= 12)
        return {p0[0]-p1[0],p0[1]-p1[1],p0[2]-p1[2]};
    }
  }
  return {0,0,0};
}

int main() {
  mz ans = 0;

  string input;
  vector<unordered_set<vector<int> > > scans;
  while(getline(cin, input)) {
    if(input.size() == 0)
      continue;
    if(input[0] == '-' && input[1] == '-') {
      scans.push_back({});
      continue;
    }
    vector<int> ints = split_int(input, {","});
    scans.back().insert(ints);
  }

  vector<vector<int> > coords(scans.size(), {0,0,0});
  vector<bool> solved(scans.size(), false);
  solved[0] = true;
  vector<vector<bool> > checked(scans.size(), vector<bool>(scans.size(), false));
  int numSolved = 1;
  while(numSolved < scans.size()) {
    for(int s0 = 0; s0 < scans.size(); s0++) {
      for(int s1 = s0+1; s1 < scans.size(); s1++) {
        bool solved0 = solved[s0];
        bool solved1 = solved[s1];
        if(solved0 && solved1 || !solved0 && !solved1)
          continue;
        if(checked[s0][s1])
          continue;
        checked[s0][s1] = true;
        for(int rot = 0; rot < 24; rot++) {
          auto v = overlap(scans[s0], scans[s1]);
          if(v[0] != 0 && v[1] != 0 && v[2] != 0) {
            if(s0 == 0 || solved0) {
              coords[s1] = {coords[s0][0]+v[0],coords[s0][1]+v[1],coords[s0][2]+v[2]};
              solved[s1] = true;
              numSolved++;
            } else {
              coords[s0] = {coords[s1][0]-v[0],coords[s1][1]-v[1],coords[s1][2]-v[2]};
              solved[s0] = true;
              numSolved++;
            }
            break;
          }
          if(s0 == 0 || solved0)
            nextRotation(scans[s1], rot);
          else
            nextRotation(scans[s0], rot);
        }
      }
    }
  }

  unordered_set<vector<int> > pts;
  for(int s = 0; s < scans.size(); s++) {
    auto scan = scans[s];
    for(auto p: scan) {
      pts.insert({coords[s][0]+p[0],coords[s][1]+p[1],coords[s][2]+p[2]});
    }
  }

  int maxDist = 0;
  for(auto v0: coords) {
    for(auto v1: coords) {
      int dist = abs(v1[0]-v0[0]) + abs(v1[1]-v0[1]) + abs(v1[2]-v0[2]);
      if(dist > maxDist)
        maxDist = dist;
    }
  }

  cout << pts.size() << endl;
  cout << maxDist << endl;
  return 0;
}

