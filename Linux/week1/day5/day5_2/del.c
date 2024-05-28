#include <func.h>

void deleteDir(const char* path);

int main(int argc, char *argv[])
{
    
    ARGS_CHECK(argc, 2);

    deleteDir(argv[1]);
    return 0;
}

void deleteDir(const char* path) {
    DIR *pdir = opendir(path);
    struct dirent *pdirent;
    if (pdir == NULL) {
        perror("opendir");
        return;
    }

    char buf[1024];
    while ((pdirent = readdir(pdir)) != NULL) {
        // 忽略.和..
        if(strcmp(pdirent->d_name, ".") == 0 || strcmp(pdirent->d_name, "..") == 0) {
            continue;
        }

        snprintf(buf, sizeof(buf), "%s/%s", path, pdirent->d_name);

        struct stat statbuf;
        if(stat(buf, &statbuf) == -1) {
            perror("stat");
            continue;
        }

        // 如果该目录项是目录，则调用deleteDir递归删除
        if(S_ISDIR(statbuf.st_mode)) {
            deleteDir(buf);
        } else { // 如果该目录项是文件，则调用unlink删除文件
            if(unlink(buf) == -1) {
                perror("unlink");
            }
        }
    }

    // 关闭目录流
    closedir(pdir);

    // 目录为空了，可以删除该目录了
    if(rmdir(path) == -1) {
        perror("rmdir");
    }
}
