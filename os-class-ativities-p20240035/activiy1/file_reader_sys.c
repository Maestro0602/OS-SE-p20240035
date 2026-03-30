/* file_creator_sys.c */
#include <fcntl.h>    // open(), O_WRONLY, O_CREAT, O_TRUNC
#include <unistd.h>   // write(), close()
#include <string.h>   // strlen()

int main() {
    char buffer[256];
    int fd;

    // 1. Open file
    fd = open("output.txt", O_RDONLY);
    if (fd < 0) {
        write(1, "Error opening file\n", 19);
        return 1;
    }

    // 2. Read and 3. Write in a loop
    int bytesRead;
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        write(1, buffer, bytesRead);
    }

    // 4. Close file
    close(fd);

    return 0;
}
