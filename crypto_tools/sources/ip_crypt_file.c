#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    // 1. Validate arguments
    if (argc != 3)
        return (1);

    char *filename = argv[1];
    // Take the first character of the second argument as the KEY
    unsigned char key = (unsigned char)argv[2][0];

    // 2. Pass 1: Count total bytes (since lseek/stat are not allowed)
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (1);

    int total_bytes = 0;
    int ret;
    char temp_buf[4096];
    while ((ret = read(fd, temp_buf, sizeof(temp_buf))) > 0)
        total_bytes += ret;
    close(fd);

    // 3. Pass 2: Allocate memory and read the actual content
    char *content = malloc(total_bytes);
    if (!content)
        return (1);

    fd = open(filename, O_RDONLY);
    read(fd, content, total_bytes);
    close(fd);

    // 4. Apply XOR encryption using the numeric value of the KEY
    for (int i = 0; i < total_bytes; i++)
    {
        content[i] = content[i] ^ key;
    }

    // 5. Build the output filename (<file>.enc) manually
    int name_len = 0;
    while (filename[name_len])
        name_len++;

    char *out_name = malloc(name_len + 5); // space for name + ".enc" + '\0'
    if (!out_name)
        return (1);

    int j = 0;
    while (j < name_len)
    {
        out_name[j] = filename[j];
        j++;
    }
    out_name[j++] = '.';
    out_name[j++] = 'e';
    out_name[j++] = 'n';
    out_name[j++] = 'c';
    out_name[j] = '\0';

    // 6. Write the result to the new file
    int out_fd = open(out_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out_fd != -1)
    {
        write(out_fd, content, total_bytes);
        close(out_fd);
    }

    // 7. Cleanup
    free(content);
    free(out_name);

    return (0);
}
