#include "cub3d.h"

static uint32_t     **ft_buf_line_text(mlx_texture_t *tex_Wall_R)
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
	if (data->tex_Wall_N->height == 100 && data->tex_Wall_N->width == 100)
		data->n_buf = ft_buf_line_text(data->tex_Wall_N);
	if (data->tex_Wall_S->height == 100 && data->tex_Wall_S->width == 100)
		data->s_buf = ft_buf_line_text(data->tex_Wall_S);
	if (data->tex_Wall_E->height == 100 && data->tex_Wall_E->width == 100)
		data->e_buf = ft_buf_line_text(data->tex_Wall_E);
	if (data->tex_Wall_O->height == 100 && data->tex_Wall_O->width == 100)
		data->o_buf = ft_buf_line_text(data->tex_Wall_O);
	else
	{
		// ft_resize_tex(data, data->tex_Wall_N, data->n_buf);
		// ft_resize_tex(data, data->tex_Wall_S, data->s_buf);
		// ft_resize_tex(data, data->tex_Wall_E, data->e_buf);
		// ft_resize_tex(data, data->tex_Wall_O, data->o_buf);
		perror("Erreur texture 100x100");
		ft_free(data);
		exit(1);
	}
    printf("rere\n");
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
		if (buf_y >= 0 && buf_y <= TEX_HEIGHT && buf_x >= 0
			&& buf_x <= TEX_WIDTH && ft_check_frame(line->x, j) == 0)
			mlx_put_pixel(data->img[0], line->x, j, buf[buf_y][buf_x]);
		j++;
	}
}

void	ft_resize_tex(mlx_texture_t *tex_Wall, uint32_t **dest_data)
{
	float	x_ratio;
	float	y_ratio;
	int		x;
	int		y;
	int		src_x;
	int		src_y;
	int		i;

	x_ratio = (float)tex_Wall->width / 100;
	y_ratio = (float)tex_Wall->height / 100;
	dest_data = malloc(sizeof(uint32_t *) * (TEX_HEIGHT));
	if (!dest_data)
	{
		// free
		exit(-1);
	}
	y = 0;
	while (y < 100)
	{
		dest_data[y] = malloc(sizeof(uint32_t) * (TEX_WIDTH));
		if (!dest_data[y])
		{
			// ft_free();
			exit(-1);
		}
		x = 0;
		while (x < 100)
		{
			src_x = (int)(x * x_ratio);
			src_y = (int)(y * y_ratio);
			i = (src_y * tex_Wall->width * 4) + (src_x * 4);
			dest_data[y][x] = get_rgba(tex_Wall->pixels[i], tex_Wall->pixels[i
					+ 1], tex_Wall->pixels[i + 2], tex_Wall->pixels[i + 3]);
			x++;
		}
		y++;
	}
}
