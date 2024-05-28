#include <func.h>

int main() {
    int fd_client, fd_server;
    char client_fifo[] = "client_fifo";
    char server_fifo[] = "server_fifo";
    char buf[1024];

    // 创建有名管道
    mkfifo(client_fifo, 0666);
    mkfifo(server_fifo, 0666);

    // 打开客户端和服务器管道
    fd_client = open(client_fifo, O_RDONLY);
    fd_server = open(server_fifo, O_WRONLY);

    printf("服务器已启动，等待客户端连接...\n");

    while (1) {
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(fd_client, &read_fds);

        // 使用 select 监视客户端管道
        select(fd_client + 1, &read_fds, NULL, NULL, NULL);

        if (FD_ISSET(fd_client, &read_fds)) {
            // 从客户端管道读取数据
            read(fd_client, buf, sizeof(buf));
            printf("收到消息: %s\n", buf);

            // 回复客户端
            write(fd_server, "服务器收到消息", strlen("服务器收到消息"));
        }
    }

    close(fd_client);
    close(fd_server);
    unlink(client_fifo);
    unlink(server_fifo);

    return 0;
}
