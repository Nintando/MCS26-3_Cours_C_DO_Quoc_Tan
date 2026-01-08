#include "ip2si.h"

int ip_bin_pack(int b1, int b2, int b3, int b4)
{
    int packed_value;

    packed_value = (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;

    return (packed_value);
}
