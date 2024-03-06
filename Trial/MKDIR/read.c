#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    DIR *directory;
    struct dirent *entry;

    // Check if the directory argument is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char* dirname = argv[1]; // Name of the directory to be created

    // Attempt to create the directory
    if (mkdir(dirname, 0777) == 0) {
        printf("Directory '%s' created successfully.\n", dirname);
    } else {
        printf("Failed to create directory '%s'.\n", dirname);
    }
    
    FILE *fd;
    fd=fopen("file.txt", "w");
    fclose(fd);
    return 0;
}
