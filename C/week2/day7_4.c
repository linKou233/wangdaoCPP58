#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 20

int main(){

    char smallest_word[MAX];
    char largest_word[MAX];
    char c[MAX];
    int length=0;
    
    printf("Enter word: ");
    scanf("%s", &c);
    strcpy(smallest_word, c);
    strcpy(largest_word, c);
    
    do
    {
        printf("Enter word: ");
        scanf("%s", &c);

        if(strcmp(c, smallest_word) <= 0)
            strcpy(smallest_word, c);
        if(strcmp(c, largest_word) >= 0)
            strcpy(largest_word, c);
        length = strlen(c);
    } while ( length != 4);

    printf("Smallest word: %s\n", smallest_word);
    printf("Largest word: %s", largest_word);

    return 0;
}