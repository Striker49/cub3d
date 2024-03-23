#include "cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_gradient(t_data *data, int y, int x)
{
	int color1[3] = {199, 0, 57};
	int color2[3] = {88, 24, 69};
	int	mix_color[3];
	double t;

	t = (double)y / WINDOW_HEIGHT;
	mix_color[0] = (int)((1 - t) * color1[0] + t * color2[0]);
	mix_color[1] = (int)((1 - t) * color1[1] + t * color2[1]);
	mix_color[2] = (int)((1 - t) * color1[2] + t * color2[2]);
	mlx_put_pixel(data->img[0], x, y, get_rgba(mix_color[0], mix_color[1], mix_color[2], 255));
}

int	ft_check_frame(t_data *data)
{
	if (data->sc_x <= WINDOW_WIDTH && data->sc_y <= WINDOW_HEIGHT && data->sc_y >= 0 && data->sc_x >= 0)
	{
		return (0);
	}
	return (1);
}

void	ft_floor_sky(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			ft_gradient(data, y, x);
			x++;
		}
		y++;
	}
}

void	paint_line(t_data *data, t_line *line, t_color *color)
{
	int x;

	x = line->x0;
	while (x <= line->x1)
	{
		mlx_put_pixel(data->img[0], x, line->y, get_rgba(color->Color1[0], color->Color1[1], color->Color1[2], 255));
		x++;
	}
}

void	paint_texture_line(t_data *data, t_ray *ray, t_line *line, double wall_x)
{
	line->tex_x = (int)(wall_x * TEX_WIDTH);
	if ((ray->side == WEST || ray->side == EAST) && ray->rayDirX > 0)
		line->tex_x = TEX_WIDTH - line->tex_x - 1;
	if ((ray->side == NORTH || ray->side == SOUTH) && ray->rayDirY < 0)
		line->tex_x = TEX_WIDTH - line->tex_x - 1;

	int y;
	int color;

	y = line->y0;
	while (y <= line->y1)
	{
		line->tex_y = (((y *2 - WINDOW_HEIGHT + ray->line_height) * TEX_HEIGHT) / (ray->line_height * 2));
		// color = get_tex_pixel(line->tex_x, line->tex_y);
		// mlx_texture_to_image(mlx_t* mlx, mlx_texture_t* texture);
		mlx_put_pixel(data->img[0], line->x, y, color);
		y++;
	}
}