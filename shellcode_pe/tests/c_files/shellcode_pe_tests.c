#include "ip2si.h"
#include <stdio.h>

int main() {
    printf("----- Testing ip_atoi -----\n");
    char *test_A = "65";
    int val_A = ip_atoi(test_A);
    printf("String: \"%s\" -> Integer: %d (Char: %c)\n\n", test_A, val_A, (char)val_A);


    printf("----- Testing ip_print_memory -----\n");
    char test_str[] = "Hello IPSSI!";
    ip_print_memory(test_str, sizeof(test_str));
    printf("\n");

    return 0;
}
