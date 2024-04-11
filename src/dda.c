#include "cub3d.h"

void	ft_trace_wall(t_data *data, t_ray *ray)
{
	ray->line->tex_x = TEX_WIDTH;
	ray->line->x = 0;
	while (ray->line->x < WINDOW_WIDTH)
	{
		ft_dda(data, ray);
		ray->h_wall = (int)(WINDOW_HEIGHT / ray->perpWallDist);
		ray->line->y0 = -ray->h_wall / 2 + WINDOW_HEIGHT / 2;
		if (ray->line->y0 < 0)
			ray->line->y0 = 0;
		ray->line->y1 = ray->h_wall / 2 + WINDOW_HEIGHT / 2;
		if (ray->line->y1 >= WINDOW_HEIGHT)
			ray->line->y1 = WINDOW_HEIGHT - 1;
		trace_line(data, ray->line);
		ray->line->x++;
		clean_data(data);
		clean_line(ray->line);
	}
}

void	trace_line(t_data *data, t_line *line)
{
	int	buf_x;

	buf_x = 0;
	if (data->ray->side == 1)
	{
		buf_x = get_hit(data, data->tex_Wall_N);
		ft_get_texture(data, line, data->n_buf, buf_x);
	}
	else if (data->ray->side == 2)
	{
		buf_x = get_hit2(data, data->tex_Wall_S);
		ft_get_texture(data, line, data->s_buf, buf_x);
	}
	else if (data->ray->side == 3)
	{
		buf_x = get_hit(data, data->tex_Wall_E);
		ft_get_texture(data, line, data->e_buf, buf_x);
	}
	else
	{
		buf_x = get_hit2(data, data->tex_Wall_O);
		ft_get_texture(data, line, data->o_buf, buf_x);
	}
}

int	get_hit(t_data *data, mlx_texture_t *tex_Wall)
{
	double	hit;
	int		buf_x;

	hit = data->ray->perpWallDist;
	hit = data->player.x + hit * data->ray->rayDirX;
	hit -= floor(hit);
	buf_x = (int)(hit * (double)tex_Wall->width);
	return (buf_x);
}

int	get_hit2(t_data *data, mlx_texture_t *tex_Wall)
{
	double	hit;
	int		buf_x;

	hit = data->ray->perpWallDist;
	hit = data->player.y + hit * data->ray->rayDirY;
	hit -= floor(hit);
	buf_x = (int)(hit * (double)tex_Wall->width);
	return (buf_x);
}
