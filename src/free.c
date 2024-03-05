#include "cub3d.h"

void	free_filecp(t_data *data)
{
	int i;

	i = 0;
	if (!data->file)
	{
		while (data->file[i])
		{
			free(data->file[i]);
			i++;
		}
		free(data->file);
	}
}


void	free_map(t_data *data)
{
	int i;

	i = 0;
	if (!data->map)
	{
		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
}

void ft_free(t_data *data)
{
	free_filecp(data);
	free_map(data);
	free(data->no);
	free(data->so);
	free(data->ea);
	free(data->we);
	free(data->floor);
	free(data->ceiling);
}