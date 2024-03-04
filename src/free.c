#include "cub3d.h"

void ft_free(t_data *data)
{
	int i;

	i = 0;
	while (data->file[i])
	{
		free(data->file[i]);
		i++;
	}
	free(data->file);
}