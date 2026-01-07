#include "ip2si.h"

int *ip_range(int min, int max) {
    int *range;
    int size;
    int i;

    if (min >= max)
        return (NULL);

    size = max - min;
    range = (int *)malloc(sizeof(int) * size);

    if (!range)
        return (NULL);

    i = 0;
    while (min < max) {
        range[i] = min;
        min++;
        i++;
    }
    return (range);
}
