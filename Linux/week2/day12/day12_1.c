#include <func.h>

typedef struct {
    int id;
    int money;
    pthread_mutex_t mutex;
} Account;

Account acct1 = {1, 100, PTHREAD_MUTEX_INITIALIZER};
Account acct2 = {2, 900, PTHREAD_MUTEX_INITIALIZER};

void transfer(Account *from, Account *to, int amount) {
    pthread_mutex_lock(&from->mutex);
    printf("从 %d 转账 %d 到 %d\n", from->id, amount, to->id);
    from->money -= amount;
    pthread_mutex_unlock(&from->mutex);

    pthread_mutex_lock(&to->mutex);
    to->money += amount;
    pthread_mutex_unlock(&to->mutex);
}

void *transferThread(void *arg) {
    //从acct1转账到acct2
    transfer(&acct1, &acct2, 100);
}

int main(void) {
    // 创建两个线程：
    // 其中一个线程：从acct1转账100给acct2
    // 同时另一个线程：从acct2转账900给acct1
    // 要求：任何情况下，都避免死锁现象！

    // 主线程等待各个子线程结束。
    pthread_t thread;
    //线程1
    pthread_create(&thread, NULL, transferThread, NULL);
    //线程2
    transfer(&acct2, &acct1, 900);
    pthread_join(thread, NULL);

    printf("账户1余额为：%d\n", acct1.money);
    printf("账户2余额为：%d\n", acct2.money);
}