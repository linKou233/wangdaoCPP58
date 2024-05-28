#include <func.h>

int main() {
    int fd_client, fd_server;
    char client_fifo[] = "client_fifo";
    char server_fifo[] = "server_fifo";
    char buf[1024];

    // 打开客户端和服务器管道
    fd_client = open(client_fifo, O_WRONLY);
    fd_server = open(server_fifo, O_RDONLY);

    printf("客户端已连接到服务器。\n");

    while (1) {
        printf("请输入消息: ");
        fgets(buf, sizeof(buf), stdin);

        // 发送消息到服务器
        write(fd_client, buf, strlen(buf));

        // 等待服务器回复
        read(fd_server, buf, sizeof(buf));
        printf("服务器回复: %s\n", buf);
    }

    close(fd_client);
    close(fd_server);

    return 0;
}
