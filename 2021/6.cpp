#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "split.h"

using namespace std;

int main() {
  long ans = 0;

  string input;
  getline(cin, input);
  vector<int> ints = split_int(input, {","});

  map<int, long> days;
  for(int x: ints)
    days[x]++;
  for(int d = 1; d < 80; d++) {
    for(int i = 1; i <= 9; i++) {
      days[i-1] = days[i];
    }
    days[9] = days[0];
    days[7] += days[0];
  }
  for(int i = 1; i <= 9; i++)
    ans += days[i];
  cout << ans << endl;

  for(int d = 80; d < 256; d++) {
    for(int i = 1; i <= 9; i++) {
      days[i-1] = days[i];
    }
    days[9] = days[0];
    days[7] += days[0];
  }

  ans = 0;
  for(int i = 1; i <= 9; i++)
    ans += days[i];
  cout << ans << endl;
  return 0;
}

