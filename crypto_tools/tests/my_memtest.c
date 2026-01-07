#include "ip2si.h"
#include <stdio.h>

int main() {

    // my_memset
    ip_putstr("--- Testing Memset ---\n");
    char str1[10] = "XXXXXXXXX";
    ip_memset(str1, '!', 5);
    printf("memset:  %s\n", str1); 
    ip_putstr("\n");

    // my_memcpy
    ip_putstr("--- Testing Memcpy ---\n");
    char str2[10] = "---------";
    ip_memcpy(str2, "Hello", 5);
    printf("memcpy:  %s\n", str2);
    ip_putstr("\n");


    // my_memmove
    ip_putstr("--- Testing Memmove ---\n");
    char str3[10] = "ABCDEFGHI";
    ip_memmove(str3 + 2, str3, 3);
    printf("memmove: %s\n", str3);
    ip_putstr("\n");

    return 0;
}
