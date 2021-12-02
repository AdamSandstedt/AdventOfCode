#include <iostream>
#include <string>

using namespace std;

int main() {
  int ans = 0;

  string input;
  int x;
  int depth1(0), depth2(0), horiz(0), aim(0);
  while(cin >> input) {
    cin >> x;
    if(input == "forward") {
      horiz += x;
      depth2 += aim*x;
    } else if(input == "down") {
      depth1 -= x;
      aim -= x;
    } else {
      depth1 += x;
      aim += x;
    }
  }

  cout << -horiz*depth1 << endl;
  cout << -horiz*depth2 << endl;
  return 0;
}

