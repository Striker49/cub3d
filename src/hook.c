#include "cub3d.h"

void	show_minimap(t_data *data)
{
	if (data->img[1]->instances[0].z >= 0)
	{
		data->img[1]->instances[0].z = -1;
		data->img[2]->instances[0].z = -1;

	}
	else
	{
		data->img[1]->instances[0].z = 1;
		data->img[2]->instances[0].z = 2;
	}
}

void	re_img(t_data *data)
{
	mlx_delete_image(data->mlx, data->img[0]);
	data->img[0] = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	ft_floor_sky(data);
	ft_trace_wall(data, data->ray);
	mlx_image_to_window(data->mlx, data->img[0], 0, 0);
	// mlx_image_to_window(data->mlx, data->img[1], 0, 0);
	// mlx_image_to_window(data->mlx, data->img[2], 0, 0);
}

// void	ft_displayMiniMap(t_data *data)
// {
// 	if (data->miniMap_satus == 1)
// 	{
// 		mlx_delete_image(data->mlx, data->img[1]);
// 		data->img[1] = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
// 		ft_put_pixel(&data);
// 		mlx_image_to_window(data->mlx, data->img[1], 0, 0);
// 		data->miniMap_satus = 0;
// 	}
// 	else
// 	{
// 		mlx_delete_image(data->mlx, data->img[1]);
// 		mlx_image_to_window(data->mlx, data->img[1], 0, 0);
// 	}
// }

void	ft_hook(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data->mlx);
		// ft_free(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		move(data, NORTH);
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		move(data, SOUTH);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		move(data, WEST);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		move(data, EAST);
}

void	ft_option(mlx_key_data_t	keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		show_minimap(data);
}