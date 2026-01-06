#include "ip2si.h"
#include <stdio.h>

int main() {

    // my_memset
    char str1[10] = "XXXXXXXXX";
    my_memset(str1, '!', 5);
    printf("memset:  %s\n", str1);

    // my_memcpy
    char str2[10] = "---------";
    my_memcpy(str2, "Hello", 5);
    printf("memcpy:  %s\n", str2);

    // my_memmove
    char str3[10] = "ABCDEFGHI";
    my_memmove(str3 + 2, str3, 3);
    printf("memmove: %s\n", str3);
    
    return 0;
}
