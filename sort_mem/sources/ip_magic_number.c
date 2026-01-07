#include "ip2si.h"

int ip_magic_number(char *file_header)
{
    if (!file_header)
        return (0);

    if ((unsigned char)file_header[0] == 0x7f &&
        (unsigned char)file_header[1] == 0x45 &&
        (unsigned char)file_header[2] == 0x4c &&
        (unsigned char)file_header[3] == 0x46)
    {
        return (1);
    }

    return (0);
}
