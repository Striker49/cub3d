#include "cub3d.h"

void	free_filecp(t_data *data)
{
	int	i;

	i = 0;
	if (data->file)
	{
		while (data->file[i])
		{
			if (data->file[i])
				free(data->file[i]);
			i++;
		}
		if (data->file)
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
			if (map[i])
				free(map[i]);
			i++;
		}
		if (map)
			free(map);
	}
}

void	free_tex_buf(uint32_t **buf)
{
	int	i;

	i = 0;
	while (i < TEX_HEIGHT)
	{
		if (buf[i])
			free(buf[i]);
		i++;
	}
	if (buf)
		free(buf);
}

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	free_filecp(data);
	free_map(data->map);
	while (i < 6)
	{
		if (data->path[i])
			free(data->path[i]);
		i++;
	}
	free_tex_buf(data->n_buf);
	free_tex_buf(data->s_buf);
	free_tex_buf(data->e_buf);
	free_tex_buf(data->o_buf);
	if (data->tex_Wall_N)
		mlx_delete_texture(data->tex_Wall_N);
	if (data->tex_Wall_S)
		mlx_delete_texture(data->tex_Wall_S);
	if (data->tex_Wall_E)
		mlx_delete_texture(data->tex_Wall_E);
	if (data->tex_Wall_O)
		mlx_delete_texture(data->tex_Wall_O);
	if (data->ray->line)
		free(data->ray->line);
	if (data->ray)
		free(data->ray);
}

void	free_close(int fd, t_data *data)
{
	close(fd);
	ft_free(data);
}
