#include "ip2si.h"

int ip_magic_number(void *ptr, size_t n, unsigned char magic)
{
    unsigned char *p;
    size_t i;

    if (!ptr)
        return (-1);
    
    p = (unsigned char *)ptr;
    i = 0;
    while (i < n)
    {
        if (p[i] == magic)
            return (i);
        i++;
    }
    return (-1);
}
