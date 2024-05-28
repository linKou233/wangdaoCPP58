#include <func.h>

typedef struct {
    long long start;
    long long end;
    long long result;
} SumArgs;

void* sum(void* args) {
    SumArgs* sum_args = (SumArgs*)args;
    long long start = sum_args->start;
    long long end = sum_args->end;
    long long result = 0;
    for (long long i = start; i <= end; ++i) {
        result += i;
    }
    sum_args->result = result;
    return NULL;
}

int main(void) {
    long long n;
    printf("Please input a long long int: ");
    scanf("%lld", &n);

    pthread_t t1, t2;
    SumArgs args1 = {1, n / 2, 0};
    SumArgs args2 = {n / 2 + 1, n, 0};

    pthread_create(&t1, NULL, sum, &args1);
    pthread_create(&t2, NULL, sum, &args2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    long long result = args1.result + args2.result;
    printf("The sum from 1 to %lld is %lld\n", n, result);

    return 0;
}
