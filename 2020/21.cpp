#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

#include "split.h"

using namespace std;

int main() {
    long ans = 0;

    string input;
    auto lines = vector<vector<string> >();
    auto poss = map<string, unordered_set<string> >();
    auto unsolved = unordered_set<string>();
    auto solved = unordered_set<string>();
    while(getline(cin, input)) {
        auto ls = split_strip(input, {" (", ")"});
        auto l1 = split_strip(ls.at(0), {" "});
        lines.push_back(l1);
        for(string s: l1)
            if(!solved.count(s))
                unsolved.insert(s);
        auto l2 = split_strip(ls.at(1), {" ", ", "});
        l2.erase(l2.begin());
        for(string s: l2) {
            auto ns = unordered_set<string>();
            if(!poss.count(s)) {
                for(string k: l1)
                    if(!solved.count(k))
                        ns.insert(k);
            } else {
                for(string k: l1)
                    if(poss[s].count(k))
                        ns.insert(k);
            }
            poss[s] = ns;
            if(ns.size() == 1) {
                auto q = queue<string>();
                q.push(s);
                while(!q.empty()) {
                    string s1 = q.front();
                    q.pop();
                    string s2 = *poss[s1].begin();
                    solved.insert(s2);
                    for(auto it = poss.begin(); it != poss.end(); it++)
                        if(it->first != s1) {
                            it->second.erase(s2);
                            if(it->second.size() == 1 && !solved.count(*it->second.begin()))
                                q.push(it->first);
                        }
                }
            }
        }
//         cout << endl;
//         for(auto p: poss) {
//             cout << p.first << ": ";
//             for(string s: p.second)
//                 cout << s << " ";
//             cout << endl;
//         }
    }
    for(auto p: poss) {
        for(string s: p.second) {
            unsolved.erase(s);
        }
    }
//     for(auto s: unsolved)
//         cout << s << " ";
//     cout << endl;
    for(auto l: lines) {
        for(string s: l) {
            if(unsolved.count(s))
                ans++;
        }
    }
    auto ss = map<string, string>();
    for(auto p: poss)
        ss[p.first] = *p.second.begin();

    cout << ans << endl;
    auto it = poss.begin();
    cout << *it->second.begin();
    for(it++; it != poss.end(); it++) {
        cout << "," << *it->second.begin();
    }
        cout << endl;
    return 0;
}

