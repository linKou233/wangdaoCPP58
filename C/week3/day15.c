#include <stdio.h>

//  选择排序
void selection_sort(int arr[], int n) {
    int i, j, min, temp;
    for (i = 0; i < n-1; i++) {
        min = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min])
                min = j;
        }
        temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}

//冒泡排序
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

//插入排序
void insertion_sort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


int main() {
    int arr[10] = {11, 9, 18, 7, 23, 35, 46, 51, 31, 28};
    
    //selection_sort(arr, 10);
    //bubble_sort(arr, 10);
    insertion_sort(arr, 10);
    
    for(int i=0; i<10; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
