#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 3)
        return (1);

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        return (1);

    off_t len = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    unsigned char *data = malloc(len);
    if (!data)
        return (close(fd), 1);

    read(fd, data, len);
    close(fd);

    unsigned char key = argv[2][0];
    for (size_t i = 0; i < len; i++)
        data[i] ^= key;

    char *out_name = malloc(strlen(argv[1]) + 5);
    if (!out_name)
        return (free(data), 1);

    strcat(strcpy(out_name, argv[1]), ".enc");

    int out_fd = open(out_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out_fd != -1)
    {
        write(out_fd, data, len);
        close(out_fd);
    }

    free(data);
    free(out_name);
    return (0);
}
