#include "cub3d.h"

void	ft_safety(uint32_t **buf)
{
	if (!buf)
	{
		free(buf);
		exit(-1);
	}
}

void	ft_safety_small(uint32_t **buf, int y)
{
	int	j;

	j = 0;
	if (!buf[y])
	{
		while (j < y)
		{
			free(buf[j]);
			j++;
		}
		free(buf);
		exit(-1);
	}
}
