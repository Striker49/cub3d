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
			if (y < (WINDOW_HEIGHT / 2))
				mlx_put_pixel(data->img[0], x, y, get_rgba(data->ceiling[0], data->ceiling[1], data->ceiling[2], 255));
			else
				mlx_put_pixel(data->img[0], x, y, get_rgba(data->floor[0], data->floor[1], data->floor[2], 255));
			x++;
		}
		y++;
	}
}

// void ft_scaling_transform(t_data *data, t_ray *ray, int rgb)
// {
// 	data->pixTex[0] = (rgb >> 16) & 0xFF;
// 	data->pixTex[1] = (rgb >> 8) & 0xFF;
// 	data->pixTex[2] = rgb & 0xFF;

// 	data->img[0]->pixels[data->tex_Wall_R->width + ray->line->x * data->tex_Wall_R->bytes_per_pixel / 8] = data->pixTex[2];
// 	data->img[0]->pixels[data->tex_Wall_R->width + ray->line->x * data->tex_Wall_R->bytes_per_pixel / 8 + 1] = data->pixTex[1];
// 	data->img[0]->pixels[data->tex_Wall_R->width + ray->line->x * data->tex_Wall_R->bytes_per_pixel / 8 + 2] = data->pixTex[0];
// }

// void ft_scaling_transform(t_data *data, t_ray *ray)
// {
// 	int i;
// 	int scale;
// 	int img_index = (ray->line->y * data->ray->h_wall) + (ray->line->x * 24 / 8);
// 	int tex_index = (ray->line->tex_y * ray->line->tex_length) + (ray->line->tex_x * (32 / 8));
	
// 	scale = ray->line->y * ray->line->tex_length - (WINDOW_HEIGHT * data->cameraX) * ray->line->tex_length / 2 + ray->h_wall * ray->line->tex_length / 2;
// 	ray->line->tex_y = ((scale * ray->line->tex_height) / ray->h_wall) / ray->line->tex_length;
// 	i = 0;
// 	while (i < 3)
// 	{
// 		data->img[0]->pixels[img_index + i] = data->tex_Wall_R->pixels[tex_index + i];
// 		i++;
// 	}
// }


// int *ft_scaling_transform(t_data *data, t_ray *ray)
// {
// 	int offset;

// 	offset = (y * TEX_WIDTH + x) * 3; //rgb format 3 bytes par pixel
// 	data->pixTex[0] = data->tex_Wall_R[offset];
// 	data->pixTex[1] = data->tex_Wall_R[offset + 1];
// 	data->pixTex[2] = data->tex_Wall_R[offset + 2];
// 	return (pixTex);	

// }
