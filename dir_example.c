#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

// Step 2: Create a structure DIRENT
// This is actually included from the <dirent.h> header file,
// so we don't need to redefine it. We use it directly.

int main() {
    // Step 3: Declare Buff, Pointer
    DIR *dir;          // Pointer to a directory stream
    struct dirent *entry; // Pointer to a directory entry

    // Step 4: Get directory name
    char dirname[256];
    printf("Enter the directory name: ");
    scanf("%255s", dirname);

    // Step 5: Open Directory
    dir = opendir(dirname);
    if (dir == NULL) {
        perror("Unable to open directory");
        return EXIT_FAILURE;
    }

    // Step 6: Read content of the Directory
    printf("Contents of directory '%s':\n", dirname);
    while ((entry = readdir(dir)) != NULL) {
        printf("Name: %s\n", entry->d_name);
    }

    // Step 7: Close Directory
    closedir(dir);
    
    return EXIT_SUCCESS;
}

