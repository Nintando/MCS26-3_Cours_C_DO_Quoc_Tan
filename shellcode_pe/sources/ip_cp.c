#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fd_src;
    int fd_dest;
    int ret;
    char buf[4096];

    if (argc != 3)
        return (1);

    fd_src = open(argv[1], O_RDONLY);
    if (fd_src == -1)
        return (1);

    fd_dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_dest == -1)
    {
        close(fd_src);
        return (1);
    }

    while ((ret = read(fd_src, buf, sizeof(buf))) > 0)
    {
        write(fd_dest, buf, ret);
    }

    close(fd_src);
    close(fd_dest);
    return (0);
}
