#include <func.h>

void handler(int signo) {
    const char *signal_name;
    switch (signo) {
        case SIGINT:
            signal_name = "SIGINT";
            break;
        case SIGQUIT:
            signal_name = "SIGQUIT";
            break;
        case SIGTSTP:
            signal_name = "SIGTSTP";
            break;
        default:
            signal_name = "未知信号";
    }
    printf("捕获到信号 %s\n", signal_name);
}

int main() {
     // 注册信号处理函数 (捕获信号)
    sighandler_t oldhandler = signal(SIGINT, handler);
    if (oldhandler == SIG_ERR) {
        error(1, errno, "signal %d", SIGINT);
    }

    oldhandler = signal(SIGTSTP, handler);
    if (oldhandler == SIG_ERR) {
        error(1, errno, "signal %d", SIGTSTP);
    }
    for (;;) {
        pause();
    }
}
