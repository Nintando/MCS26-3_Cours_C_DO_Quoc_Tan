#include <sys/stat.h>
#include <stdio.h>
#include "ip2si.h"

void ip_file_info(char *filename)
{
    struct stat sb;

    if (stat(filename, &sb) == -1)
    {
        printf("Error: Could not stat file %s\n", filename);
        return;
    }

    printf("Name: %s\n", filename);
    printf("Size: %lld\n", (long long)sb.st_size);
    printf("Inode: %llu\n", (unsigned long long)sb.st_ino);

    printf("Type: ");
    if (S_ISDIR(sb.st_mode))
        printf("Dir\n");
    else if (S_ISREG(sb.st_mode))
        printf("File\n");
    else if (S_ISLNK(sb.st_mode))
        printf("Link\n");
    else
        printf("Other\n");
}
