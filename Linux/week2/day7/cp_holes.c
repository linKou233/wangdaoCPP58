#include <func.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int src_fd, dst_fd;
    ssize_t num_in, num_out;
    char buffer[BUFFER_SIZE];
    off_t offset;

    // 检查参数个数
    ARGS_CHECK(argc, 3);

    // 打开源文件
    src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // 创建目标文件
    dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd == -1) {
        perror("Error creating destination file");
        close(src_fd);
        exit(EXIT_FAILURE);
    }

    // 循环读取源文件并写入目标文件
    while ((num_in = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        char *buf_ptr = buffer;
        while (num_in > 0) {
            num_out = write(dst_fd, buf_ptr, num_in);
            if (num_out == -1) {
                perror("Error writing to destination file");
                close(src_fd);
                close(dst_fd);
                exit(EXIT_FAILURE);
            }

            // 如果写入的字节数少于读取的字节数，说明可能遇到了文件空洞
            if (num_out < num_in) {
                offset = lseek(src_fd, 0, SEEK_CUR);
                if (offset == -1) {
                    perror("Error seeking in source file");
                    close(src_fd);
                    close(dst_fd);
                    exit(EXIT_FAILURE);
                }

                // 跳过空洞
                if (lseek(dst_fd, offset, SEEK_SET) == -1) {
                    perror("Error seeking in destination file");
                    close(src_fd);
                    close(dst_fd);
                    exit(EXIT_FAILURE);
                }
            }

            num_in -= num_out;
            buf_ptr += num_out;
        }
    }

    if (num_in == -1) {
        perror("Error reading from source file");
        close(src_fd);
        close(dst_fd);
        exit(EXIT_FAILURE);
    }

    // 关闭文件描述符
    close(src_fd);
    close(dst_fd);

    return 0;
}

