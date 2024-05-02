#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100

// a)检查回文
// int main(){
//     char msg[MAX];
//     char c;

//     int front=0, rear;
    
//     printf("Enter a message: ");
//     while( (c=getchar()) != '\n' ){
//         msg[front] = c;
//         front++;
//     }
//     msg[front] = '\0';
//     rear = front-1;

//     int flag = 0;       //flag为0表示比较的两个字母相等
//     front = 0;          //将front置为0
//     while(front != rear){
//         while( 0 == isalpha(msg[front]) )   //msg[front]不为字母
//             front++;
//         while( 0 == isalpha(msg[rear]) )
//             rear--;
//         if( (msg[front] - msg[rear] != 32) && (msg[front] - msg[rear] != -32) && (msg[front] - msg[rear] != 0)){
//             flag = 1;
//             break;
//         }
//         if(front == rear)
//             break;
//         front++, rear--;
//     }

//     if(flag != 0)
//         printf("Not a palindrome");
//     else
//         printf("Palindrome");

//     return 0;
// }

// b)   改用指针追踪
int main(){
    char msg[MAX];
    char c;

    char  *front=msg, *rear = NULL;
    
    printf("Enter a message: ");
    while( (c=getchar()) != '\n' ){
        *front = c;
        front++;
    }
    *front = '\0';
    rear = front-1;

    int flag = 0;       //flag为0表示比较的两个字母相等
    front = msg;          //将front置为到数组首地址
    while(front != rear){
        while( 0 == isalpha(*front) )   //msg[front]不为字母
            front++;
        while( 0 == isalpha(*rear) )
            rear--;
        if( (*front - *rear != 32) && (*front - *rear != -32) && ( *front - *rear != 0)){
            flag = 1;
            break;
        }
        if(front == rear)
            break;
        front++, rear--;
    }

    if(flag != 0)
        printf("Not a palindrome");
    else
        printf("Palindrome");

    return 0;
}