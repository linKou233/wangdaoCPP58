#include <func.h>

int main(int argc, char* argv[]) {
    char cmd[1024];
    pid_t pid;
    int status;

    for(;;) {
        printf("简易shell> ");
        fflush(stdout);

        // 读取用户输入的命令 cmd
        if(fgets(cmd, sizeof(cmd), stdin) == NULL) {
            break; // 如果读取失败，则退出循环
        }

        // 移除换行符
        cmd[strcspn(cmd, "\n")] = 0;

        // 如果cmd为exit，终止进程
        if(strcmp(cmd, "exit") == 0) {
            break;
        }

        // 创建子进程
        pid = fork();
        if(pid == -1) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if(pid == 0) { // 子进程
            // 让子进程执行命令
            char *args[] = {"/bin/sh", "-c", cmd, NULL};
            execvp(args[0], args);
            // 如果execvp返回，说明执行失败
            perror("execvp failed");
            exit(EXIT_FAILURE);
        } 
        else { // 父进程
            // 父进程等待子进程结束
            waitpid(pid, &status, 0);
            // 打印子进程的终止状态信息
            if(WIFEXITED(status)) {
                printf("子进程结束状态: %d\n", WEXITSTATUS(status));
            }
        }
    }

    return 0;
}
