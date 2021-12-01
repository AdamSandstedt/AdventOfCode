#include <iostream>
#include <string>
#include <set>

using namespace std;

pair<int, int> get_coords(string s);

int main() {
    long ans = 0;

    auto s = set<pair<int, int> >();
    string input;
    getline(cin, input);
    do {
        auto p = get_coords(input);
        auto it = s.find(p);
        if(it == s.end())
            s.insert(p);
        else
            s.erase(it);
        getline(cin, input);
    } while(!input.empty());

    cout << s.size() << endl;

    set<pair<int, int> > neighbors = {{2,0},{-2,0},{1,-1},{-1,-1},{1,1},{-1,1}};
    for(int day = 0; day < 100; day++) {
        auto cur = set<pair<int, int> >(s);
        auto toDo = set<pair<int, int> >(s);
        for(auto p: cur) {
            for(auto d: neighbors) {
                toDo.insert(make_pair(p.first+d.first,p.second+d.second));
            }
        }
        for(auto p: toDo) {
            int b = 0;
            for(auto d: neighbors) {
                if(cur.count(make_pair(p.first+d.first,p.second+d.second)))
                    b++;
            }
            if(cur.count(p)) {
                if(b == 0 || b > 2)
                    s.erase(p);
            } else {
                if(b == 2) {
                    s.insert(p);
                }
            }
        }
    }

    cout << s.size() << endl;
    return 0;
}

pair<int, int> get_coords(string s) {
    int x = 0, y = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s.at(i) == 'e') {
            x += 2;
        } else if(s.at(i) == 'w') {
            x -= 2;
        } else if(s.at(i) == 's') {
            if(s.at(i+1) == 'e') {
                x++;
                y--;
            } else {
                x--;
                y--;
            }
            i++;
        } else {
            if(s.at(i+1) == 'e') {
                x++;
                y++;
            } else {
                x--;
                y++;
            }
            i++;
        }
    }
    return make_pair(x,y);
}

