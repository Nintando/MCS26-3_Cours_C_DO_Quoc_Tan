#include "ip2si.h"
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int fd;
    char buffer[4096];
    ssize_t bytes_read;

    if (argc != 2) return (1);

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
	    fprintf(stderr, "Error opening file: %s\n", strerror(errno));
     	    return (1);
    }

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        write(1, buffer, bytes_read);
    }

    close(fd);
    return (0);
}
