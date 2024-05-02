#include <stdio.h>
#include <string.h>

#define MAX 100

// a)     逆序输出          
int main(){
    char line[MAX];
    char c;

    int i=0;

    printf("Enter a message: ");
    while((c = getchar()) != '\n'){
        line[i] = c;
        i++;
    }
    line[i] = '\0' ;

    printf("Reversal is: ");
    for(i; i>=0; i--){
        printf("%c", line[i]);
    }

    return 0;
}


//b)用指针来追踪当前位置
// int main(){
//     char line[MAX];
//     char c;

//     char *p = line;

//     printf("Enter a message: ");
//     while((c = getchar()) != '\n'){
//         *p = c;
//         p++;
//     }
//     *p = '\0' ;

//     printf("Reversal is: ");
//     while(p != line){
//         p--;
//         printf("%c", *p);
//     }

//     return 0;
// }