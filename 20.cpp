#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>

#include "split.h"

using namespace std;

vector<long> rotate(vector<long> &tile);
vector<string > rotate_tile(vector<string > &tile);
vector<long> flip(vector<long> &tile, bool dir);
vector<string > flip_tile(vector<string > &tile, bool dir);
long flip_edge(long id);

const int N = 10;

int main() {
    long ans = 1;

    auto tiles = map<long, vector<string> >();
    string input;
    while(getline(cin, input)) {
        long id = stol(split_str(input, {" ", ":"}).at(1));
        auto tile = vector<string>(N);
        for(int i = 0; i < N; i++) {
            getline(cin, input);
            tile.at(i) = string(N, '0');
            for(int j = 0; j < N; j++)
                tile.at(i).at(j) = input.at(j) == '#' ? '1' : '0';
        }
        tiles[id] = tile;
        getline(cin, input);
    }

    auto edges = unordered_map<int, set<long> >();
    auto tileEdges = unordered_map<long, vector<long> >();
    for(auto p: tiles) {
        auto v = vector<long>(4);
        int n1 = bitset<N>(p.second.at(0)).to_ulong();
        v.at(0) = n1;
        int n2 = flip_edge(n1);
        int n = min(n1, n2);
        if(!edges.count(n))
            edges[n] = set<long>();
        edges[n].insert(p.first);
        n1 = bitset<N>(p.second.at(N-1)).to_ulong();
        v.at(1) = n1;
        n2 = flip_edge(n1);
        n = min(n1, n2);
        if(!edges.count(n))
            edges[n] = set<long>();
        edges[n].insert(p.first);
        auto b = bitset<N>();
        for(int i = 0; i < N; i++)
            b[N-1-i] = p.second.at(i)[0] == '1';
        n1 = b.to_ulong();
        v.at(2) = n1;
        n2 = flip_edge(n1);
        n = min(n1, n2);
        if(!edges.count(n))
            edges[n] = set<long>();
        edges[n].insert(p.first);
        for(int i = 0; i < N; i++)
            b[N-1-i] = p.second.at(i)[N-1] == '1';
        n1 = b.to_ulong();
        v.at(3) = n1;
        n2 = flip_edge(n1);
        n = min(n1, n2);
        if(!edges.count(n))
            edges[n] = set<long>();
        edges[n].insert(p.first);
        tileEdges[p.first] = v;
    }

    auto counts = map<long, int>();
    for(auto p: edges) {
        if(p.second.size() == 1) {
            counts[*p.second.begin()]++;
//             if(counts[*p.second.begin()] == 2)
//                 cout << p.first << endl;
        }
//         cout << p.first;
//         for(auto x: p.second)
//             cout << " " << x;
//         cout << endl;
    }
//     cout << endl;
//     for(auto p: counts)
//         cout << p.first << ": " << p.second << endl;
//     cout << endl;
    const int I = sqrt(tiles.size());

    long startId;
    for(auto p: counts) {
        if(p.second == 2) {
            ans *= p.first;
            startId = p.first;
        }
    }
    cout << ans << endl;

    auto grid = vector<vector<long> >(I);
    for(int i = 0; i < I; i++)
        grid.at(i) = vector<long>(I);

    while(true) {
        bool valid = true;
        if(!edges.count(tileEdges[startId].at(0))) {
            if(edges[flip_edge(tileEdges[startId].at(0))].size() != 1) {
                valid = false;
            }
        } else {
            if(edges[tileEdges[startId].at(0)].size() != 1) {
                valid = false;
            }
        }
        if(!edges.count(tileEdges[startId].at(2))) {
            if(edges[flip_edge(tileEdges[startId].at(2))].size() != 1) {
                valid = false;
            }
        } else {
            if(edges[tileEdges[startId].at(2)].size() != 1) {
                valid = false;
            }
        }
        if(valid)
            break;
        tileEdges[startId] = rotate(tileEdges[startId]);
        tiles[startId] = rotate_tile(tiles[startId]);
    }
    grid.at(0).at(0) = startId;
    for(long x: tileEdges[startId]) {
        if(edges.count(x))
            edges[x].erase(startId);
        else
            edges[flip_edge(x)].erase(startId);
    }

    int i = 0;
    for(int j = 1; j < I; j++) {
        long edge = tileEdges[grid.at(0).at(j-1)].at(3);
        long next;
        if(!edges.count(edge)) {
            next = *edges[flip_edge(edge)].begin();
        } else {
            next = *edges[edge].begin();
        }
        auto v = tileEdges[next];
        if(find(v.begin(), v.end(), edge) == v.end()) {
            edge = flip_edge(edge);
        }
        int k = 0;
        for(; k < 4; k++) {
            if(v.at(k) == edge)
                break;
        }
        if(k == 0) {
            v = rotate(v);
            tiles[next] = rotate_tile(tiles[next]);
        } else if(k == 1) {
            v = rotate(v);
            v = rotate(v);
            v = rotate(v);
            tiles[next] = rotate_tile(tiles[next]);
            tiles[next] = rotate_tile(tiles[next]);
            tiles[next] = rotate_tile(tiles[next]);
        } else if(k == 3) {
            v = rotate(v);
            v = rotate(v);
            tiles[next] = rotate_tile(tiles[next]);
            tiles[next] = rotate_tile(tiles[next]);
        }
        if(v.at(2) != tileEdges[grid.at(0).at(j-1)].at(3)) {
            v = flip(v, true);
            tiles[next] = flip_tile(tiles[next], true);
        }
        tileEdges[next] = v;
        grid.at(i).at(j) = next;
        for(long x: tileEdges[next]) {
            if(edges.count(x))
                edges[x].erase(next);
            else
                edges[flip_edge(x)].erase(next);
        }
    }

    for(i = 1; i < I; i++) {
        for(int j = 0; j < I; j++) {
            long edge = tileEdges[grid.at(i-1).at(j)].at(1);
            long next;
            if(!edges.count(edge)) {
                next = *edges[flip_edge(edge)].begin();
            } else {
                next = *edges[edge].begin();
            }
            auto v = tileEdges[next];
            if(find(v.begin(), v.end(), edge) == v.end()) {
                edge = flip_edge(edge);
            }
            int k = 0;
            for(; k < 4; k++) {
                if(v.at(k) == edge)
                    break;
            }
            if(k == 3) {
                v = rotate(v);
                tiles[next] = rotate_tile(tiles[next]);
            } else if(k == 2) {
                v = rotate(v);
                v = rotate(v);
                v = rotate(v);
                tiles[next] = rotate_tile(tiles[next]);
                tiles[next] = rotate_tile(tiles[next]);
                tiles[next] = rotate_tile(tiles[next]);
            } else if(k == 1) {
                v = rotate(v);
                v = rotate(v);
                tiles[next] = rotate_tile(tiles[next]);
                tiles[next] = rotate_tile(tiles[next]);
            }
            if(v.at(0) != tileEdges[grid.at(i-1).at(j)].at(1)) {
                v = flip(v, false);
                tiles[next] = flip_tile(tiles[next], false);
            }
            tileEdges[next] = v;
            grid.at(i).at(j) = next;
            for(long x: tileEdges[next]) {
                if(edges.count(x))
                    edges[x].erase(next);
                else
                    edges[flip_edge(x)].erase(next);
            }
        }
    }

//     for(int k = 0; k < I; k++) {
//         for(int i = 0; i < N; i++) {
//             for(int j = 0; j < I; j++) {
//                 cout << tiles[grid[k][j]][i] << " ";
//             }
//             cout << endl;
//         }
//         cout << endl;
//     }

    const int nsize = (N-2)*I;
    auto ngrid = vector<string>(nsize);
    for(int i = 0; i < nsize; i++)
        ngrid[i] = string(nsize, '0');
    for(int k = 0; k < I; k++) {
        for(int i = 1; i < N-1; i++) {
            for(int j = 0; j < I; j++) {
                for(int l = 1; l < N-1; l++) {
                    ngrid[(N-2)*k+i-1][(N-2)*j+l-1] = tiles[grid[k][j]][i][l];
                }
            }
        }
    }

//     for(int i = 0; i < nsize; i++)
//         cout << ngrid[i] << endl;
//     cout << endl;

    set<pair<int, int> > monster = {{0,18},{1,0},{1,5},{1,6},{1,11},{1,12},{1,17},{1,18},{1,19},{2,1},{2,4},{2,7},{2,10},{2,13},{2,16}};
    int count = 0;
    while(count == 0) {
        for(int i = 0; i < nsize-2; i++) {
            for(int j = 0; j < nsize-19; j++) {
                bool all = true;
                for(auto p: monster) {
                    if(ngrid[i+p.first][j+p.second] != '1') {
                        all = false;
                        break;
                    }
                }
                if(all) {
                    count -= monster.size();
                }
            }
        }
        if(count != 0)
            break;
        ngrid = flip_tile(ngrid, true);
        for(int i = 0; i < nsize-2; i++) {
            for(int j = 0; j < nsize-19; j++) {
                bool all = true;
                for(auto p: monster) {
                    if(ngrid[i+p.first][j+p.second] != '1') {
                        all = false;
                        break;
                    }
                }
                if(all) {
                    count -= monster.size();
                }
            }
        }
        ngrid = flip_tile(ngrid, true);
        ngrid = rotate_tile(ngrid);
    }
    for(int i = 0; i < nsize; i++) {
        for(int j = 0; j < nsize; j++) {
            if(ngrid[i][j] == '1')
                count++;
        }
    }

    cout << count << endl;

    return 0;
}

