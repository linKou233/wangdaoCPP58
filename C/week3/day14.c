#include <stdio.h>
#include <stdlib.h>
int binary_search1(int arr[], int n, int key) {
    int l = 0, r = n - 1;
	while (l <= r) {
		int mid=l+(r-l)/2;
		if (arr[mid] > key)     
            r = mid - 1;
		else                    
            l = mid + 1;
	}
	if (r<0 || arr[r] != key)
        return -1;
	
    return r;
}

int binary_search2(int arr[], int n, int key) {
    int l = 0, r = n - 1;
	while (l <= r) {
		int mid=l+(r-l)/2;
		if (arr[mid] > key)
            r = mid - 1;
		else
            l = mid + 1;
	}
	if (r < 0)
	    return -1;
	
    return r;
}

int main() {
    int arr[10] = {3, 6, 9, 12, 12, 12, 18, 43, 51, 61};

    int res = binary_search1(arr, 10, 12);      //返回的应当是数组下标5
    printf("%d\n", res);
    int res1 = binary_search1(arr, 10, 20);      //没有找到，返回-1
    printf("%d\n", res1);
    int res2 = binary_search1(arr, 10, 2);      //返回-1
    printf("%d\n", res2);
    int res3 = binary_search1(arr, 10, 61);      //返回9
    printf("%d\n", res3);

    printf("-----------------------------\n");
    int res4 = binary_search2(arr, 10, 20);      //返回的应当是数组下标6
    printf("%d\n", res4);
    int res5 = binary_search2(arr, 10, 12);      //返回5
    printf("%d\n", res5);
    int res6 = binary_search2(arr, 10, 3);      //返回0
    printf("%d\n", res6);
    int res7 = binary_search2(arr, 10, 100);      //返回9
    printf("%d\n", res7);

    return 0;
}