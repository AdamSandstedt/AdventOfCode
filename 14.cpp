#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {

    string input;
    string mask;
    long maskOr, maskAnd;
    unordered_map<long, long> mem1 = unordered_map<long, long>();
    unordered_map<long, long> mem2 = unordered_map<long, long>();
    while(getline(cin, input)) {
        if(input.substr(0,2) == "ma") {
            maskOr = 0;
            maskAnd = 0;
            for(int i = 7; i < input.size(); i++) {
                if(input.at(i) == 'X') {
                    maskOr = (maskOr << 1) | 0;
                    maskAnd = (maskAnd << 1) | 1;
                } else if(input.at(i) == '1') {
                    maskOr = (maskOr << 1) | 1;
                    maskAnd = (maskAnd << 1) | 1;
                } else {
                    maskOr = (maskOr << 1) | 0;
                    maskAnd = (maskAnd << 1) | 0;
                }
            }
            mask = input.substr(7);

        } else {
            int i = input.find("]");
            long m = stoi(input.substr(4, i - 4));
            long x = stoi(input.substr(i + 4));
            mem1[m] = (x | maskOr) & maskAnd;

            unordered_set<long> s = unordered_set<long>();
            unordered_set<long> ns = unordered_set<long>();
            s.insert(0);
            for(int i = 0; i < mask.size(); i++) {
                m = m << 1;
                ns.clear();
                if(mask.at(i) == 'X') {
                    for(long y: s) {
                        ns.insert((y << 1) | 1);
                        ns.insert((y << 1) | 0);
                    }
                } else if(mask.at(i) == '1') {
                    for(long y: s) {
                        ns.insert((y << 1) | 1);
                    }
                } else {
                    for(long y: s) {
                        ns.insert((y << 1) | ((m >> 36) & 1));
                    }
                }
                s = unordered_set<long>(ns);
            }
            for(long y: s) {
                mem2[y] = x;
            }

        }
    }

    long ans = 0;
    for(auto it = mem1.begin(); it != mem1.end(); it++) {
        ans += it->second;
    }
    cout << ans << endl;

    ans = 0;
    for(auto it = mem2.begin(); it != mem2.end(); it++) {
        ans += it->second;
    }
    cout << ans << endl;

    return 0;
}

