#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int main() {
  string alg;
  getline(cin, alg);

  string input;
  getline(cin, input);
  int y = 0;
  set<pair<int, int> > grid;
  while(getline(cin, input)) {
    for(int x = 0; x < input.size(); x++)
      if(input[x] == '#')
        grid.insert({x,y});
    y++;
  }

  int bound = 200;
  for(int iter = 1; iter <= 50; iter++) {
    set<pair<int, int> > newGrid;
    for(int y0 = -bound; y0 <= bound; y0++) {
      for(int x0 = -bound; x0 <= bound; x0++) {
        int index = 0;
        for(int dy = -1; dy <= 1; dy++) {
          for(int dx = -1; dx <= 1; dx++) {
            int x = x0+dx;
            int y = y0+dy;
            index = index*2 + grid.count({x,y});
          }
        }
        if(alg[index] == '#')
          newGrid.insert({x0,y0});
      }
    }
    grid = newGrid;
    bound--;
    if(iter == 2 || iter == 50)
      cout << grid.size() << endl;
  }

  return 0;
}

