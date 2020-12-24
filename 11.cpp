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

int num_surrounding(const vector<string> &grid, const set<pair<int,int> > &surrounding_set);
int num_occupied(const vector<string> &grid);

int main() {
    vector<string> grid1;
    vector<string> grid2;
    string input;
    while(getline(cin, input)) {
        grid1.push_back(input);
        grid2.push_back(string(input));
    }

    auto surrounding1 = vector<vector<set<pair<int,int> > > >(grid2.size());
    auto surrounding2 = vector<vector<set<pair<int,int> > > >(grid2.size());
    set<pair<int,int> > todo1 = set<pair<int,int> >();
    set<pair<int,int> > todo2 = set<pair<int,int> >();
    for(int i = 0; i < grid2.size(); i++) {
        surrounding1[i] = vector<set<pair<int,int> > >(grid2[0].size());
        surrounding2[i] = vector<set<pair<int,int> > >(grid2[0].size());
        for(int j = 0; j < grid2[0].size(); j++) {
            surrounding1[i][j] = set<pair<int,int> >();
            surrounding2[i][j] = set<pair<int,int> >();
        }
    }
    for(int i = 0; i < grid2.size(); i++) {
        for(int j = 0; j < grid2[0].size(); j++) {
            if(grid2[i][j] == '.')
                continue;
            todo1.insert(pair<int,int>(i,j));
            todo2.insert(pair<int,int>(i,j));
            int y = i+1;
            int x = j;
            if(grid2[y][x] == 'L')
                surrounding1[i][j].insert(pair<int,int>(y,x));
            while(y < grid2.size()) {
                if(grid2[y][x] == 'L') {
                    surrounding2[i][j].insert(pair<int,int>(y,x));
                    break;
                }
                y++;
            }
            y = i-1;
            if(grid2[y][x] == 'L')
                surrounding1[i][j].insert(pair<int,int>(y,x));
            while(y >= 0) {
                if(grid2[y][x] == 'L') {
                    surrounding2[i][j].insert(pair<int,int>(y,x));
                    break;
                }
                y--;
            }
            y = i;
            x = j+1;
            if(grid2[y][x] == 'L')
                surrounding1[i][j].insert(pair<int,int>(y,x));
            while(x < grid2[0].size()) {
                if(grid2[y][x] == 'L') {
                    surrounding2[i][j].insert(pair<int,int>(y,x));
                    break;
                }
                x++;
            }
            x = j-1;
            if(grid2[y][x] == 'L')
                surrounding1[i][j].insert(pair<int,int>(y,x));
            while(x >= 0) {
                if(grid2[y][x] == 'L') {
                    surrounding2[i][j].insert(pair<int,int>(y,x));
                    break;
                }
                x--;
            }
            y = i+1;
            x = j+1;
            if(grid2[y][x] == 'L')
                surrounding1[i][j].insert(pair<int,int>(y,x));
            while(y < grid2.size() && x < grid2[0].size()) {
                if(grid2[y][x] == 'L') {
                    surrounding2[i][j].insert(pair<int,int>(y,x));
                    break;
                }
                y++;
                x++;
            }
            y = i+1;
            x = j-1;
            if(grid2[y][x] == 'L')
                surrounding1[i][j].insert(pair<int,int>(y,x));
            while(y < grid2.size() && x >= 0) {
                if(grid2[y][x] == 'L') {
                    surrounding2[i][j].insert(pair<int,int>(y,x));
                    break;
                }
                y++;
                x--;
            }
            y = i-1;
            x = j+1;
            if(grid2[y][x] == 'L')
                surrounding1[i][j].insert(pair<int,int>(y,x));
            while(y >= 0 && x < grid2[0].size()) {
                if(grid2[y][x] == 'L') {
                    surrounding2[i][j].insert(pair<int,int>(y,x));
                    break;
                }
                y--;
                x++;
            }
            y = i-1;
            x = j-1;
            if(grid2[y][x] == 'L')
                surrounding1[i][j].insert(pair<int,int>(y,x));
            while(y >= 0 && x >= 0) {
                if(grid2[y][x] == 'L') {
                    surrounding2[i][j].insert(pair<int,int>(y,x));
                    break;
                }
                y--;
                x--;
            }
        }
    }

    bool gridupdated;
    do {
        gridupdated = false;
        vector<string> tmp = vector<string>(grid1);
        for(auto it = todo1.begin(); it != todo1.end();) {
            int i = it->first;
            int j = it->second;
            int s = num_surrounding(tmp, surrounding1[i][j]);
            if(tmp[i][j] == 'L' && s == 0) {
                grid1[i][j] = '#';
                gridupdated = true;
                it++;
            } else if(tmp[i][j] == '#' && s > 3) {
                grid1[i][j] = 'L';
                gridupdated = true;
                it++;
            } else {
//                 it = todo1.erase(it);
                it++;
            }
        }
//         for(int i = 0; i < grid2.size(); i++)
//             cout << grid2[i] << endl;
//         cout << endl;
    } while(gridupdated);

    do {
        gridupdated = false;
        vector<string> tmp = vector<string>(grid2);
        for(auto it = todo2.begin(); it != todo2.end();) {
            int i = it->first;
            int j = it->second;
            int s = num_surrounding(tmp, surrounding2[i][j]);
            if(tmp[i][j] == 'L' && s == 0) {
                grid2[i][j] = '#';
                gridupdated = true;
                it++;
            } else if(tmp[i][j] == '#' && s > 4) {
                grid2[i][j] = 'L';
                gridupdated = true;
                it++;
            } else {
//                 it = todo2.erase(it);
                it++;
            }
        }
//         for(int i = 0; i < grid2.size(); i++)
//             cout << grid2[i] << endl;
//         cout << endl;
    } while(gridupdated);

    cout << num_occupied(grid1) << endl;
    cout << num_occupied(grid2) << endl;

    return 0;
}

int num_surrounding(const vector<string> &grid, const set<pair<int,int> > &surrounding_set) {
    int count = 0;
    for(pair<int,int> p: surrounding_set) {
        if(grid[p.first][p.second] == '#') count++;
    }
    return count;
}

int num_occupied(const vector<string> &grid) {
    int count = 0;
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[i].size(); j++) {
            if(grid[i][j] == '#') count++;
        }
    }
    return count;
}
