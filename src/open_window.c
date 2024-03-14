#include "cub3d.h"

int	init_mlx(t_data *data)
{
	if (!(data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(data->img[0] = mlx_new_image(data->mlx, 128, 128)))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	// if (!(data->img[1] = mlx_new_image(data->mlx, 128, 128)))
	// {
	// 	mlx_close_window(data->mlx);
	// 	puts(mlx_strerror(mlx_errno));
	// 	return(EXIT_FAILURE);
	// }
	if (mlx_image_to_window(data->mlx, data->img[0], 128, 128) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	// if (mlx_image_to_window(data->mlx, data->img[1], 256, 256) == -1)
	// {
	// 	mlx_close_window(data->mlx);
	// 	puts(mlx_strerror(mlx_errno));
	// 	return(EXIT_FAILURE);
	// }
	return (0);
}
