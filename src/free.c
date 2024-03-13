#include "cub3d.h"

void	free_filecp(t_data *data)
{
	int	i;

	i = 0;
	if (data->file)
	{
		while (data->file[i])
		{
			free(data->file[i]);
			i++;
		}
		free(data->file);
	}
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

void	ft_free(t_data *data)
{
	free_filecp(data);
	free_map(data->map);
	free(data->path[NORTH]);
	free(data->path[SOUTH]);
	free(data->path[EAST]);
	free(data->path[WEST]);
	free(data->path[FLOOR]);
	free(data->path[CEILING]);
	free(data->path);
}

void	free_close(int fd, t_data *data)
{
	close(fd);
	ft_free(data);
}
