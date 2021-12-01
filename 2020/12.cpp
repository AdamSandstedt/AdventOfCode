#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() {
    long x1 = 0;
    long y1 = 0;
    long x = 0;
    long y = 0;
    long dx = 10;
    long dy = 1;
    int dir = 0;

    string input;
    char instr;
    while(getline(cin, input)) {
        char instr = input[0];
        int num = stoi(input.substr(1));
        int tmp;
        switch(instr) {
            case 'N':
                dy += num;
                y1 += num;
                break;
            case 'S':
                dy -= num;
                y1 -= num;
                break;
            case 'E':
                dx += num;
                x1 += num;
                break;
            case 'W':
                dx -= num;
                x1 -= num;
                break;

            case 'L':
                switch(num/90) {
                    case 1:
                        tmp = dx;
                        dx = -dy;
                        dy = tmp;
                        break;
                    case 2:
                        dx = -dx;
                        dy = -dy;
                        break;
                    case 3:
                        tmp = -dx;
                        dx = dy;
                        dy = tmp;
                        break;
                }
                dir = (dir + num/90) % 4;
                break;

            case 'R':
                switch(num/90) {
                    case 3:
                        tmp = dx;
                        dx = -dy;
                        dy = tmp;
                        break;
                    case 2:
                        dx = -dx;
                        dy = -dy;
                        break;
                    case 1:
                        tmp = -dx;
                        dx = dy;
                        dy = tmp;
                        break;
                }
                dir = (dir - num/90 + 4) % 4;
                break;

            case 'F':
                x += dx*num;
                y += dy*num;
                switch(dir) {
                    case 0:
                        x1 += num;
                        break;
                    case 1:
                        y1 += num;
                        break;
                    case 2:
                        x1 -= num;
                        break;
                    case 3:
                        y1 -= num;
                        break;
                }
                break;
        }
    }

    cout << abs(x1) + abs(y1) << endl;
    cout << abs(x) + abs(y) << endl;
    return 0;
}

