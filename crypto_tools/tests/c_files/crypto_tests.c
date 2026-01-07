#include "ip2si.h"
#include <stdio.h>

int main(void)
{
    printf("--- TEST Factorial ---\n");
    printf("Factorial of 5: %d (Expected: 120)\n\n", ip_iterative_factorial(5));

    printf("--- TEST Power ---\n");
    printf("2 to the power 3: %d (Expected: 8)\n\n", ip_pow(2, 3));

    printf("--- TEST Bit Packing ---\n");
    int packed = ip_bin_pack(0xAB, 0xCD, 0xEF, 0x01);
    printf("Packed Value: 0x%x (Expected: 0xabcdef01)\n\n", packed);

    printf("--- TEST XOR Function ---\n");
    char message[] = "Hello";
    char key = 'X';
    
    printf("Original: %s\n", message);
    simple_xor(message, key);
    printf("Encrypted: %s\n", message);
    simple_xor(message, key);
    printf("Decrypted: %s\n", message);

    return (0);
}
