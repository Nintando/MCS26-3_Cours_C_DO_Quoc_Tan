#include "ip2si.h"

void ip_putnbr(int nb) {
    long n;

    n = nb;
    if (n < 0)
    {
        ip_putchar('-');
        n = -n;
    }

    if (n >= 10)
        ip_putnbr(n / 10);

    ip_putchar((n % 10) + '0');
}
