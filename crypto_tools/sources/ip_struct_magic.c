#include "ip2si.h"

void ip_struct_magic(t_magic *data)
{
    if (!data)
        return;

    data->id = 1337;
    data->name = "Magical_Pointer";
}
