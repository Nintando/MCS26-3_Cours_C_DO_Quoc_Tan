#include "ip2si.h"

void *my_memcpy(void *dest, const void *src, size_t n) {
    if (!dest && !src) return NULL;

    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    while (n-- > 0) {
        *d++ = *s++;
    }
    return dest;
}
