#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include <stack>
#include <set>
#include <unordered_set>
#include <sstream>
#include <map>
#include <unordered_map>
#include <iomanip>
#include <cstring>

using namespace std;

int main() {
    long ans = 1;

    char input[256];
    cin.getline(input, 256);
    vector<long> valid = vector<long>();
    int I = 0;
    while(!((string)input).empty()) {
        I++;
        strtok(input, ":");
        valid.push_back(atoi(strtok(NULL, "-")));
        valid.push_back(atoi(strtok(NULL, " ")));
        strtok(NULL, " ");
        valid.push_back(atoi(strtok(NULL, "-")));
        valid.push_back(atoi(strtok(NULL, "")));
        cin.getline(input, 256);
    }
    vector<long> your = vector<long>();

    cin.getline(input, 256);
    cin.getline(input, 256);
    char *s = strtok(input, ",");
    do {
        your.push_back(atoi(s));
    } while((s = strtok(NULL, ",")));
    cin.getline(input, 256);

    cin.getline(input, 256);
    long sum = 0;
    vector<unordered_set<int> > poss = vector<unordered_set<int> >();
    for(int i = 0; i < I; i++) {
        unordered_set<int> s = unordered_set<int>();
        poss.push_back(s);
    }

    cin.getline(input, 256);
    while(!((string)input).empty()) {
        s = strtok(input, ",");
        vector<long> xs = vector<long>();
        do {
            long x = atoi(s);
            xs.push_back(x);
        } while((s = strtok(NULL, ",")));
        bool t = true;
        for(int j = 0; j < xs.size(); j++) {
            bool b = false;
            long x = xs.at(j);
            for(int i = 0; i < valid.size(); i += 2) {
                if(x >= valid.at(i) && x <= valid.at(i+1)) {
                    b = true;
                    break;
                }
            }
            if(!b) {
                sum += x;
                t = false;
                break;
            }
        }
        if(t) {
            for(int j = 0; j < xs.size(); j++) {
                poss.at(j).insert(xs.at(j));
            }
        }
        cin.getline(input, 256);
    }
    poss.at(0).erase(0);

    cout << sum << endl;

    unordered_set<int> solved = unordered_set<int>();
    vector<int> stuff = vector<int>(I);
    for(int i = 0; i < I; i++)
        stuff.at(i) = -1;
    while(solved.size() < I) {
        for(int j = 0; j < I; j++) {
            if(stuff.at(j) != -1)
                continue;
            for(int i = 0; i < valid.size(); i += 4) {
                if(solved.count(i/4))
                    continue;
                bool b = true;
                for(int x: poss.at(j)) {
                    if((x < valid.at(i) || x > valid.at(i+1)) && (x < valid.at(i+2) || x > valid.at(i+3))) {
                        b = false;
                        break;
                    }
                }
                if(b) {
                    if(stuff.at(j) == -1) {
                        stuff.at(j) = i/4;
                    } else {
                        stuff.at(j) = -1;
                        break;
                    }
                }
            }
            if(stuff.at(j) != -1) {
                solved.insert(stuff.at(j));
            }
        }
    }

    for(int i = 0; i < I; i++) {
        if(stuff.at(i) < 6)
            ans *= your.at(i);
    }

    cout << ans << endl;
    return 0;
}

