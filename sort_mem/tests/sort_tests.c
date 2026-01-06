#include "ip2si.h"
#include <stdlib.h>

void test_putnbr(void)
{
    ip_putstr("--- Testing ip_putnbr ---\n");
    ip_putchar('\n');
    ip_putstr("Expected: 42 | Result: ");
    ip_putnbr(42);
    ip_putstr("\n\n");
}

void test_range(void)
{
    int *res;
    int min = 5;
    int max = 10;
    int i;

    ip_putstr("--- Testing ip_range (5 to 10) ---\nResult: ");
    res = ip_range(min, max);
    if (!res)
    {
        ip_putstr("Allocation failed or min >= max\n");
        return;
    }
    i = 0;
    while (i < (max - min))
    {
        ip_putnbr(res[i]);
        ip_putchar(' ');
        i++;
    }
    free(res);
    ip_putstr("\n\n");
}

void test_strdup(void)
{
    char *original = "Hello Ipssi";
    char *copy;

    ip_putstr("--- Testing ip_strdup ---\n");
    copy = ip_strdup(original);
    ip_putstr("Original: ");
    ip_putstr(original);
    ip_putstr("\nCopy:     ");
    ip_putstr(copy);
    
    if (copy != original)
        ip_putstr("\nMemory addresses are different.");
    
    free(copy);
    ip_putstr("\n\n");
}

void test_magic(void)
{
    t_magic data;
    char *box = "ABCDEFG";
    int index;

    ip_putstr("--- Testing Magic Functions ---\n");

    data.id = 0;
    data.name = "Normal";
    ip_struct_magic(&data);
    ip_putstr("Struct Magic Result -> ID: ");
    ip_putnbr(data.id);
    ip_putstr(" | Name: ");
    ip_putstr(data.name);
    ip_putstr("\n");

    index = ip_magic_number(box, 7, 'E');
    ip_putstr("Magic Number 'E' in 'ABCDEFG' -> Index: ");
    ip_putnbr(index);
    ip_putstr("\n");
}

int main(void)
{
    test_putnbr();
    test_range();
    test_strdup();
    test_magic();
    return (0);
}
