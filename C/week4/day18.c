//
#include <stdio.h>

// 函数用于左旋转数组
void rotateLeft(int arr[], int n, int k) {
    int temp[n];

    for (int i = 0; i < n; i++) {
        temp[(i + n - k) % n] = arr[i];
    }
    for (int i = 0; i < n; i++) {
        arr[i] = temp[i];
    }
}

int main() {
    int arr[] = {0, 1,2,3,4,5,6,7,8};
    rotateLeft(arr, 9, 10);
    for(int i=0; i<9; i++){
        printf("%d ", arr[i]);
    }

    return 0;
}