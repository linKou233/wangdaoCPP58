#include <stdio.h>
#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("ERROR, Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    FILE* sourceFile = fopen(argv[1], "rb");
    if (sourceFile == NULL) {
        printf("ERROR, cannot open %s\n", argv[1]);
        return 1;
    }

    FILE* destinationFile = fopen(argv[2], "wb");
    if (destinationFile == NULL) {
        printf("ERROR, cannot open %s\n", argv[2]);
        fclose(sourceFile);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destinationFile);
    }

    fclose(sourceFile);
    fclose(destinationFile);

    return 0;
}
