#include "cub3d.h"

uint32_t	**ft_buf_line_text(mlx_texture_t *tex_Wall_R)
{
	int			x;
	int			y;
	int			i;
	uint32_t	**buf;

	x = 0;
	y = 0;
	i = 0;
	buf = malloc(sizeof(uint32_t *) * (TEX_HEIGHT));
	ft_safety(buf);
	while (y < TEX_HEIGHT)
	{
		buf[y] = malloc(sizeof(uint32_t) * (TEX_WIDTH));
		ft_safety_small(buf, y);
		x = 0;
		while (x < TEX_WIDTH)
		{
			i = (y * tex_Wall_R->width * 4) + (x * 4);
			buf[y][x] = get_rgba(tex_Wall_R->pixels[i], tex_Wall_R->pixels[i
					+ 1], tex_Wall_R->pixels[i + 2], tex_Wall_R->pixels[i + 3]);
			x++;
		}
		y++;
	}
	return (buf);
}

void	ft_load_texture(t_data *data)
{
	data->tex_Wall_N = mlx_load_png(data->path[NORTH]);
	if (data->tex_Wall_N == NULL)
		error_texture(data);
	data->tex_Wall_S = mlx_load_png(data->path[SOUTH]);
	if (data->tex_Wall_S == NULL)
		error_texture(data);
	data->tex_Wall_E = mlx_load_png(data->path[EAST]);
	if (data->tex_Wall_E == NULL)
		error_texture(data);
	data->tex_Wall_O = mlx_load_png(data->path[WEST]);
	if (data->tex_Wall_O == NULL)
		error_texture(data);
	ft_fill_bufs(data);
}

void	ft_fill_bufs(t_data *data)
{
	if (ft_check_oversize_tex(data) == 1)
	{
		data->n_buf = ft_buf_line_text(data->tex_Wall_N);
		data->s_buf = ft_buf_line_text(data->tex_Wall_S);
		data->e_buf = ft_buf_line_text(data->tex_Wall_E);
		data->o_buf = ft_buf_line_text(data->tex_Wall_O);
	}
	else
	{
		data->n_buf = ft_resize_tex(data, data->tex_Wall_N, data->n_buf);
		data->s_buf = ft_resize_tex(data, data->tex_Wall_S, data->s_buf);
		data->e_buf = ft_resize_tex(data, data->tex_Wall_E, data->e_buf);
		data->o_buf = ft_resize_tex(data, data->tex_Wall_O, data->o_buf);
	}
}

int	ft_check_oversize_tex(t_data *data)
{
	if ((data->tex_Wall_N->height == 100 && data->tex_Wall_N->width == 100)
		&& (data->tex_Wall_S->height == 100 && data->tex_Wall_S->width == 100)
		&& (data->tex_Wall_E->height == 100 && data->tex_Wall_E->width == 100)
		&& (data->tex_Wall_O->height == 100 && data->tex_Wall_O->width == 100))
		return (1);
	return (0);
}

void	ft_get_texture(t_data *data, t_line *line, uint32_t **buf, int buf_x)
{
	int		buf_y;
	int		j;
	float	prop;

	j = line->y0;
	prop = ((float)TEX_WIDTH / data->ray->h_wall);
	while (j < line->y1)
	{
		buf_y = (j - line->y0) * prop;
		if (buf_y >= 0 && buf_y < TEX_HEIGHT && buf_x >= 0 && buf_x < TEX_WIDTH
			&& ft_check_frame(line->x, j) == 0)
			mlx_put_pixel(data->img[0], line->x, j, buf[buf_y][buf_x]);
		j++;
	}
}