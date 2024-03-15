#include <stdio.h>
#include "cub3d.h"
#include <stdlib.h>
#include <stdbool.h>

// void	draw_square(t_data *data, int32_t i, int32_t y, int32_t color)
// {
// 	int	l;
// 	int	k;
// 	k = y;
// 	l = i;
// 	while (y < k + 9)
// 	{
// 		i = l ;
// 		while (i < l + 9)
// 		{
// 			mlx_put_pixel(data->img[0], i, y, color);
// 			i++;
// 		}
// 		y++;
// 	}
// }

// int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }

// void ft_put_pixel(void* param)
// {
// 	t_data	*data;
// 	uint32_t y;
// 	uint32_t i;
// 	uint32_t color;

// 	data = param;
// 	y = 0;
// 	while (y < data->height)
// 	{
// 		i = 0;
// 		while (i < data->width)
// 		{
// 			// printf("i: %d\n", i);
// 			if (data->map[y][i] == '0')
// 				color = ft_pixel(0xFF, 0xFF, 0xFF,0xFF);
// 			else if (data->map[y][i] == '1')
// 				color = ft_pixel(0x0, 0x0, 0x8B,0xFF);
// 			else if (data->map[y][i] == 'P')
// 				color = ft_pixel(0xDC, 0x14, 0x3C,0xFF);
// 			else
// 				color = ft_pixel(0x0, 0x0, 0x0,0xFF);
// 			draw_square(data, i * 10, y * 10, color);
// 			// mlx_put_pixel(data->img[0], i * 10, y * 10, color);
// 			i++;
// 		}
// 		// printf("y: %d\n", y);
// 		y++;
// 	}
// }

int	main( int argc, char **argv)
{
	t_data	data;

	init_struct(&data);
	ft_file_format(argc, argv[1]);
	ft_read_file(&data, argv);
	if (!ver_data(&data))
		ft_free(&data);
	// init_mlx(&data);
	// ft_put_pixel(&data);
	// mlx_loop_hook(data.mlx, &ft_hook, &data);
	// mlx_loop(data.mlx);
	// mlx_terminate(data.mlx);
	ft_free(&data);
	return (EXIT_SUCCESS);
}

// int	main( int argc, char **argv)
// {
// 	ft_set_camera(&data);
// 	if (!(data.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "MLX42", true)))
// 	{
// 		return(EXIT_FAILURE);
// 	}
// 	if (!(data.img = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT)))
// 	{
// 		mlx_close_window(data.mlx);
// 		return(EXIT_FAILURE);
// 	}
// 	ft_floor_sky(&data);
// 	if (mlx_image_to_window(data.mlx, data.img, 0, 0) == -1)
// 	{
// 		mlx_close_window(data.mlx);
// 		return(EXIT_FAILURE);
// 	}
	
// 	// mlx_loop_hook(mlx, ft_put_pixel, mlx);
// 	// mlx_loop_hook(mlx, ft_hook, mlx);

// 	mlx_loop(data.mlx);
// 	mlx_terminate(data.mlx);
// 	return (EXIT_SUCCESS);
// }
