#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <gmpxx.h>

#include "split.h"

using namespace std;

typedef mpz_class mz;

mz bitsToInt(vector<bool> &pac, int pos, int len) {
  mz ret = 0;
  for(int i = pos; i < pos+len; i++)
    ret = ret*2+pac[i];
  return ret;
}

tuple<mz, int, mz> parse(vector<bool> &pac, int pos) {
  mz ret = 0;
  mz ver = 0;
  ver += bitsToInt(pac, pos, 3);
  pos += 3;
  mz typ = bitsToInt(pac, pos, 3);
  pos += 3;
  vector<mz> rets;
  if(typ == 4) {
    ret = 0;
    while(pac[pos]) {
      ret = ret*16+bitsToInt(pac, pos+1, 4);
      pos += 5;
    }
    ret = ret*16+bitsToInt(pac, pos+1, 4);
    pos += 5;;
  } else {
    bool lenTyp = pac[pos];
    pos++;
    if(lenTyp) {
      mz l = bitsToInt(pac, pos, 11);
      pos += 11;
      for(int n = 0; n < l; n++) {
        auto p = parse(pac, pos);
        pos = get<1>(p);
        rets.push_back(get<0>(p));
        ver += get<2>(p);
      }
    } else {
      mz l = bitsToInt(pac, pos, 15);
      pos += 15;
      mz end = pos + l;
      while(pos < end) {
        auto p = parse(pac, pos);
        pos = get<1>(p);
        rets.push_back(get<0>(p));
        ver += get<2>(p);
      }
    }
    if(typ == 0) {
      ret = 0;
      for(mz x: rets) {
        ret += x;
      }
    } else if(typ == 1) {
      ret = 1;
      for(mz x: rets) {
        ret *= x;
      }
    } else if(typ == 2) {
      ret = rets[0];
      for(mz x: rets) {
        ret = ret < x ? ret : x;
      }
    } else if(typ == 3) {
      ret = rets[0];
      for(mz x: rets) {
        ret = ret > x ? ret : x;
      }
    } else if(typ == 5) {
      ret = rets[0] > rets[1];
    } else if(typ == 6) {
      ret = rets[0] < rets[1];
    } else if(typ == 7) {
      ret = rets[0] == rets[1];
    }
  }
  return {ret, pos, ver};
}

int main() {
  mz ans = 0;

  string input;
  getline(cin, input);
  vector<bool> pac;
  for(int i = 0; i < input.size(); i++) {
    int x = stoi(input.substr(i,1), NULL, 16);
    pac.push_back(x & 8);
    pac.push_back(x & 4);
    pac.push_back(x & 2);
    pac.push_back(x & 1);
  }

  auto p = parse(pac, 0);

  cout << get<2>(p) << endl;
  cout << get<0>(p) << endl;
  return 0;
}

