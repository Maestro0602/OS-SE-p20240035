/* file_creator_sys.c */
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(void) {
	const char *text = "Hello from Operating Systems class!\n";
	const char *ok_msg = "File created successfully!\n";
	const char *err_msg = "Error creating file\n";

	int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0) {
		write(2, err_msg, strlen(err_msg));
		return 1;
	}

	write(fd, text, strlen(text));
	close(fd);

	write(1, ok_msg, strlen(ok_msg));
	return 0;
}
