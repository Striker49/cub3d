#include <stdio.h>
#include "cub3d.h"
#include <stdlib.h>
#include <stdbool.h>

int	main( int argc, char **argv)
{
	t_data	data;

	init_struct(&data);
	ft_file_format(argc, argv[1]);
	ft_read_file(&data, argv);
	if (!ver_data(&data))
		ft_free(&data);
	ft_free(&data);
	return (0);
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
