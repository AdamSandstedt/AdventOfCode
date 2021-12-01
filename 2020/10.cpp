#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
    int input;
    unordered_map<int, long> nums = unordered_map<int, long>();
    int max;
    while(cin >> input) {
        nums[input] = 0;
        if(input > max)
            max = input;
    }
    nums[0] = 1;
    int num = 0;
    int new_num;
    int count1 = 0;
    int count3 = 0;

    while(num < max) {
        if(nums.count(num + 1)) {
            nums[num+1] += nums[num];
            new_num = num + 1;
            count1++;
        }
        if(nums.count(num + 2)) {
            nums[num+2] += nums[num];
            if(new_num == num)
                new_num = num + 2;
        }
        if(nums.count(num + 3)) {
            nums[num+3] += nums[num];
            if(new_num == num) {
                new_num = num + 3;
                count3++;
            }
        }
        nums.erase(num);
        num = new_num;
    }
    count3++;

    cout << count1 * count3 << endl;
    cout << nums[max] << endl;
    return 0;
}