vector<long> rotate(vector<long> &tile) {
    auto ntile = vector<long>(4);
    ntile.at(0) = tile.at(3);
    ntile.at(1) = tile.at(2);
    ntile.at(2) = flip_edge(tile.at(0));
    ntile.at(3) = flip_edge(tile.at(1));
    return ntile;
}

vector<string> rotate_tile(vector<string> &tile) {
    auto ntile = vector<string>(tile.size());
    for(int i = 0; i < tile.size(); i++)
        ntile[i] = string(tile.size(), '0');
    for(int i = 0; i < tile.size(); i++) {
        for(int j = 0; j < tile.size(); j++) {
            ntile[i][j] = tile[j][tile.size()-1-i];
        }
    }
    return ntile;
}

vector<long> flip(vector<long> &tile, bool dir) {
    auto ntile = vector<long>(4);
    if(dir) {
        ntile.at(0) = tile.at(1);
        ntile.at(1) = tile.at(0);
        ntile.at(2) = flip_edge(tile.at(2));
        ntile.at(3) = flip_edge(tile.at(3));
    } else {
        ntile.at(2) = tile.at(3);
        ntile.at(3) = tile.at(2);
        ntile.at(0) = flip_edge(tile.at(0));
        ntile.at(1) = flip_edge(tile.at(1));
    }
    return ntile;
}

vector<string > flip_tile(vector<string > &tile, bool dir) {
    auto ntile = vector<string >(tile.size());
    for(int i = 0; i < tile.size(); i++)
        ntile[i] = string(tile.size(), '0');
    if(dir) {
        for(int i = 0; i < tile.size(); i++)
            ntile[i] = tile[tile.size()-1-i];
    } else {
        for(int i = 0; i < tile.size(); i++)
            for(int j = 0; j < tile.size(); j++)
                ntile[i][j] = tile[i][tile.size()-1-j];
    }
    return ntile;
}

long flip_edge(long id) {
    long n = 0;
    for(int i = 0; i < 10; i++) {
        n += (id & 1) << (N-1-i);
        id >>= 1;
    }
    return n;
}

