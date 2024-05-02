#include <stdio.h>

void find_two_largest(int arr[], int n, int* largest, int* second_largest) {
    *largest = *second_largest = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > *largest) {
            *second_largest = *largest;
            *largest = arr[i];
        } 
        else if (arr[i] > *second_largest && arr[i] != *largest) {
            *second_largest = arr[i];
        }
    }
}

int main() {
    int arr[] = {10, 2, 4, 45, 6, 89, 7}; 
    int n = sizeof(arr) / sizeof(arr[0]);
    int largest, second_largest;
    
    find_two_largest(arr, n, &largest, &second_largest);
    printf("数组中最大的元素是：%d\n", largest);
    printf("数组中第二大的元素是：%d\n", second_largest);
    
    return 0;
}
