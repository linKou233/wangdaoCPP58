#include <func.h>

int main() {
    int pipe1[2], pipe2[2];
    pid_t pid;
    char parent_message[] = "来自父进程的消息";
    char child_message[] = "来自子进程的消息";
    char readbuffer[80];

    // 创建两个管道
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("创建管道失败");
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        perror("fork 失败");
        return 1;
    }

    if (pid > 0) {  // 父进程
        close(pipe1[1]); // 关闭管道1的写端
        close(pipe2[0]); // 关闭管道2的读端

        // 从子进程读取消息
        read(pipe1[0], readbuffer, sizeof(readbuffer));
        printf("父进程接收到: %s\n", readbuffer);

        // 给子进程发送消息
        write(pipe2[1], parent_message, strlen(parent_message)+1);
        
        close(pipe1[0]); 
        close(pipe2[1]); 
    } else {  // 子进程
        close(pipe1[0]); // 关闭管道1的读端
        close(pipe2[1]); // 关闭管道2的写端

        // 给父进程发送消息
        write(pipe1[1], child_message, strlen(child_message)+1);

        // 从父进程读取消息
        read(pipe2[0], readbuffer, sizeof(readbuffer));
        printf("子进程接收到: %s\n", readbuffer);

        close(pipe1[1]);
        close(pipe2[0]); 
    }

    return 0;
}
