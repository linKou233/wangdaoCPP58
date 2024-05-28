#include <func.h>

typedef struct {
    int id;
    int money;
} Account;

Account acct = {1, 100};
pthread_mutex_t lock;

void* withdraw(void* arg) {
    pthread_mutex_lock(&lock);
    if (acct.money >= 100) {
        acct.money -= 100;
        printf("Thread %ld withdraws 100, balance: %d\n", pthread_self(), acct.money);
    } else {
        printf("Thread %ld fails to withdraw due to insufficient funds, balance: %d\n", pthread_self(), acct.money);
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(void) {
    pthread_t tids[10];
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < 10; ++i) {
        pthread_create(&tids[i], NULL, withdraw, NULL);
    }

    for (int i = 0; i < 10; ++i) {
        pthread_join(tids[i], NULL);
    }

    printf("Final balance: %d\n", acct.money);

    pthread_mutex_destroy(&lock);
    return 0;
}
