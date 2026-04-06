/* dir_list_sys.c - Version B Using System Calls */
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

int main() {
    char buffer[512];
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    int fd = 1;  // stdout file descriptor
    
    // 1. Open current directory with opendir(".")
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }
    
    // 2. Print header line using write()
    const char *header = "Files in current directory:\n";
    write(fd, header, strlen(header));
    
    // 3. Loop through entries with readdir()
    while ((entry = readdir(dir)) != NULL) {
        // Skip . and ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
            
        // 4. For each entry, use stat() to get file size
        if (stat(entry->d_name, &file_stat) == 0) {
            // 5. Format output into buffer with snprintf(), then write() to fd 1
            int len = snprintf(buffer, sizeof(buffer), "%-30s %10ld\n", 
                             entry->d_name, file_stat.st_size);
            write(fd, buffer, len);
        }
    }
    
    // 6. Close directory with closedir()
    closedir(dir);
    
    return 0;
}
