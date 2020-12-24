#include <iostream>
#include <unordered_map>
#include <cstring>

using namespace std;

int main() {
    int ans = 0;

    char input[256];
    cin.getline(input, 256);
    char* s = strtok(input, ",");
    long x;
    long index = 1;
    unordered_map<long, long> m = unordered_map<long, long>();
    long prev;
    do {
        x = atoi(s);
        m[x] = index;
        prev = x;
        index++;
    } while((s = strtok(NULL, ",")));
    m.erase(prev);
    index--;

    for(; index < 2020; index++) {
        if(m.count(prev)) {
            long tmp = index - m[prev];
            m[prev] = index;
            prev = tmp;
        } else {
            m[prev] = index;
            prev = 0;
        }
    }

    cout << prev << endl;

    for(; index < 30000000; index++) {
        if(m.count(prev)) {
            long tmp = index - m[prev];
            m[prev] = index;
            prev = tmp;
        } else {
            m[prev] = index;
            prev = 0;
        }
        // cout << prev << endl;
    }

    cout << prev << endl;
    return 0;
}

