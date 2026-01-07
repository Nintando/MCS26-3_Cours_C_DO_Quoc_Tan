#include "ip2si.h"

void simple_xor(char *str, char key)
{
	while (*str)
	{
		*str = *str ^ key;
		str++;
	}
}
