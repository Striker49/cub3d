#include <stdio.h>
#include "cub3d.h"
#include <stdlib.h>
#include <stdbool.h>

void ft_set_camera(t_data *data)
{
	t_vec vec;

	//position player
	data->pl_x = 3;
	data->pl_y = 2;
	//definir le vecteur directionnel
	data->pl_dir_x = 0;
	data->pl_dir_y = 1;
	//definir le vecteur normal
	vec.x = -data->pl_dir_y;
	vec.y = data->pl_dir_x;
	printf("Camera vector: (%f, %f)\n", vec.x, vec.y);

	//calcul du FOV horizontal
	data->fov_x = atan2(vec.y, vec.x);
	//calcul du FOV vectical
	data->aspect_ratio = (double)WINDOW_WIDTH / WINDOW_HEIGHT;
	data->fov_y = 2 * atan(tan(data->fov_x / 2) / data->aspect_ratio);

	printf("FOV horizontal: %f degrees\n", data->fov_x * 180 / M_PI);
    printf("FOV vertical: %f degrees\n", data->fov_y * 180 / M_PI);
}

ft_calculer_dist_floor();

void	ft_floor_sky(t_data *data)
{
	int x;
	double dist_floor;
	double dist_sky;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		dist_floor = ft_calculer_dist_floor();
		x++;
	}
}

int	main( int argc, char **argv)
{
	t_data	data;

	init_struct(&data);
	// ft_file_format(argc, argv[1]);
	// ft_read_file(&data, argv);
	ft_set_camera(&data);
	ft_floor_sky(&data);
	if (!(data.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "MLX42", true)))
	{
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(data.img = mlx_new_image(data.mlx, 128, 128)))
	{
		mlx_close_window(data.mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(data.mlx, data.img, 0, 0) == -1)
	{
		mlx_close_window(data.mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	// mlx_loop_hook(mlx, ft_randomize, mlx);
	// mlx_loop_hook(mlx, ft_hook, mlx);

	// if (!ver_data(&data))
		// ft_free(&data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}