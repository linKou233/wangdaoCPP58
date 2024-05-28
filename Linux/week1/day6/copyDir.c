#include <func.h>

void copyFile(const char* src, const char* dst);
void copyDir(const char* src, const char* dst);

int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 3);
    copyDir(argv[1], argv[2]);

    printf("Directory copied successfully!\n");
    return 0;
}

void copyFile(const char* src, const char* dst) {
    int src_fd = open(src, O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening source file");
        return;
    }

    int dst_fd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd == -1) {
        perror("Error opening destination file");
        close(src_fd);
        return;
    }

    char buffer[4096];
    ssize_t bytes_read;

    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        ssize_t bytes_written = write(dst_fd, buffer, bytes_read);
        if (bytes_written == -1) {
            perror("Error writing to destination file");
            close(src_fd);
            close(dst_fd);
            return;
        }
    }

    close(src_fd);
    close(dst_fd);

    printf("File copied successfully!\n");
}

void copyDir(const char* src, const char* dst) {
    // 创建目标目录
    mkdir(dst, 0755);

    // 打开源目录
    DIR* dir = opendir(src);
    if (!dir) {
        perror("Error opening source directory");
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue; // 忽略 . 和 ..
        }

        char srcPath[PATH_MAX];
        char dstPath[PATH_MAX];
        snprintf(srcPath, PATH_MAX, "%s/%s", src, entry->d_name);
        snprintf(dstPath, PATH_MAX, "%s/%s", dst, entry->d_name);

        struct stat st;
        if (lstat(srcPath, &st) == -1) {
            perror("Error getting file status");
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            // 如果是目录，递归复制
            copyDir(srcPath, dstPath);
        } else if (S_ISREG(st.st_mode)) {
            // 如果是文件，复制文件
            copyFile(srcPath, dstPath);
        }
    }

    closedir(dir);
}

