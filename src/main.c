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

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->pix->addr + (y * data->pix->line_length + x * (data->pix->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_gradient(t_data *data, int y, int x)
{
	int color1[3] = {199, 0, 57};
	int color2[3] = {218, 247, 166};
	int	mix_color[3];
	double t;

	t = (double)y / WINDOW_HEIGHT;
	mix_color[0] = (int)((1 - t) * color1[0] + t * color2[0]);
	mix_color[1] = (int)((1 - t) * color1[1] + t * color2[1]);
	mix_color[2] = (int)((1 - t) * color1[2] + t * color2[2]);
	mlx_put_pixel(data->img, x, y, get_rgba(mix_color[0], mix_color[1], mix_color[2], 255));
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

int	main( int argc, char **argv)
{
	t_data	data;

	init_struct(&data);
	// ft_file_format(argc, argv[1]);
	// ft_read_file(&data, argv);
	ft_set_camera(&data);
	if (!(data.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "MLX42", true)))
	{
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(data.img = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT)))
	{
		mlx_close_window(data.mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	ft_floor_sky(&data);
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