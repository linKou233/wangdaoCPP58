#include <func.h>

int main(int argc, char *argv[]) {
    ARGS_CHECK(argc, 3);
    int src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1)
    {
        perror("Error opening source file");
        return 1;
    }

    int dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd == -1)
    {
        perror("Error opening destination file");
        close(src_fd);
        return 1;
    }

    char buffer[4096];
    ssize_t bytes_read;

    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0)
    {
        ssize_t bytes_written = write(dst_fd, buffer, bytes_read);
        if (bytes_written == -1)
        {
            perror("Error writing to destination file");
            close(src_fd);
            close(dst_fd);
            return 1;
        }
    }

    close(src_fd);
    close(dst_fd);

    printf("File copied successfully!\n");
    return 0;
}

