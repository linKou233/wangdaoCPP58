#include <func.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "用法: %s <文件名>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    int fd;
    char buf[1024];
    ssize_t bytes_read;

    // 打开文件以读取数据
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("无法打开文件");
        return 1;
    }

    // 创建有名管道
    mkfifo("myfifo", 0666);

    // 打开管道以写入数据
    int pipe_fd = open("myfifo", O_WRONLY);
    if (pipe_fd == -1) {
        perror("无法打开管道");
        return 1;
    }

    // 从文件读取数据并写入管道
    while ((bytes_read = read(fd, buf, sizeof(buf))) > 0) {
        write(pipe_fd, buf, bytes_read);
    }

    close(fd);
    close(pipe_fd);

    return 0;
}
