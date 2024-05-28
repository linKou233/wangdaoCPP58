#include <func.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "用法: %s <目标文件名>\n", argv[0]);
        return 1;
    }

    const char* target_filename = argv[1];
    int fd;
    char buf[1024];
    ssize_t bytes_read;

    // 创建有名管道
    mkfifo("myfifo", 0666);

    // 打开管道以读取数据
    int pipe_fd = open("myfifo", O_RDONLY);
    if (pipe_fd == -1) {
        perror("无法打开管道");
        return 1;
    }

    // 打开目标文件以写入数据
    fd = open(target_filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("无法打开目标文件");
        return 1;
    }

    // 从管道读取数据并写入目标文件
    while ((bytes_read = read(pipe_fd, buf, sizeof(buf))) > 0) {
        write(fd, buf, bytes_read);
    }

    close(fd);
    close(pipe_fd);

    return 0;
}
