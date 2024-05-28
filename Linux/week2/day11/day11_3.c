#include <func.h>

typedef struct {
    long long* value;
    int times;
} IncrArgs;

void* incr(void* args) {
    IncrArgs* incr_args = (IncrArgs*)args;
    for (int i = 0; i < incr_args->times; ++i) {
        (*(incr_args->value))++;
    }
    return NULL;
}

int main(void) {
    long long* value = (long long*) calloc(1, sizeof(long long));
    const int times = 10000000;

    pthread_t t1, t2;
    IncrArgs args = {value, times};

    pthread_create(&t1, NULL, incr, &args);
    pthread_create(&t2, NULL, incr, &args);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("The value is %lld\n", *value);

    free(value);
    return 0;
}
