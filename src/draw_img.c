#include "cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_line(t_data *data)
{
	double	x;
	double	y;
    double	step = 0.1;  // Adjust this value as needed
	uint32_t color;

	x = data->player.x;
	y = data->player.y;
	color = ft_pixel(0x7F, 0xFF, 0x0, 0xFF);
	while (x <= data->player.x + data->pl_dir_x * 2 && y <= data->player.y + data->pl_dir_y * 2)
	{
		mlx_put_pixel(data->img[1], x * 10, y * 10, color);
		x += step * data->pl_dir_x;
		y += step * data->pl_dir_y;
	}
}

void	draw_player(t_data *data, int32_t i, int32_t y, int32_t color)
{
	int	l;
	int	k;
	k = y;
	l = i;
	while (y - 3 < k + 3)
	{
		i = l ;
		while (i - 3 < l + 3)
		{
			mlx_put_pixel(data->img[2], i - 3, y - 3, color);
			i++;
		}
		y++;
	}
}

void	draw_square(t_data *data, int32_t i, int32_t y, int32_t color)
{
	int	l;
	int	k;
	k = y;
	l = i;
	while (y < k + 9)
	{
		i = l ;
		while (i < l + 9)
		{
			mlx_put_pixel(data->img[1], i, y, color);
			i++;
		}
		y++;
	}
}

void ft_put_pixel(void* param)
{
	t_data	*data;
	uint32_t y;
	uint32_t i;
	uint32_t color;

	data = param;
	y = 0;
	while (y < data->height)
	{
		i = 0;
		while (i < data->width)
		{
			// printf("i: %d\n", i);
			if (data->map[y][i] == '0')
				color = get_rgba(52, 113, 235, 255);
				// color = ft_pixel(0xFF, 0xFF, 0xFF,0xFF);
			else if (data->map[y][i] == '1')
				color = get_rgba(54, 39, 194, 255);
				// color = ft_pixel(0x0, 0x0, 0x8B,0xFF);
			else
				color = ft_pixel(0x0, 0x0, 0x0,0xFF);
			draw_square(data, i * 10, y * 10, color);
			// mlx_put_pixel(data->img[1], i * 10, y * 10, color);
			i++;
		}
		// printf("y: %d\n", y);
		y++;
	}
	color = ft_pixel(0xDC, 0x14, 0x3C,0xFF);
	// printf("data->player.x: %f\n", data->player.x);
	// printf("data->player.y: %f\n", data->player.y);
	draw_player(data, data->player.x * 10, data->player.y * 10, color);
	// draw_line(data);
}