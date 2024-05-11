#include <iostream>
#include <algorithm>
using namespace std;

int q[] ={2, 7, 9, 31, 27, 22, 56, 43, 39, 17};

//快排
void quick_sort(int q[], int l, int r) {
    if (l >= r) return;

    int i = l - 1, j = r + 1, x = q[l + r >> 1];
    while (i < j)
    {
        do i ++ ; while (q[i] < x);
        do j -- ; while (q[j] > x);
        if (i < j)
            swap(q[i], q[j]);
    }
    quick_sort(q, l, j), quick_sort(q, j + 1, r);
}
void quick_sort(int arr[], int n){
    quick_sort(arr, 0, n-1);
    for(auto x: q)
        cout << x << " ";
}

//归并排序
int n;
int *tmp = new int[n];

void merge_sort(int q[], int l, int r)
{
    if (l >= r) return;

    int mid = l + r >> 1;
    merge_sort(q, l, mid);
    merge_sort(q, mid + 1, r);

    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)
        if (q[i] <= q[j]) tmp[k ++ ] = q[i ++ ];
        else tmp[k ++ ] = q[j ++ ];

    while (i <= mid) tmp[k ++ ] = q[i ++ ];
    while (j <= r) tmp[k ++ ] = q[j ++ ];

    for (i = l, j = 0; i <= r; i ++, j ++ )
        q[i] = tmp[j];
}
void merge_sort(int arr[], int n) {
    merge_sort(arr, 0, n-1);
    for(auto x: q)
        cout << x << " ";
    delete tmp;
}

int main() {
    //quick_sort(q, 10);
    merge_sort(q, 10);
}