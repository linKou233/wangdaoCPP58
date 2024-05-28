// (a) 判断一个整数是不是丑数 (质因素只包含2, 3, 5的整数，比如：2， 3， 4， 5， 6， 8，9，10，...)

// bool isUglyNumber(long long n);
// (b) (拓展题，不要求每个同学都做) 生成前 n 个丑数。

// long long* generateUglyNumbers(int n);
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isUglyNumber(long long n) {
    while(n % 2 == 0)   n = n/2;
    while(n%3 == 0)     n = n/3;
    while(n%5 == 0)     n = n/5;
    if(n == 1)          return true;
    else                return false;
}
long long* generateUglyNumbers(int n) {
    vector<long long> uglyNumbers(n);
    uglyNumbers[0] = 1;
    
    int total=n;
    total = total-1;

    int j=1;
    for(int i=2; total>0 ; i++){
        if(isUglyNumber(i)){
            uglyNumbers[j] = i;
            j++;
            total--;
        }
    }

    long long* uglyArray = new long long[n];
    for (int i = 0; i < n; i++) {
        uglyArray[i] = uglyNumbers[i];
    }

    return uglyArray;
}

int main() {
    long long number;
    cout << "Please input the number you want to judge: ";
    cin >> number;
    if(isUglyNumber(number))
        cout << number << " is a uglyNumber" << endl;
    else
        cout << number << " is not a uglyNumber" << endl;
    ////////                 b题           /////////
    int n;
    cout << "Please input the number you want to generate: ";
    cin >> n;
    long long* res = generateUglyNumbers(n);
    
    for(int i=0; i<n; i++){
        cout << res[i] << " ";
    }
    delete []res;

    return 0;
}