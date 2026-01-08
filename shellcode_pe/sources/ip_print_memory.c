#include "ip2si.h"
#include <stdio.h>

void ip_print_memory(const void *addr, size_t size) {
    const unsigned char *p = (const unsigned char *)addr;
    for (size_t i = 0; i < size; i++) {
        printf("%02x ", p[i]);
        if ((i + 1) % 16 == 0) printf("\n");
    }
    printf("\n");
}
