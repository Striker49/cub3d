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

void	ft_load_texture(t_data *data)
{
	data->tex_Wall_R = mlx_load_png("/../Prototype_Textures/Grey/prototype.png");
}

// void	paint_line(t_data *data, t_line *line, t_color *color)
// {
// 	int x;

// 	x = line->x0;
// 	while (x <= line->x1)
// 	{
// 		mlx_put_pixel(data->img[0], x, line->y, get_rgba(color->Color1[0], color->Color1[1], color->Color1[2], 255));
// 		x++;
// 	}
// }

// void	pixel_on_img()
// {

// }

// void	paint_texture_line(t_data *data, t_ray *ray, t_line *line, double wall_x)
// {
// 	int y;
// 	int y_max;

// 	if (line->y0 < line->y1)
// 	{
// 		y = line->y0;
// 		y_max = line->y1;
// 	}
// 	else
// 	{
// 		y = line->y1;
// 		y_max = line->y0;
// 	}
// 	if (y >= 0)
// 	{
// 		while (y < y_max)
// 		{
			// pixel_on_img(rgb, x, y, img);
// 		}
// 	}
// }

// void	ft_scaling_transform(t_data *data, t_ray *ray)
// {
// 	double wall_x;
// 	t_color *color;

// 	if (ray->side == WEST || ray->side == EAST)
// 		ray->line->wall_x = data->pl_y + ray->perpWallDist * ray->rayDirY;
// 	else
// 		ray->line->wall_x = data->pl_x + ray->perpWallDist * ray->rayDirX;
// 	ray->line->wall_x -= floor(ray->line->wall_x); //fct qui arrondie de math.h

	ray->line->x = ray->curr_x;
	
	//paint texture
	// if (data->map[ray->mapY][ray->mapX] == '1')
	// {
	// 	paint_texture_line(data, ray, ray->line, ray->line->wall_x);
	// }
	// ray->line->y0 = 0;
	// ray->line->y1 = ray->draw_start;
	// trace_line(data, line);

	// ray->line->y0 = WINDOW_HEIGHT;
	// ray->line->y1 = ray->draw_end;

	//  trace_line(data, line);

}