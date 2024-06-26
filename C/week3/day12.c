#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

void remove_duplicate_and_sort(char* str) {
    if (str == NULL) {
        printf("ERROR，the string is null, please input again!");
        exit(1);
    }

    // 用于记录每个字母出现的次数
    int count[26] = {0};
    for (int i = 0; str[i]; i++) {
        count[str[i] - 'a']++;
    }
    
    // 用于记录当前写入的位置
    int pos = 0;
    for (int i = 0; i < 26; i++) {
        if (count[i] > 0) {
            str[pos++] = 'a' + i;
        }
    }
    str[pos] = '\0';
}

int main() {
    char str[MAX]; 
    printf("please input the string that you want to resort");
    scanf("%s", &str);
    remove_duplicate_and_sort(str);
    printf("%s", str);

    return 0;
}