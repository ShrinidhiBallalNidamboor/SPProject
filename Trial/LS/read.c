#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    DIR *directory;
    struct dirent *entry;

    // Check if the directory argument is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open the directory
    directory = opendir(argv[1]);
    if (directory == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    // Print the contents of the directory
    FILE *fd=fopen("file.txt", "w");
    fprintf(fd, "hello");
    while ((entry = readdir(directory)) != NULL) {
        fprintf(fd, "%s\n", entry->d_name);
    }
    fclose(fd);
    // Close the directory
    closedir(directory);

    return 0;
}
