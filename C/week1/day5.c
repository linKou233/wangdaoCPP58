#include <stdio.h>

/*
课堂练习 判断素数

void solve(int num){
    int flag=0;
    
    if(num >0 && num <4)
        printf("%d is prime", num);
    else{
        for(int i=2; i<num; i++){
            if(num % i ==0){
                flag = 1;
                break;
            }
        }
        if(flag == 1){
            printf("Not prime");
        }
        else
            printf("%d is prime", num);
    }
}

int main(){

    int num;
    
    printf("Enter a number:");
    scanf("%d", &num);
    solve(num);

    return 0;
}
*/


// 2c)

// long long next_fib(void) {
//     static long a=0;
//     static long b=1;

//     long long t = a + b;

//     a = b;
//     b = t;

//     return a;
// }

// int main(void) {
// 	// foo();	// Fibnacii: 0, 1, 1, 2, 3, 5, 8, 13, 21, ...
// 	printf("next_fib() = %lld\n", next_fib());	// 1
// 	printf("next_fib() = %lld\n", next_fib());	// 1
// 	printf("next_fib() = %lld\n", next_fib());	// 2
// 	printf("next_fib() = %lld\n", next_fib());	// 3
// 	printf("next_fib() = %lld\n", next_fib());	// 5
// 	return 0;
// }

// 3)
void hanoi(int n, char A, char B, char C) {
    if (n == 1) {
        printf("%c->%c\n", A, C);
    } else {
        hanoi(n - 1, A, C, B);
        printf("%c->%c\n", A, C);
        hanoi(n - 1, B, A, C);
    }
}

int main() {
    int num;
    printf("请输入汉诺塔的层数：");
    scanf("%d", &num);
    hanoi(num, 'A', 'B', 'C');
    return 0;
}



/*
解答题4（拓展题

int josephus(int n, int k) {
    int ans = 0;
    for (int i = 2; i <= n; ++i) {
        ans = (ans + k) % i;
    }
    return ans;
}

int main() {
    int n,m;
    printf("Enter n and m：");
    scanf("%d %d", &n, &m);

    int survivor = josephus(n, m);
    printf("最终活下来的人编号是：%d\n", survivor + 1);

    return 0;
}
*/