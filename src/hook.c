#include "cub3d.h"

void	show_minimap(t_data *data)
{
	if (data->img[1]->instances[0].z >= 0)
	{
		data->img[1]->instances[0].z = -1;
		data->img[2]->instances[0].z = -1;
		data->miniMap_satus = -1;
	}
	else
	{
		data->img[1]->instances[0].z = 1;
		data->img[2]->instances[0].z = 2;
		data->miniMap_satus = 2;
	}
}

void	re_img(t_data *data)
{
	ft_floor_sky(data);
	ft_trace_wall(data, data->ray);
}

void	mouse_hook(void *param)
{
	int32_t	x;
	int32_t	y;
	t_data	*data;

	data = param;
	mlx_get_mouse_pos(data->mlx, &x, &y);
	if (x < WINDOW_WIDTH / 2)
		rotate_left(data, (x - (WINDOW_WIDTH / 2)));
	else if (x > WINDOW_WIDTH / 2)
		rotate_right(data, (x - (WINDOW_WIDTH / 2)));
	mlx_set_mouse_pos(data->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	if (x != 0)
		re_img(data);
}

void	ft_hook(void *param)
{
	t_data	*data;

	data = param;
	mouse_hook(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data->mlx);
		// ft_free(data);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move(data, NORTH);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move(data, SOUTH);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move(data, WEST);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move(data, EAST);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_left(data, 10);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_right(data, 10);
	else
		return ;
	re_img(data);
}

void	ft_option(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		show_minimap(data);
}
