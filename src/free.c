#include "cub3d.h"

void ft_free(t_data *data)
{
	int i;

	i = 0;
	while (data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
}