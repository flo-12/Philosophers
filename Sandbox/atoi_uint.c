
#include "stdio.h"

unsigned int	atoi_uint(char *str)
{
	int				i;
	unsigned int	nbr;

printf("str=%s\n", str);
	nbr = 0;
	i = -1;
	while (str[++i])
	{
		printf("str[%d]=%d\n", str[i] - '0');
		nbr = nbr * 10 + (str[i] - '0');
	}
	return (nbr);
}

int	main(int argc, char **argv)
{
	printf("\nnbr=%u\n", atoi_uint(argv[1]));
	return (0);
}