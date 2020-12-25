#include <iostream>

using namespace std;

int main() {
    long cardPublic, doorPublic;
    cin >> cardPublic >> doorPublic;

    long subject = 7;
    long current = 1;
    int loop = 0;
    while(current != cardPublic && current != doorPublic) {
        current = (current * subject) % 20201227;
        loop++;
    }

    if(current == cardPublic)
        subject = doorPublic;
    else
        subject = cardPublic;
    current = 1;
    for(int i = 1; i <= loop; i++) {
        current = (current * subject) % 20201227;
    }

    cout << current << endl;
    return 0;
}

