#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string input;
  vector<string> bits;
  while(getline(cin, input)) {
    bits.push_back(input);
  }

  vector<int> counts(bits.at(0).size(), 0);
  for(int i = 0; i < bits.size(); i++) {
    for(int j = 0; j < bits.at(i).size(); j++) {
      if(bits.at(i).at(j) == '1')
        counts.at(j)++;
    }
  }

  int g(0), e(0);
  for(int i = 0; i < counts.size(); i++) {
    g *= 2;
    e *= 2;
    if(counts.at(i)*2 > bits.size())
      g++;
    else
      e++;
  }

  vector<string> orig = bits;
  while(bits.size() > 1) {
    for(int i = 0; i < counts.size(); i++) {
      int count = 0;
      int total = bits.size();
      for(string s: bits)
        if(s.at(i) == '1')
          count++;
      for(int j = 0; j < bits.size(); j++) {
        if(bits.at(j).at(i) != (count*2 >= total) + '0') {
          bits.erase(bits.begin()+j);
          j--;
        }
      }
    }
  }
  int oxy = stoi(bits.front(), NULL, 2);

  bits = orig;
  while(bits.size() > 1) {
    for(int i = 0; i < counts.size(); i++) {
      int count = 0;
      int total = bits.size();
      for(string s: bits)
        if(s.at(i) == '1')
          count++;
      for(int j = 0; j < bits.size(); j++) {
        if(bits.at(j).at(i) != (count*2 < total) + '0') {
          bits.erase(bits.begin()+j);
          j--;
        }
      }
    }
  }
  int co2 = stoi(bits.front(), NULL, 2);

  cout << g*e << endl;
  cout << oxy*co2 << endl;
  return 0;
}

