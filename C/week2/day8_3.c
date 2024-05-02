#include <stdio.h>

// 定义枚举类型Month
typedef enum {
    January = 1,February,March,April,May,June,
    July,August,September,October,November,December
} Month;

int days_in_month(int year, Month month) {
    switch (month) {
        case January:
        case March:
        case May:
        case July:
        case August:
        case October:
        case December:
            return 31;
        case April:
        case June:
        case September:
        case November:
            return 30;
        case February:
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
                return 29;
            else
                return 28;
        default:
            return 0;
    }
}

int main() {
    Month month = June;
    int year = 2020;
    
    printf("The number of days in month %d of year %d is: %d\n", month, year, days_in_month(year, month));
    
    return 0;
}
