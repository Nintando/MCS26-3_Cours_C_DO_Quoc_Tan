#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	int i;
	int e = 0;

	i=0;
	while (envp[i] != NULL)
	{
		printf("%s\n",envp[i]);
		e++;
		i++;
	}

	if (argc > 1)
		printf ("arguments: %d | environnement: %d\n",argc - 1, e);
	else{
		printf("Pad d'arguments\n");
		return 1;
	}
	return 0;
}
