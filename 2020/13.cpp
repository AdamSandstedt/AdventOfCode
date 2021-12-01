#include <iostream>
#include <vector>

long mod(long a, long b);
long gcd(long a, long b);
long lcm(long a, long b);

using namespace std;

int main() {
    char input[256];
    cin.getline(input, 256);
    long earliest = atoi(input);

    vector<long> buses = vector<long>();
    vector<long> busNums = vector<long>();

    cin.getline(input, 256);
    char* l = strtok(input, ",");
    long n = -1;
    do {
        n++;
        if(l[0] == 'x')
            continue;
        buses.push_back(atoi(l));
        busNums.push_back(n);
    } while((l = strtok(NULL, ",")));

    long minTime = earliest * 100;
    long minIndex;

    for(long i = 0; i < buses.size(); i++) {
        long m = buses[i] * (earliest / buses[i] + 1);
        if(m < minTime) {
            minTime = m;
            minIndex = i;
        }
    }

    long t = buses[0];
    long dt = buses[0];
    long ci = 1;
    while(true) {
        if((t + busNums[ci]) % buses[ci] == 0) {
            dt = lcm(dt, buses[ci]);
            ci++;
            if(ci == buses.size())
                break;
        }
        t += dt;
    }

    cout << (minTime - earliest) * buses[minIndex] << endl;
    cout << t << endl;

    return 0;
}

long gcd(long a, long b) {
    if(b == 0)
        return a;
    else
        return gcd(b, a % b);
}

long lcm(long a, long b) {
    return a * b / gcd(a,b);
}

long mod(long a, long b) {
    int m = a % b;
    return m < 0 ? m + b : m;
}

