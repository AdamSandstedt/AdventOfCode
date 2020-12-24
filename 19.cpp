#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>

#include "split.h"

using namespace std;

int correct1(string str, int index, int current, const unordered_map<int, set<vector<int> > > &sets, const unordered_map<int, char> &chars);
int correct2(string str, int index, set<vector<int> > &current, unordered_map<int, set<vector<int> > > &sets, unordered_map<int, char> &chars);

int main() {
    long ans1 = 0;
    long ans2 = 0;

    string input;
    getline(cin, input);
    auto sets = unordered_map<int, set<vector<int> > >();
    auto chars = unordered_map<int, char>();
    do {
        auto strs = split_strip(input, {":"});
        int x = stoi(strs.at(0));
        if(input.find("\"") != string::npos) {
            chars[x] = strs.at(1).at(1);
        } else {
            sets[x] = set<vector<int> >();
            auto xs = split_int(strs.at(1), {" "});
            auto v = vector<int>();
            for(int i = 0; i < xs.size(); i++) {
                if(xs.at(i) == -1) {
                    sets[x].insert(vector<int>(v));
                    v.clear();
                } else {
                    v.push_back(xs.at(i));
                }
            }
            sets[x].insert(vector<int>(v));
        }
        getline(cin, input);
    } while(!input.empty());

    while(getline(cin, input)) {
        if(correct1(input, 0, 0, sets, chars) == input.size())
            ans1++;
        if(correct2(input, 0, sets[0], sets, chars) == input.size())
            ans2++;
    }

    cout << ans1 << endl;
    cout << ans2 << endl;
    return 0;
}

int correct2(string str, int index, set<vector<int> > &current, unordered_map<int, set<vector<int> > > &sets, unordered_map<int, char> &chars) {
    for(vector<int> v: current) {
        int n = index;
        bool valid = true;
        for(int i = 0; i < v.size(); i++) {
            if(v.at(i) == 8) {
                int nn = correct2(str, n, sets.at(42), sets, chars);
                auto nv = vector<int>(v.size()-i-1);
                copy_n(v.begin()+i+1, v.size()-i-1, nv.begin());
                while(nn != -1) {
                    auto s = set<vector<int> >();
                    s.insert(nv);
                    int nnn = correct2(str, nn, s, sets, chars);
                    if(nnn != -1)
                        return nnn;
                    nn = correct2(str, nn, sets.at(42), sets, chars);
                }
                valid = false;
                break;
            } else if(v.at(i) == 11) {
                int nn = correct2(str, n, sets.at(42), sets, chars);
                auto nv = vector<int>(v.size()-i);
                nv.at(0) = 31;
                copy_n(v.begin()+i+1, v.size()-i-1, nv.begin()+1);
                while(nn != -1) {
                    auto s = set<vector<int> >();
                    s.insert(nv);
                    int nnn = correct2(str, nn, s, sets, chars);
                    if(nnn != -1)
                        return nnn;
                    nn = correct2(str, nn, sets.at(42), sets, chars);
                    nv.insert(nv.begin(), 31);
                }
                valid = false;
                break;
            } else {
                if(chars.count(v.at(i))) {
                    if(n >= str.size()) {
                        valid = false;
                        break;
                    }
                    if(str.at(n) != chars.at(v.at(i))) {
                        valid = false;
                        break;
                    } else {
                        n++;
                    }
                } else {
                    n = correct2(str, n, sets.at(v.at(i)), sets, chars);
                    if(n == -1) {
                        valid = false;
                        break;
                    }
                }
            }
        }
        if(valid) {
            return n;
        }
    }
    return -1;
}

int correct1(string str, int index, int current, const unordered_map<int, set<vector<int> > > &sets, const unordered_map<int, char> &chars) {
    for(auto v: sets.at(current)) {
        int n = index;
        bool valid = true;
        for(int x: v) {
            if(chars.count(x)) {
                if(str.at(n) != chars.at(x)) {
                    valid = false;
                    break;
                } else {
                    n++;
                }
            } else {
                n = correct1(str, n, x, sets, chars);
                if(n == -1) {
                    valid = false;
                    break;
                }
            }
        }
        if(valid) {
            return n;
        }
    }
    return -1;
}

