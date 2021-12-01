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

#include "split.h"

using namespace std;

int main() {
    long ans1 = 0;
    long ans2 = 0;

    string input;
    while(getline(cin, input)) {
        vector<string> expr1 = vector<string>();
        vector<string> expr2 = vector<string>();
        auto v = split_strip(input, {" "});
        v.back() += ")";
        int par = v.at(0).find_first_not_of("(");
        if(par != string::npos)
            v.at(0) = v.at(0).substr(par);
        expr1.push_back("(");
        expr1.push_back(v.at(0));
        expr2.push_back("(");
        expr2.push_back(v.at(0));
        for(int i = 1; i < v.size(); i += 2) {
            expr1.push_back(v.at(i));
            expr2.push_back(v.at(i));
            if(v.at(i+1).find("(") != string::npos) {
                par = v.at(i+1).find_first_not_of("(");
                for(int j = 0; j < par; j++) {
                    expr1.push_back("(");
                    expr2.push_back("(");
                }
                v.at(i+1) = v.at(i+1).substr(par);
                par = 0;
            } else if(v.at(i+1).find(")") != string::npos) {
                par = v.at(i+1).size() - v.at(i+1).find(")");
                v.at(i+1) = v.at(i+1).substr(0,v.at(i+1).size() - par);
            } else {
                par = 0;
            }
            expr1.push_back(v.at(i+1));
            expr2.push_back(v.at(i+1));
            int par2 = par;

            while(expr1.size() > 2) {
                if(expr1.at(expr1.size() - 2) == "(") {
                    if(par == 0)
                        break;
                    expr1.erase(expr1.end()-2);
                    par--;
                    continue;
                }
                long x1 = stol(expr1.at(expr1.size()-3));
                string op = expr1.at(expr1.size()-2);
                long x2 = stol(expr1.at(expr1.size()-1));
                expr1.pop_back();
                expr1.pop_back();
                if(op == "+") {
                    expr1.back() = to_string(x1 + x2);
                } else if(op == "*") {
                    expr1.back() = to_string(x1 * x2);
                }
            }

            while(expr2.size() > 3) {
                if(expr2.at(expr2.size() - 2) == "(") {
                    if(par2 == 0)
                        break;
                    expr2.erase(expr2.end()-2);
                    par2--;
                    continue;
                }
                if(expr2.at(expr2.size() - 2) == "*") {
                    if(par2 == 0)
                        break;
                }
                long x1 = stol(expr2.at(expr2.size()-3));
                string op = expr2.at(expr2.size()-2);
                long x2 = stol(expr2.at(expr2.size()-1));
                expr2.pop_back();
                expr2.pop_back();
                if(op == "+") {
                    expr2.back() = to_string(x1 + x2);
                } else if(op == "*") {
                    expr2.back() = to_string(x1 * x2);
                }
            }
        }
        ans1 += stol(expr1.back());
        ans2 += stol(expr2.back());
    }

    cout << ans1 << endl;
    cout << ans2 << endl;
    return 0;
}

