#include "cub3d.h"
#include <stdio.h>

void ft_print_map(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
}
