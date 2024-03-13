#include <stdio.h>
#include "cub3d.h"
#include <stdlib.h>
#include <stdbool.h>

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	t_data	*data;
	uint32_t y;
	uint32_t i;
	uint32_t color;

	data = param;
	y = 0;
	while (y * 10 < data->img[0]->height)
	{
		i = 0;
		while (i * 10 < data->img[0]->width)
		{
			if (data->map[y][i] == '0')
				color = ft_pixel(0xF5, 0xF5, 0xDC,0xFF);
			if (data->map[y][i] == '1')
				color = ft_pixel(0x0, 0x0, 0x8B,0xFF);
			mlx_put_pixel(data->img[0], i * 13, y * 13, color);
			i++;
		}
		y++;
	}
}

int	main( int argc, char **argv)
{
	t_data	data;

	init_struct(&data);
	ft_file_format(argc, argv[1]);
	ft_read_file(&data, argv);
	if (!ver_data(&data))
		ft_free(&data);
	init_mlx(&data);
	ft_randomize(&data);
	mlx_loop_hook(data.mlx, &ft_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	ft_free(&data);
	return (EXIT_SUCCESS);
}


// int	main( int argc, char **argv)
// {
// 	t_data	data;

// 	// init_struct(&data);
// 	// ft_file_format(argc, argv[1]);
// 	// ft_read_file(&data, argv);
// 	if (!(data.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "MLX42", true)))
// 	{
// 		// puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (!(data.img = mlx_new_image(data.mlx, 128, 128)))
// 	{
// 		mlx_close_window(data.mlx);
// 		// puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (mlx_image_to_window(data.mlx, data.img, 0, 0) == -1)
// 	{
// 		mlx_close_window(data.mlx);
// 		// puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
	
// 	// mlx_loop_hook(mlx, ft_randomize, mlx);
// 	// mlx_loop_hook(mlx, ft_hook, mlx);

// 	// if (!ver_data(&data))
// 		// ft_free(&data);
// 	mlx_loop(data.mlx);
// 	mlx_terminate(data.mlx);
// 	return (EXIT_SUCCESS);
// }
