#include <func.h>

int main() {
    const char* filename = "text1";
    int fd;

    // 打开文件 text1，以 O_RDWR | O_CREAT | O_TRUNC 方式
    fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // 将文件大小截断为 40959
    if (ftruncate(fd, 40959) == -1) {
        perror("Error truncating file");
        close(fd);
        return 1;
    }

    // 将文件位置偏移到文件末尾
    if (lseek(fd, 0, SEEK_END) == -1) {
        perror("Error seeking to end of file");
        close(fd);
        return 1;
    }

    // 写入数据 "Hello world"
    if (write(fd, "Hello world", 11) == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    // 使用 fstat 获取 st_blocks（实际占用磁盘的块数）
    struct stat stat_info;
    if (fstat(fd, &stat_info) == -1) {
        perror("Error getting file status");
        close(fd);
        return 1;
    }

    printf("st_blocks (实际占用磁盘的块数): %ld\n", stat_info.st_blocks);

    // 关闭文件
    close(fd);

    return 0;
}

