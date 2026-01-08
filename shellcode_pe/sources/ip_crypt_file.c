#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int fd, len = 0, i = 0, ret;
    char buf[4096], *data, *out;

    if (argc != 3 || (fd = open(argv[1], O_RDONLY)) == -1)
        return (1);

    while ((ret = read(fd, buf, 4096)) > 0)
        len += ret;
    
    close(fd);
    data = malloc(len);
    fd = open(argv[1], O_RDONLY);
    if (!data || fd == -1 || read(fd, data, len) != len)
        return (1);
    close(fd);

    while (i < len)
        data[i++] ^= argv[2][0];

    for (i = 0; argv[1][i]; i++);
    out = malloc(i + 5);
    if (!out) return (1);

    for (int j = 0; j < i; j++) out[j] = argv[1][j];
    out[i] = '.'; out[i+1] = 'e'; out[i+2] = 'n'; out[i+3] = 'c'; out[i+4] = '\0';

    fd = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd != -1)
    {
        write(fd, data, len);
        close(fd);
    }
    
    free(data);
    free(out);
    return (0);
}
