#include <iostream>
#include <string>
#include <algorithm>
#include <deque>
#include <set>

using namespace std;

int combat2(deque<long> &q1, deque<long> &q2);
long combat1(deque<long> q1, deque<long> q2);

int main() {
    long ans = 0;

    auto q1 = deque<long>();
    auto q2 = deque<long>();
    string input;
    getline(cin, input);
    getline(cin, input);
    do {
        q1.push_back(stol(input));
        getline(cin, input);
    } while(!input.empty());

    getline(cin, input);
    getline(cin, input);
    do {
        q2.push_back(stol(input));
        getline(cin, input);
    } while(!input.empty());

    cout << combat1(q1, q2) << endl;

    if(combat2(q1, q2) == 1) {
        long n = q1.size();
        while(!q1.empty()) {
            ans += q1.front() * n;
            n--;
            q1.pop_front();
        }
    } else {
        long n = q2.size();
        while(!q2.empty()) {
            ans += q2.front() * n;
            n--;
            q2.pop_front();
        }
    }
    cout << ans << endl;
    return 0;
}

int combat2(deque<long> &q1, deque<long> &q2) {
    set<deque<long> > prev = set<deque<long> >();
    while(!q1.empty() && !q2.empty()) {
        if(prev.count(q1))
            return 1;
        else
            prev.insert(q1);

        int c1 = q1.front();
        int c2 = q2.front();
        q1.pop_front();
        q2.pop_front();

        if(q1.size() < c1 || q2.size() < c2) {
            if(c1 > c2) {
                q1.push_back(c1);
                q1.push_back(c2);
            } else {
                q2.push_back(c2);
                q2.push_back(c1);
            }
        } else {
            auto nq1 = deque<long>(c1);
            copy_n(q1.begin(), c1, nq1.begin());
            auto nq2 = deque<long>(c2);
            copy_n(q2.begin(), c2, nq2.begin());

            if(combat2(nq1, nq2) == 1) {
                q1.push_back(c1);
                q1.push_back(c2);
            } else {
                q2.push_back(c2);
                q2.push_back(c1);
            }
        }
    }

    if(!q1.empty())
        return 1;
    else
        return 2;
}

long combat1(deque<long> q1, deque<long> q2) {
    while(!q1.empty() && !q2.empty()) {
        int c1 = q1.front();
        int c2 = q2.front();
        q1.pop_front();
        q2.pop_front();
        if(c1 > c2) {
            q1.push_back(c1);
            q1.push_back(c2);
        } else {
            q2.push_back(c2);
            q2.push_back(c1);
        }
    }

    long ans = 0;

    if(!q1.empty()) {
        long n = q1.size();
        while(!q1.empty()) {
            ans += q1.front() * n;
            n--;
            q1.pop_front();
        }
    } else {
        long n = q2.size();
        while(!q2.empty()) {
            ans += q2.front() * n;
            n--;
            q2.pop_front();
        }
    }

    return ans;
}
