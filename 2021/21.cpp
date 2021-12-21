#include <iostream>
#include <string>
#include <tuple>
#include <boost/unordered_map.hpp>
using boost::unordered_map;
#include <gmpxx.h>

using namespace std;

typedef mpz_class mz;

pair<mz, mz> winner(int score1, int score2, int pos1, int pos2, bool turn) {
  static unordered_map<tuple<int, int, int, int, bool>, pair<mz, mz> > mem;
  if(score1 >= 21)
    return {1, 0};
  if(score2 >= 21)
    return {0, 1};
  tuple<int,int,int,int,bool> par = {score1, score2, pos1, pos2, turn};
  if(mem.count(par))
    return mem[par];
  mz w1 = 0;
  mz w2 = 0;
  int rolls[3];
  for(rolls[0] = 1; rolls[0] <= 3; rolls[0]++) {
    for(rolls[1] = 1; rolls[1] <= 3; rolls[1]++) {
      for(rolls[2] = 1; rolls[2] <= 3; rolls[2]++) {
        pair<mz, mz> p;
        if(turn) {
          int pos2n = (pos2+rolls[0]+rolls[1]+rolls[2]-1)%10+1;
          int score2n = score2 + pos2n;
          p = winner(score1, score2n, pos1, pos2n, !turn);
        } else {
          int pos1n = (pos1+rolls[0]+rolls[1]+rolls[2]-1)%10+1;
          int score1n = score1 + pos1n;
          p = winner(score1n, score2, pos1n, pos2, !turn);
        }
        w1 += p.first;
        w2 += p.second;
      }
    }
  }
  mem[par] = {w1, w2};
  return {w1, w2};
}

int main() {
  string input;
  int pos1, pos2;
  cin >> input >> input >> input >> input >> pos1;
  cin >> input >> input >> input >> input >> pos2;

  int roll = 0;
  bool turn = 0;
  int pos[2] = {pos1, pos2};
  int scores[2] = {0,0};
  while(scores[0] < 1000 && scores[1] < 1000) {
    roll++;
    pos[turn] += (roll-1)%100+1;
    roll++;
    pos[turn] += (roll-1)%100+1;
    roll++;
    pos[turn] += (roll-1)%100+1;
    pos[turn] = (pos[turn]-1)%10+1;
    scores[turn] += pos[turn];
    turn = !turn;
  }
  cout << scores[turn]*roll << endl;

  auto p = winner(0, 0, pos[0], pos[1], 0);
  cout << max(p.first, p.second) << endl;

  return 0;
}

