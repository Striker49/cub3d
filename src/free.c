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
	int	i;

	i = 0;
	free_filecp(data);
	free_map(data->map);
	while (i < 6)
		free(data->path[i++]);
	free(data->path);
	free(data->img);
	free(data->ceiling);
	free(data->floor);
}

void	free_close(int fd, t_data *data)
{
	close(fd);
	ft_free(data);
}
