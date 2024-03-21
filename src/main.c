#include <stdio.h>
#include "cub3d.h"
#include <stdlib.h>
#include <stdbool.h>


// 

int	main( int argc, char **argv)
{
	t_data	data;

	init_struct(&data);
	ft_file_format(argc, argv[1]);
	ft_read_file(&data, argv);
	if (!ver_data(&data))
		ft_free(&data);
	init_mlx(&data);
	ft_put_pixel(&data);
	mlx_loop_hook(data.mlx, &ft_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
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
