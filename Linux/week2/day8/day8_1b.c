#include <func.h>
int main(int argc, char* argv[])
{
    for (int i = 0; i < 3; i++) {
        printf("a+%d", i);
        fork();
    } 
    return 0;
}