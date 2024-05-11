#include <iostream>
using namespace std;

void shuffle(int arr[], int n) {
    srand(time(NULL));
    for(int i=0; i<n; i++) {
        int j = rand() % (i+1);
        swap(arr[i], arr[j]);
    }
}

int main() {
    int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    shuffle(arr, 10);

    for(auto i:arr)
        cout << i << " ";
}