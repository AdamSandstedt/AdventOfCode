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
  vector<int> nums = split_int(input, {","});

  vector<vector<vector<int> > > boards;
  int x;
  int b = -1, r = 4, c = 4;
  while(cin >> x) {
    c++;
    if(c == 5) {
      c = 0;
      r++;
      if(r == 5) {
        r = 0;
        b++;
        boards.push_back(vector<vector<int> >(5, vector<int>(5)));
      }
    }
    boards.at(b).at(r).at(c) = x;
  }
  int B = boards.size();

  vector<vector<vector<int> > > marked = vector<vector<vector<int> > >(B, vector<vector<int> >(5, vector<int>(5)));

  set<int> boardsWon;
  for(int b = 0; b < B; b++)
    boardsWon.insert(b);
  int firstToWin = -1;
  int lastToWin = -1;
  int firstX, lastX;
  for(int x: nums) {
    for(int b = 0; b < B; b++) {
      bool anyWin = false;
      for(int r = 0; r < 5; r++)
        for(int c = 0; c < 5; c++) {
          if(boards[b][r][c] == x)
            marked[b][r][c] = 1;
      }
      for(int c = 0; c < 5; c++) {
        bool win = true;
        for(int r = 0; r < 5; r++) {
          if(!marked[b][r][c]) {
            win = false;
            break;
          }
        }
        if(win) {
          anyWin = true;
          break;
        }
      }
      for(int r = 0; r < 5; r++) {
        bool win = true;
        for(int c = 0; c < 5; c++) {
          if(!marked[b][r][c]) {
            win = false;
            break;
          }
        }
        if(win) {
          anyWin = true;
          break;
        }
      }
      if(anyWin) {
        boardsWon.erase(b);
        if(boardsWon.empty()) {
          lastToWin = b;
          lastX = x;
          break;
        }
        if(firstToWin == -1) {
          firstToWin = b;
          for(int r = 0; r < 5; r++) {
            for(int c = 0; c < 5; c++) {
              if(!marked[b][r][c])
                ans += boards[b][r][c];
            }
          }
          cout << ans*x << endl;
        }
      }
    }
    if(lastToWin != -1) {
      lastX = x;
      break;
    }
  }

  ans = 0;
  for(int r = 0; r < 5; r++) {
    for(int c = 0; c < 5; c++) {
      if(!marked[lastToWin][r][c])
        ans += boards[lastToWin][r][c];
    }
  }

  cout << ans*lastX << endl;
  return 0;
}

