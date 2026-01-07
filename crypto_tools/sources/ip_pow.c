#include "ip2si.h"

int ip_pow(int nb, int power)
{
    int result = 1;

    if (power < 0)
        return (0);
    if (power == 0)
        return (1);

    while (power > 0)
    {
        result *= nb;
        power--;
    }
    return (result);
}
