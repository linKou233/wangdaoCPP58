#include <func.h>

int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 3);

    const char* src_filename = argv[1];
    const char* dst_filename = argv[2];

    // 打开源文件
    int src_fd = open(src_filename, O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // 获取源文件大小
    struct stat src_stat;
    if (fstat(src_fd, &src_stat) == -1) {
        perror("Error getting source file size");
        close(src_fd);
        exit(EXIT_FAILURE);
    }
    off_t src_size = src_stat.st_size;

    // 创建目标文件
    int dst_fd = open(dst_filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (dst_fd == -1) {
        perror("Error creating destination file");
        close(src_fd);
        exit(EXIT_FAILURE);
    }

    // 设置目标文件大小
    if (ftruncate(dst_fd, src_size) == -1) {
        perror("Error setting destination file size");
        close(src_fd);
        close(dst_fd);
        exit(EXIT_FAILURE);
    }

    // 映射源文件到内存
    void* src_map = mmap(NULL, src_size, PROT_READ, MAP_SHARED, src_fd, 0);
    if (src_map == MAP_FAILED) {
        perror("Error mapping source file");
        close(src_fd);
        close(dst_fd);
        exit(EXIT_FAILURE);
    }

    // 映射目标文件到内存
    void* dst_map = mmap(NULL, src_size, PROT_WRITE, MAP_SHARED, dst_fd, 0);
    if (dst_map == MAP_FAILED) {
        perror("Error mapping destination file");
        munmap(src_map, src_size);
        close(src_fd);
        close(dst_fd);
        exit(EXIT_FAILURE);
    }

    // 复制数据
    memcpy(dst_map, src_map, src_size);

    // 解除映射
    munmap(src_map, src_size);
    munmap(dst_map, src_size);

    // 关闭文件描述符
    close(src_fd);
    close(dst_fd);

    printf("File copied successfully!\n");

    return 0;
}

