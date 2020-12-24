#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

int main() {
    string input;
    int y = 0;
    set<vector<int> > active3 = set<vector<int> >();
    set<vector<int> > active4 = set<vector<int> >();
    while(getline(cin, input)) {
        for(int x = 0; x < input.size(); x++) {
            if(input.at(x) == '#') {
                active3.insert(vector<int>({x,y,0}));
                active4.insert(vector<int>({x,y,0,0}));
            }
        }
        y++;
    }

    for(int cycle = 1; cycle <= 6; cycle++) {
        set<vector<int> > toUpdate = set<vector<int> >();
        for(auto v: active3) {
            for(int dx = -1; dx <= 1; dx++) {
                for(int dy = -1; dy <= 1; dy++) {
                    for(int dz = -1; dz <= 1; dz++) {
                        toUpdate.insert(vector<int>({v.at(0)+dx,v.at(1)+dy,v.at(2)+dz}));
                    }
                }
            }
        }
        set<vector<int> > newActive = set<vector<int> >();
        for(auto v: active3) {
            int count = -1;
            for(int dx = -1; dx <= 1; dx++) {
                for(int dy = -1; dy <= 1; dy++) {
                    for(int dz = -1; dz <= 1; dz++) {
                        if(active3.count(vector<int>({v.at(0)+dx,v.at(1)+dy,v.at(2)+dz})))
                            count++;
                    }
                }
            }
            if(count == 2 || count == 3)
                newActive.insert(v);
        }
        for(auto v: toUpdate) {
            if(active3.count(v))
                continue;
            int count = 0;
            for(int dx = -1; dx <= 1; dx++) {
                for(int dy = -1; dy <= 1; dy++) {
                    for(int dz = -1; dz <= 1; dz++) {
                        if(dx == 0 && dy == 0 && dz == 0)
                            continue;
                        if(active3.count(vector<int>({v.at(0)+dx,v.at(1)+dy,v.at(2)+dz})))
                            count++;
                    }
                }
            }
            if(count == 3)
                newActive.insert(v);
        }
        active3 = newActive;

//         vector<int> mins = vector<int>(3);
//         for(int i = 0; i < 3; i++)
//             mins.at(i) = 999999;
//         vector<int> maxs = vector<int>(3);
//         for(int i = 0; i < 3; i++)
//             maxs.at(i) = -999999;
//         for(auto v: active3) {
//             for(int i = 0; i < 3; i ++) {
//                 if(v.at(i) < mins.at(i))
//                     mins.at(i) = v.at(i);
//                 if(v.at(i) > maxs.at(i))
//                     maxs.at(i) = v.at(i);
//             }
//         }
//         cout << mins.at(0) << " " << maxs.at(0) << endl;
//         cout << mins.at(1) << " " << maxs.at(1) << endl;
//         cout << mins.at(2) << " " << maxs.at(2) << endl;
//         cout << "After " << cycle << " cycle(s):" << endl;
//         for(int z = mins.at(2); z <= maxs.at(2); z++) {
//             cout << "z=" << z << endl;
//             for(int y = mins.at(1); y <= maxs.at(1); y++) {
//                 for(int x = mins.at(0); x <= maxs.at(0); x++) {
//                     if(active3.count(vector<int>({x,y,z})))
//                         cout << "#";
//                     else
//                         cout << ".";
//                 }
//                 cout << endl;
//             }
//             cout << endl;
//         }

    }
    cout << active3.size() << endl;

    for(int cycle = 1; cycle <= 6; cycle++) {
        set<vector<int> > toUpdate = set<vector<int> >();
        for(auto v: active4) {
            for(int dx = -1; dx <= 1; dx++) {
                for(int dy = -1; dy <= 1; dy++) {
                    for(int dz = -1; dz <= 1; dz++) {
                        for(int dw = -1; dw <= 1; dw++) {
                            toUpdate.insert(vector<int>({v.at(0)+dx,v.at(1)+dy,v.at(2)+dz,v.at(3)+dw}));
                        }
                    }
                }
            }
        }
        set<vector<int> > newActive = set<vector<int> >();
        for(auto v: active4) {
            int count = -1;
            for(int dx = -1; dx <= 1; dx++) {
                for(int dy = -1; dy <= 1; dy++) {
                    for(int dz = -1; dz <= 1; dz++) {
                        for(int dw = -1; dw <= 1; dw++) {
                            if(active4.count(vector<int>({v.at(0)+dx,v.at(1)+dy,v.at(2)+dz,v.at(3)+dw})))
                                count++;
                        }
                    }
                }
            }
            if(count == 2 || count == 3)
                newActive.insert(v);
        }
        for(auto v: toUpdate) {
            if(active4.count(v))
                continue;
            int count = 0;
            for(int dx = -1; dx <= 1; dx++) {
                for(int dy = -1; dy <= 1; dy++) {
                    for(int dz = -1; dz <= 1; dz++) {
                        for(int dw = -1; dw <= 1; dw++) {
                            if(dx == 0 && dy == 0 && dz == 0 && dw == 0)
                                continue;
                            if(active4.count(vector<int>({v.at(0)+dx,v.at(1)+dy,v.at(2)+dz,v.at(3)+dw})))
                                count++;
                        }
                    }
                }
            }
            if(count == 3)
                newActive.insert(v);
        }
        active4 = newActive;
    }
    cout << active4.size() << endl;

    return 0;
}

