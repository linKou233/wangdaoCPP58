#include <func.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("用法: %s <信号编号> <进程ID>...\n", argv[0]);
        return 1;
    }

    int signo = atoi(argv[1]);

    for (int i = 2; i < argc; i++) {
        pid_t pid = atoi(argv[i]);
        if (kill(pid, signo) == -1) {
            perror("发送信号失败");
            continue;
        }
        printf("向进程 %d 发送信号 %d 成功\n", pid, signo);
    }

    return 0;
}
