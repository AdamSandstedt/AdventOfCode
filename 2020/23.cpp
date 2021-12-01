#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <unordered_map>

#include "split.h"

using namespace std;

int main() {
    long ans = 1;

    string input;
    getline(cin, input);
    list<int> cups1 = list<int>();
    list<int> cups2 = list<int>();
    for(int i = 0; i < input.size(); i++) {
        cups1.push_back(input.at(i) - '0');
        cups2.push_back(input.at(i) - '0');
    }
    for(int i = 10; i <= 1000000; i++)
        cups2.push_back(i);

    cups1.splice(cups1.end(), cups1, cups1.begin());
    cups2.splice(cups2.end(), cups2, cups2.begin());
    auto m1 = unordered_map<int, list<int>::iterator>();
    auto m2 = unordered_map<int, list<int>::iterator>();
    for(auto it = cups1.begin(); it != cups1.end(); it++) {
        m1[*it] = it;
    }
    for(auto it = cups2.begin(); it != cups2.end(); it++) {
        m2[*it] = it;
    }

    const int cupsSize1 = cups1.size();
    const int cupsSize2 = cups2.size();
    list<int> removed = list<int>();
    for(int move = 0; move < 100; move++) {
        auto i2 = cups1.begin();
        advance(i2,3);
        removed.splice(removed.begin(), cups1, cups1.begin(), i2);
        for(int i = cups1.back()-1; i > 0; i--) {
            if(find(removed.begin(), removed.end(), i) == removed.end()) {
                auto maxUnder = m1[i];
                cups1.splice(++maxUnder, removed, removed.begin(), removed.end());
                break;
            }
        }
        if(!removed.empty()) {
            for(int i = cupsSize1; i > 0; i--) {
                if(find(removed.begin(), removed.end(), i) == removed.end()) {
                    auto max = m1[i];
                    cups1.splice(++max, removed, removed.begin(), removed.end());
                    break;
                }
            }
        }
        cups1.splice(cups1.end(), cups1, cups1.begin());
    }
    while(cups1.front() != 1) {
        cups1.splice(cups1.end(), cups1, cups1.begin());
    }

    cups1.pop_front();
    for(auto it = cups1.begin(); it != cups1.end(); it++)
        cout << *it;
    cout << endl;

    for(int move = 0; move < 10000000; move++) {
        auto i2 = cups2.begin();
        advance(i2,3);
        removed.splice(removed.begin(), cups2, cups2.begin(), i2);
        for(int i = cups2.back()-1; i > 0; i--) {
            if(find(removed.begin(), removed.end(), i) == removed.end()) {
                auto maxUnder = m2[i];
                cups2.splice(++maxUnder, removed, removed.begin(), removed.end());
                break;
            }
        }
        if(!removed.empty()) {
            for(int i = cupsSize2; i > 0; i--) {
                if(find(removed.begin(), removed.end(), i) == removed.end()) {
                    auto max = m2[i];
                    cups2.splice(++max, removed, removed.begin(), removed.end());
                    break;
                }
            }
        }
        cups2.splice(cups2.end(), cups2, cups2.begin());
    }
    while(cups2.front() != 1) {
        cups2.splice(cups2.end(), cups2, cups2.begin());
    }

    cups2.pop_front();
    auto it = cups2.begin();
    ans *= *(it++);
    ans *= *it;
    cout << ans << endl;

    return 0;
}

