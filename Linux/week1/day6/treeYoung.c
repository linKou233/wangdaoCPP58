#include <func.h>

void dfs_print(const char* path, int width);

int directories = 0, files = 0;

int main(int argc, char *argv[]) {
    ARGS_CHECK(argc, 2);
    puts(argv[1]); // 打印目录的名字
    dfs_print(argv[1], 4); // 递归打印每一个目录项

    printf("\n%d directories, %d files\n", directories, files); // 最后打印统计信息
    return 0;
}

void dfs_print(const char* path, int width) {
    DIR* dir = opendir(path);
    if (!dir) {
        perror("Error opening directory");
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue; // 忽略 . 和 ..
        char itemPath[PATH_MAX];
        snprintf(itemPath, PATH_MAX, "%s/%s", path, entry->d_name);

        struct stat st;
        if (lstat(itemPath, &st) == -1) {
            perror("Error getting file status");
            continue;
        }

        for (int i = 0; i < width; ++i)
            putchar(' '); // 缩进

        if (S_ISDIR(st.st_mode)) {
            printf("%s\n", entry->d_name);
            ++directories;
            dfs_print(itemPath, width + 4); // 递归处理子目录
        }
        else if (S_ISREG(st.st_mode)) {
            printf("%s\n", entry->d_name);
            ++files;
        }
    }

    closedir(dir);
}

