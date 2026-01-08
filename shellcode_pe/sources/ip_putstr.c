#include "ip2si.h"

void ip_putstr(char *str)
{
	int i=0;
	if (!str)
		return;
	while (str[i])
	{
		write(1,&str[i],1);
		i++;
	}
}
