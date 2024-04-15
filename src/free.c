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
	// int	j;

	i = 0;
	free_filecp(data);
	free_map(data->map);
	while (i < 6)
		free(data->path[i++]);
	i = 0;
	while (i < 100)
		free(data->n_buf[i++]);
	i = 0;
	while (i < 100)
		free(data->s_buf[i++]);
	i = 0;
	while (i < 100)
		free(data->e_buf[i++]);
	i = 0;
	while (i < 100)
		free(data->o_buf[i++]);
	free(data->n_buf);
	free(data->s_buf);
	free(data->e_buf);
	free(data->o_buf);
	mlx_delete_texture(data->tex_Wall_N);
	mlx_delete_texture(data->tex_Wall_S);
	mlx_delete_texture(data->tex_Wall_E);
	mlx_delete_texture(data->tex_Wall_O);
	free(data->ray->line);
	free(data->ray);
}

void	free_close(int fd, t_data *data)
{
	close(fd);
	ft_free(data);
}
