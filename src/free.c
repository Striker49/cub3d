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

void	free_tex_buf(uint32_t **buf)
{
	int	i;

	i = 0;
	while (i < TEX_HEIGHT)
	{
		free(buf[i]);
		i++;
	}
	free(buf);
}

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	free_filecp(data);
	free_map(data->map);
	while (i < 6)
		free(data->path[i++]);
	free_tex_buf(data->n_buf);
	free_tex_buf(data->s_buf);
	free_tex_buf(data->e_buf);
	free_tex_buf(data->o_buf);
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
