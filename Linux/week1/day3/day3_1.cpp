#include <iostream>
#include <algorithm>
using namespace std;

int find_kth_minimum(int arr[], int n, int k) {
    sort(arr, arr+n);
    return arr[k-1];
}
int find_median(int arr[], int n) {
    sort(arr, arr+n);
    if(n % 2 == 0)
        return arr[n/2-1];
    else
        return arr[n/2];
}

int main() {
    int arr1[] = {3, 6, 8, 9, 21, 1, 0};
    int arr2[] = {4, 1, 3, 2, 5};
    int arr3[] = {4,1,3,2};
    cout << find_kth_minimum(arr1, 7, 2) << endl;
    cout << find_median(arr2, 5) << endl;
    cout << find_median(arr3, 4) << endl;
    return 0;
}