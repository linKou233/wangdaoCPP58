#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100

void remove_filename(char* url){
    char *rear = url;

    while(*rear != '\0'){
        rear++;
    }       //定位到字符串最后
    while(1){
        if(*rear == '/')
        {
            *rear = '\0';
            break;
        }
        rear--;      
    }
    while(url <= rear){
        printf("%c", *url);
        url++;
    }
}

int main(){

    char URL[] = "http://www.knking.com/index.html";

    remove_filename(URL);

    return 0;
}