#include "cub3d.h"

void	ft_safety(uint32_t **buf, t_data *data)
{
	if (!buf)
	{
		if (buf)
			free(buf);
		ft_free(data);
		exit(-1);
	}
}

void	ft_safety_small(uint32_t **buf, int y, t_data *data)
{
	int	j;

	j = 0;
	if (!buf[y])
	{
		while (j < y)
		{
			if (buf[j])
				free(buf[j]);
			j++;
		}
		if (buf)
			free(buf);
		ft_free(data);
		exit(-1);
	}
}
