#include <stdio.h>

void split_time(long total_sec, int* hour, int* minute, int* second) {
    *hour = (total_sec / 3600) % 24;
    *minute = (total_sec / 60) % 60;
    *second = total_sec % 60;
}

int main() {
    long total_sec = 3602;
    int hour, minute, second;
    split_time(total_sec, &hour, &minute, &second);
    printf("时间是：%02d:%02d:%02d\n", hour, minute, second);
    
    return 0;
}
