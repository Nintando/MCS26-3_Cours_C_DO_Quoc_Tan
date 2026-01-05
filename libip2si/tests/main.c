#include "ip2si.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    char *hello = "Hello, World!\n";
    ip_putstr(hello);

    int a = 5;
    int b = 10;
    
    printf("Before: a=%d, b=%d\n", a, b);
    ip_swap(&a, &b);
    printf("After: a=%d, b=%d\n", a, b);

    ip_putchar('A');
    ip_putchar('\n');

    int r = ip_strcmp("test", "tests");
    printf("ip_strcmp(\"test\", \"tests\") = %d\n", r);

    printf("string length: %d\n", ip_strlen(argv[0]));

    return 0;
}

